all: p2

p2: p2.cpp
	g++ -o out p2.cpp -lm

test: all
	./out 1 < test.txt
extra_credit: all
	./out 2 < test.txt
clean:
	rm out
