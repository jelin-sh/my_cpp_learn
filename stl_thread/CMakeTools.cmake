###############################################################
# 获取子文件夹列表
# 用法：
#    list_subdir(返回列表变量 当前文件夹(绝对路径))
###############################################################
function(list_subdir RESULT CURDIR)
    file(GLOB CHILDREN RELATIVE ${CURDIR} ${CURDIR}/*)
    set(DIRLIST "")
    foreach (CHILD ${CHILDREN})
        if (IS_DIRECTORY ${CURDIR}/${CHILD})
            list(APPEND DIRLIST ${CHILD})
        endif ()
    endforeach ()
    set(${RESULT} ${DIRLIST} PARENT_SCOPE)
endfunction()

###############################################################
# 将相对路径转换为绝对路径
# 用法：
#    path_real2abs(返回绝对路径变量 相对路径变量)
###############################################################
function(path_real2abs PATH_ABS PATH_REAL)
    get_filename_component(PATH_ABS_TEMP ${PATH_REAL} ABSOLUTE)
    set(${PATH_ABS} ${PATH_ABS_TEMP} PARENT_SCOPE)
endfunction()

###############################################################
# 将相对路径列表转换为绝对路径列表
# 用法：
#    list_real2abs(返回绝对路径列表变量 相对路径列表变量)
###############################################################
function(list_real2abs LIST_ABS LIST_REAL)
    set(PATH_ITEM "")
    path_real2abs(LIST_RES ${LIST_REAL})
    foreach (PATH_ITEM IN LISTS ARGN)
        path_real2abs(PATH_ABS_TEMP ${PATH_ITEM})
        list(APPEND LIST_RES ${PATH_ABS_TEMP})
    endforeach ()
    set(${LIST_ABS} ${LIST_RES} PARENT_SCOPE)
endfunction()

###############################################################
# 根据protobuf文件生成gRPC代码，并打包为静态链接库
#
# 此函数会将protobuf文件名称作为静态链接库名称，例如 test.proto 将生成:
# - libproto_test.a
# - proto_test.pb.cc
# - proto_test.pb.h
# - proto_test.grpc.cc.h
# - proto_test.grpc.pb.h
#
# 用法：
#    grpc_generate(返回绝对路径列表变量 相对路径列表变量)
###############################################################
function(grpc_generate PROTOBUF_SRC)
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${PROTOBUF_SRC}) #获取文件名
    get_filename_component(FILE_SRC ${PROTOBUF_SRC} ABSOLUTE)
    get_filename_component(FILE_PATH "${FILE_SRC}" PATH)
    get_filename_component(FILE_GEN_DIR "${CMAKE_BINARY_DIR}/grpc_proto" ABSOLUTE)
    file(MAKE_DIRECTORY ${FILE_GEN_DIR}) #创建文件夹

    set(${FILE_NAME}_PROTO_SRC "${FILE_GEN_DIR}/${FILE_NAME}.pb.cc")
    set(${FILE_NAME}_PROTO_HDR "${FILE_GEN_DIR}/${FILE_NAME}.pb.h")
    set(${FILE_NAME}_GRPC_SRC "${FILE_GEN_DIR}/${FILE_NAME}.grpc.pb.cc")
    set(${FILE_NAME}_GRPC_HDR "${FILE_GEN_DIR}/${FILE_NAME}.grpc.pb.h")


    message(">>> FILE_NAME = ${FILE_NAME}")
    message(">>> FILE_SRC = ${FILE_SRC}")
    message(">>> FILE_PATH = ${FILE_PATH}")
    message(">>> FILE_GEN_DIR = ${FILE_GEN_DIR}")

    message(">>> ${FILE_NAME}_PROTO_SRC = ${${FILE_NAME}_PROTO_SRC}")
    message(">>> ${FILE_NAME}_PROTO_HDR = ${${FILE_NAME}_PROTO_HDR}")
    message(">>> ${FILE_NAME}_GRPC_SRC = ${${FILE_NAME}_GRPC_SRC}")
    message(">>> ${FILE_NAME}_GRPC_HDR = ${${FILE_NAME}_GRPC_HDR}")

    add_custom_command(
        OUTPUT
        "${${FILE_NAME}_PROTO_SRC}"
        "${${FILE_NAME}_PROTO_HDR}"
        "${${FILE_NAME}_GRPC_SRC}"
        "${${FILE_NAME}_GRPC_HDR}"

        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${FILE_GEN_DIR}"
        --cpp_out "${FILE_GEN_DIR}"
        -I "${FILE_PATH}"
        --plugin=protoc-gen-grpc=${_GRPC_CPP_PLUGIN_EXECUTABLE}
        "${FILE_SRC}"
        DEPENDS "${FILE_SRC}"
    )

    add_library(
        proto_${FILE_NAME}
        ${${FILE_NAME}_PROTO_SRC}
        ${${FILE_NAME}_PROTO_HDR}
        ${${FILE_NAME}_GRPC_SRC}
        ${${FILE_NAME}_GRPC_HDR}
    )

    target_include_directories(
        proto_${FILE_NAME} PUBLIC
        ${FILE_GEN_DIR}
    )

    target_link_libraries(
        proto_${FILE_NAME} PRIVATE
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF}
    )

    #    set_target_properties(
    #        proto_${FILE_NAME} PROPERTIES
    #        RUNTIME_OUTPUT_DIRECTORY ${FILE_GEN_DIR}
    #    )

endfunction()

###############################################################
# 根据protobuf文件生成gRPC代码，并打包为静态链接库，支持批量生成和打包
#
# 用法：
#    grpc_generate(返回绝对路径列表变量 相对路径列表变量)
###############################################################
function(list_grpc_generate LIST_PROTOBUF_SRC)
    grpc_generate(${LIST_PROTOBUF_SRC})
    foreach (FILE_ITEM IN LISTS ARGN)
        grpc_generate(${FILE_ITEM})
    endforeach ()
endfunction()

###############################################################
# 激活FetchContent下载的依赖，替代FetchContent_MakeAvailable
#
# 用法：
#    MakeAvailable(gtest)
###############################################################
macro(MakeAvailable NAME)
    FetchContent_GetProperties(${NAME})
    if (NOT ${NAME}_POPULATED)
        FetchContent_Populate(${NAME})
        add_subdirectory(${${NAME}_SOURCE_DIR} ${${NAME}_BINARY_DIR} EXCLUDE_FROM_ALL)
    endif ()
endmacro()
