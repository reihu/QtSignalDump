all:
	g++ -Wall -fPIC -I/usr/include/qt4/ -shared -o libQtMetaInvoke.so main.cpp
