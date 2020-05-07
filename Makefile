# TODO: Estruturar o Makefile corretamente
all: compile run clean 

compile:
	@echo "Compiling..."
	@g++ -o ./bin/preprocessing.bin ./src/preprocessing.cpp

run:
	@echo "\nRuning..."
	@./bin/preprocessing.bin

clean:
	@echo "\n\nCleaning up..."
	@rm ./bin/*.bin	
