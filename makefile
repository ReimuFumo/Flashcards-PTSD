all: unix

unix:
	mkdir -p bin
	g++ -std=c++11 main.cpp -o bin/flashcards -Wall
	./bin/flashcards

win:
	mkdir -p bin
	g++ -std=c++11 main.cpp -o bin/flashcards.exe -Wall
	./bin/flashcards.exe
