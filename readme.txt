Windows:
export PATH=$PATH:/d/project/msys32/mingw32/bin:/d//msys32/mingw32/lib:/d/project/msys32/usr/bin:/d/project/msys32/usr/lib
cd build
cmake -G "MSYS Makefiles" -DCMAKE_MAKE_PROGRAM=mingw32-make -DCMAKE_INSTALL_PREFIX:PATH=/usr ../
make

Mac:
CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:/usr/local/include/:/usr/local/Cellar/jsoncpp/1.9.1/include
cd build
cmake -G "Unix Makefiles"  -DCMAKE_CXX_COMPILER=/usr/bin/g++ -DCMAKE_PREFIX_PATH=/Users/admin/Qt5.7.1/5.7/clang_64/lib/cmake/Qt5Widgets ../ -D"CMAKE_BUILD_TYPE:STRING=Release" 
make



