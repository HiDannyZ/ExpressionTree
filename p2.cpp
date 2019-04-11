#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
using namespace std;


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
	//~LinkedListStack() {
		//delete topOfStack;
	//}

public:
	//Takes a Character and push in a Node with the Character as its value.
	void push(Node* GivenNode) {


		//Creates new Node and pushes it
		GivenNode->left = topOfStack;


		//Increment size of Stack
		size++;

	}
	Node* pop() {

		//Checks that we don't pop on empty stack
		if (topOfStack != NULL) {


			Node* tempNode = topOfStack;

			//Since Cpp Doesn't have auto garbage collecter, we have to delete it ourselves.
			//delete topOfStack;

			topOfStack = tempNode->left;

			//Decrease Size of Stack
			size--;

			cout << "From Popped"	 << endl;
			return tempNode;
		}
		else {
			cout << ("ERROR: TRYING TO POP EMPTY STACK")<< endl;
		}

	}
private:
	Node* topOfStack;
	int size;

	//Allows This Class to be used in Expression Tree
	friend class ExpressionTree;
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

			//Stack
			LinkedListStack TheStack;

			char CharCopyOfStr[1024];
			
			strcpy(CharCopyOfStr, posfixList.c_str());

			char* SplitedCharacter;

			SplitedCharacter = strtok(CharCopyOfStr, " ");

			while(SplitedCharacter!= NULL){


				cout << "Before Operation: " << SplitedCharacter << endl;

				if((*SplitedCharacter == '+') || (*SplitedCharacter == '-') || (*SplitedCharacter == '*') || (*SplitedCharacter == '/')){
					cout << "Popped" << endl;

					Node* rightChildNode = TheStack.pop();
					Node* leftChildNode = TheStack.pop();

					Node* rootNode = new Node;

					rootNode->value = *SplitedCharacter;

					rootNode->right = rightChildNode;
					rootNode->left = leftChildNode;

					TheStack.push(rootNode);


					cout << "OUT" << endl;
					

					delete(rootNode);
				}
				else{
					cout << "Pushed!" << endl;
					Node* tempNode = new Node;

					tempNode->value = *SplitedCharacter;
					TheStack.push(tempNode);

					delete tempNode;
				}


				//Goes to next Character
				SplitedCharacter = strtok(NULL, " ");
			}
		}
};

int main(int argc, char* argv[]) {
	string input;
	int type = atoi(argv[1]);
	cout<<type << endl;

	while(cin)
	{
		// Here you would be reading the file line by line
		getline(cin, input);
		cout<<"The input is: "<< input << endl;

		ExpressionTree Tree;

		Interface *Base = &Tree;

		Base->build(input);
		/*
		Here evaluate the current line and printout the result
		Using the class you implemented
		*/
	}
	return 0;
}
