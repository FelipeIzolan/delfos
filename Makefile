all: dir compile

dir:
	mkdir -p ./build

compile:
	g++ main.cpp -Iinclude $(shell pkg-config --cflags --libs gtk+-3.0  webkit2gtk-4.0) -o ./build/delfos-app
