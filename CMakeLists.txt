cmake_minimum_required(VERSION 3.0)
project(boost_threads)
set(CMAKE_BUILD_TYPE Debug)

find_package(Boost 1.68.0 COMPONENTS filesystem REQUIRED)
find_package(Boost 1.68.0 COMPONENTS thread REQUIRED)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  set(SOURCE ./src/boost_threads.cpp)
  add_executable(${PROJECT_NAME} ${SOURCE})
  target_link_libraries(
    boost_threads 
    ${Boost_LIBRARIES}
    Boost::thread)
endif()

