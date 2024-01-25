#!/bin/bash

openTestComponentWithCheck()
{
    exeName=$1;
    exePath=`dirname $(realpath $0)`/../build/Tests/Modules/$exeName/$exeName
    if test -e "$exePath";
    then
        echo "$exePath has been found";
        chmod +x $exePath
        LIBGL_ALWAYS_SOFTWARE=1 $exePath;
    else
        echo "$exePath has not been found... aborting";
    fi
}

runTestCoverage()
{
    buildPath=`dirname $(realpath $0)`/../build/
    if test -e "$buildPath";
    then
        echo "$buildPath exists";
        cd $buildPath;
        LIBGL_ALWAYS_SOFTWARE=1 make $1;
        cd $buildPath/$1;
        explorer.exe .;
    else
        echo "$buildPath has not been found... aborting";
    fi
}