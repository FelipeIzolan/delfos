qlite3:
	gcc ./libs/sqlite3/sqlite3.c -c -o ./libs/sqlite3/sqlite3.o

windows:
	g++ main.cpp ./libs/sqlite3/sqlite3.o -mwindows -Iinclude -Ilibs/sqlite3 -Ilibs/webview -Ilibs/SimpleJSON -Ilibs/webview2/build/native/include -ladvapi32 -lole32 -lshell32 -lshlwapi -luser32 -lversion -lws2_32 -o build/delfos.exe 

linux:
	g++ main.cpp -Iinclude -Ilibs/SimpleJSON -Ilibs/webview $(shell pkg-config --cflags --libs sqlite3 gtk+-3.0 webkit2gtk-4.0) -o ./build/delfos
