all:
	g++ src/*
	g++ main.cpp -I .src/ -o main

run:
	./main
