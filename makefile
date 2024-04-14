# Variables
file_name = $(file_name)

# Rules
all: build run

build:
	g++ -std=c++20 -Wall -pedantic tests/$(file_name).cpp -O3

run:
ifdef OS
	./a.exe
else
	./a.out
endif

clean:
	rm -f a.out
