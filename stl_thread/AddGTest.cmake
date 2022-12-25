include(FetchContent)

message(STATUS "Download & Install GTest ...")
set(FETCHCONTENT_QUIET FALSE)
fetchcontent_declare(
    gtest
    GIT_REPOSITORY https://gitee.com/cudi/googletest.git
    GIT_TAG release-1.12.1
    GIT_PROGRESS TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
MakeAvailable(gtest)
message(STATUS "Download & Install GTest ... Done")