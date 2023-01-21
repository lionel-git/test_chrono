
test_chrono: main.cpp
	g++ -std=c++20 -g -march=native -Wpedantic -lfmt main.cpp -o test_chrono

clean:
	rm -f test_chrono
