all:
	g++ -o test src/test.cpp -Iinc -larmadillo

clean:
	rm -f test
