cmake_minimum_required(VERSION 2.8.11)
project(TYMovieEditor)

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

aux_source_directory(. SRC_LIST)
#qt5_add_resources(qrc_FILES drawable.qrc)

qt5_wrap_ui(ui_FILES mainwindow.ui)

# Tell CMake to create the TYMovieEditor executable
#add_executable(TYMovieEditor ${SRC_LIST} ${ui_FILES} ${qrc_FILES})
add_executable(TYMovieEditor ${SRC_LIST} ${ui_FILES})

target_link_libraries(TYMovieEditor libopenshot.dll.a libopenshot-audio.dll.a)

# Use the Widgets module from Qt 5.
target_link_libraries(TYMovieEditor Qt5::Widgets)