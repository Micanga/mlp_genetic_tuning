# TODO: Estruturar o Makefile corretamente

all: clean compile run

compile:
	g++ -o ./bin/preprocessing.bin ./src/preprocessing.cpp

run:
	./bin/preprocessing.bin

clean:
	rm ./bin/*.bin