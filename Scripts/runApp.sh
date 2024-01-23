#!/bin/bash
exeName="RPGTDD";
exePath=`dirname $(realpath $0)`/../build/Src/$exeName
if test -e "$exePath";
then
    echo "$exePath has been found";
    chmod +x $exePath
    LIBGL_ALWAYS_SOFTWARE=1 $exePath;
else
    echo "$exePath has not been found... aborting";
fi