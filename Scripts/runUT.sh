#!/bin/bash
dirname=`dirname $(realpath $0)`/../build
if test -d "$dirname";
then
    echo "$dirname has been found";
    cd $dirname;
    LIBGL_ALWAYS_SOFTWARE=1 ctest -C Debug --output-on-failure;
else
    echo "$dirname has not been found";
fi