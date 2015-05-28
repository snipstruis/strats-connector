all: example.cc connector.h
	clang++ example.cc -o example -std=c++14 -g -Wall -Wextra
