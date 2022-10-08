exeName="StatesTests";
exePath=`dirname $(realpath $0)`/../build/Tests/Modules/StatesTests/$exeName
if test -e "$exePath";
then
    echo "$exePath has been found";
    chmod +x $exePath
    $exePath;
else
    echo "$exePath has not been found... aborting";
fi