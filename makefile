
test_chrono: main.cpp
	g++ -g -march=native -Wpedantic main.cpp -o test_chrono

clean:
	rm -f test_chrono

