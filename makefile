all: build run
 
build:
	g++ -std=c++20 tests/${file_name}.cpp -O3

run:
	./a.out

clean:
	rm *.out