IF EXIST *.vcproj GOTO M_ok

ECHO "�ǹ����ļ�"

EXIT

:M_ok
mkdir src 
echo > src/main.cpp

mkdir include


mkdir testunit
echo > testunit/test.cpp

mkdir workdir

pause