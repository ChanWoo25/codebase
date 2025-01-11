cmake_minimum_required(VERSION 3.10)

project(HelloWorld)

find_package(fmt CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)

set(GFLAGS_USE_TARGET_NAMESPACE ON)
find_package(gflags CONFIG REQUIRED)
find_package(glog CONFIG REQUIRED)

set(LIBRARIES fmt::fmt gflags::gflags glog::glog cpr::cpr)
add_executable(HelloWorld helloworld.cpp)
target_link_libraries(HelloWorld PRIVATE ${LIBRARIES})