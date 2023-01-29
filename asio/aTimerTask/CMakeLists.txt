
find_package(Threads REQUIRED)

add_library(aTimerTask aTimerTask.cpp)
target_include_directories(aTimerTask PUBLIC .)
target_compile_definitions(aTimerTask PUBLIC -DASIO_STANDALONE)
target_link_libraries(aTimerTask PUBLIC Threads::Threads)

add_library(Modules::aTimerTask ALIAS aTimerTask)