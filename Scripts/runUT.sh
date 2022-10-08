#!/bin/bash
dirname=`dirname $(realpath $0)`/../build
if test -d "$dirname";
then
    echo "$dirname has been found";
    cd $dirname;
    ctest -C Debug;
else
    echo "$dirname has not been found";
fi