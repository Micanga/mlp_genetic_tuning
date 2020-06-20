all:
  @g++ ./src/*.cpp -o main -Wall -lm -I./include
  
compile:
	@echo "Compiling..."
	@g++ -o ./bin/preprocessing.bin ./src/preprocessing.cpp

run:
	@echo "\nRuning..."
	@./bin/preprocessing.bin

clean:
	@echo "\nCleaning up..."
	@rm ./bin/*.bin	
  