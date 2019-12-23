cd build
cmake -G "MSYS Makefiles" -DCMAKE_MAKE_PROGRAM=mingw32-make -DCMAKE_INSTALL_PREFIX:PATH=/usr ../
make
