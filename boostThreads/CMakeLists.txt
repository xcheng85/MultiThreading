project(boost_threads)
include_directories(${Boost_INCLUDE_DIRS})
set(SOURCE ./src/boost_threads.cpp)
add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} 
    ${Boost_LIBRARIES}
    Boost::thread)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ../bin)