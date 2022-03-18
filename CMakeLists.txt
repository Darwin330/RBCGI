cmake_minimum_required(VERSION 3.14)
project(Project)
set(CMAKE_BUILD_TYPE "Debug")
set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_POSTFIX "_d")    

set(CMAKE_CXX_STANDARD 14)
add_executable(Server.exe src/Common.cpp src/Handle.cpp src/EventHandler.cpp 
    src/Eventmultiplexer.cpp src/Reactor.cpp src/Request.cpp src/Threadpool.cpp src/ssh_ser_2.cpp )
target_include_directories(Server.exe
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
