#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
using namespace std;
// Tokenizing a string using stringstream 
#include <bits/stdc++.h> 


struct Node {
	char value;
	Node* right;
	Node* left;
};

class LinkedListStack
{
	//Constructor
	LinkedListStack() {
		Node* topOfStack = nullptr;
		int size = 0;
	}
	//Deconstructor
	~LinkedListStack() {
		delete topOfStack;
	}

public:
	//Push to the top of stack
	void push(char Value) {

		//Creates new Node and pushes it
		Node* tempNode = new Node;

		tempNode->value = Value;
		tempNode->left = topOfStack;

		//New Top of Stack is this now
		topOfStack = tempNode;

		//Increment size of Stack
		size++;

	}
	Node* pop() {

		//Checks that we don't pop on empty stack
		if (topOfStack != NULL) {

			Node* tempNode = topOfStack;

			//Since Cpp Doesn't have auto garbage collecter, we have to delete it ourselves.
			delete topOfStack;

			topOfStack = tempNode->left;

			//Decrease Size of Stack
			size--;

			return tempNode;
		}
		else {
			printf("ERROR: TRYING TO POP EMPTY STACK\n");
		}

	}
private:
	Node* topOfStack;
	int size;
};



class Interface{

	public:
		virtual void build(string posfixList) = 0;
		//virtual int eval() = 0;
};

class ExpressionTree : public Interface{

	public:
		void build(string posfixList){
			cout << "This is the Given Input: " << posfixList << endl;


		}

};

int main(int argc, char* argv[]) {
	string input;
	int type = atoi(argv[1]);
	cout<<type;
	while(cin)
	{
		// Here you would be reading the file line by line
		getline(cin, input);
		cout<<"The input is: "<<input << endl;

		ExpressionTree Tree;

		Interface *Base = &Tree;

		Base->build(input);

		//Interface* Tree = new ExpressionTree();
		//Tree->build(input);
		/*
		Here evaluate the current line and printout the result
		Using the class you implemented
		*/
	}
	return 0;
}
