#!/bin/bash
dirname=`dirname $(realpath $0)`/../build
if test -d "$dirname";
then
    echo "$dirname has been found";
    cd $dirname;
else
    echo "$dirname has not been found";
    mkdir $dirname;
    cd $dirname;
    #conan install ../ --build=missing --profile=mingw64;
    cmake -DBUILD_SHARED_LIBS=OFF -S $dirname/../ -B $dirname/ -G 'Ninja' -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=OFF;
    #you can also use other makefiles instead of 'Ninja' ex. 'Unix Makefiles' etc.
fi
# make;
ninja;