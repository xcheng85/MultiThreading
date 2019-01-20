project(cpp_threads)
set(SOURCE ./src/cpp_threads.cpp)
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ../bin)