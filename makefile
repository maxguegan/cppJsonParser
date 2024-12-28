main: obj/main.o obj/JsonParser.o
	g++ obj/main.o obj/JsonParser.o -o bin/main

obj/main.o: main.cpp
	g++ -Iinclude -c main.cpp -o obj/main.o

obj/JsonParser.o: JsonParser.cpp
	g++ -Iinclude -c JsonParser.cpp -o obj/JsonParser.o