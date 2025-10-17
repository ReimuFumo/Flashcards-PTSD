all: unix

unix:
	mkdir -p bin
	g++ -std=c++11 main.cpp -o bin/flashcards
	./bin/flashcards

win:
	mkdir -p bin
	g++ -std=c++11 main.cpp -o bin/flashcards.exe
	./bin/flashcards.exe
