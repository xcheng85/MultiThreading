cmake_minimum_required(VERSION 3.0)
project(boost_threads)
set(CMAKE_BUILD_TYPE Debug)

find_package(Boost 1.68.0 COMPONENTS filesystem REQUIRED)
find_package(Boost 1.68.0 COMPONENTS thread REQUIRED)

if(Boost_FOUND)
  add_subdirectory(boostThreads)
  add_subdirectory(boostThreadsMutex)
endif()

