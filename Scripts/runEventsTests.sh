exeName="EventsTests";
exePath=`dirname $(realpath $0)`/../build/Tests/Modules/EventsTests/$exeName
if test -e "$exePath";
then
    echo "$exePath has been found";
    chmod +x $exePath
    $exePath;
else
    echo "$exePath has not been found... aborting";
fi