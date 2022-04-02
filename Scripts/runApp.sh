#!/bin/bash
exeName="RPGTDD.exe";
exePath=`dirname $(realpath $0)`/../build/Src/$exeName
if test -e "$exePath";
then
    echo "$exePath has been found";
    chmod +x $exePath
    $exePath;
else
    echo "$exePath has not been found... aborting";
fi

