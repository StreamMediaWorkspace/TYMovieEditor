cmake_minimum_required(VERSION 2.8.11)
project(testproject)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories("./include")
include_directories("./include/libopenshot-audio")
include_directories("./include/libopenshot")
include_directories("./include/libopenshot/Qt")

link_directories("./lib")

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Tell CMake to create the helloworld executable
add_executable(helloworld WIN32 main.cpp PlayerDemo.cpp)

target_link_libraries(helloworld libopenshot.dll.a)
target_link_libraries(helloworld libopenshot-audio.dll.a)

# Use the Widgets module from Qt 5.
target_link_libraries(helloworld Qt5::Widgets)