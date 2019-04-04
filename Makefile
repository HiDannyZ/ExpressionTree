all: p2


p2: g++ -o out p2.cpp -lm

test: all
	./out < test.txt

clean:
	rm out 