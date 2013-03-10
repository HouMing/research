IF EXIST *.vcproj GOTO M_ok

ECHO "非工程文件"

EXIT

:M_ok
mkdir src 
echo > src/main.cpp

mkdir include


mkdir testunit
echo > testunit/test.cpp

mkdir workdir

pause