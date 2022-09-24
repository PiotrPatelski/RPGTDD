#!/bin/bash
buildPath=`dirname $(realpath $0)`/../build/
if test -e "$buildPath";
then
    echo "$buildPath exists";
    cd $buildPath;
    make TestCoverageHtml;
    cd $buildPath/TestCoverageHtml;
    explorer.exe .;
else
    echo "$buildPath has not been found... aborting";
fi