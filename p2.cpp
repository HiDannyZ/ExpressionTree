#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Node{
	int data;
	Node* next;
};

class LinkedListStack
{
	//Constructor
	LinkedListStack(){
		topOfStack = nullptr;
		size = 0;
	}
	//Deconstructor
	~LinkedListStack(){
		delete topOfStack;
	}

	public:
		//Push to the top of stack
		void push(int Value){

			//Creates new Node and pushes it
			Node* tempNode = new Node;

			tempNode->data = Value;
			tempNode->next = topOfStack;

			//New Top of Stack is this now
			topOfStack = tempNode;

			//Increment size of Stack
			size++;

		}
		Node* pop(){

			//Checks that we don't pop on empty stack
			if(topOfStack != NULL){

				Node* tempNode = topOfStack;

				//Since Cpp Doesn't have auto garbage collecter, we have to delete it ourselves.
				delete topOfStack;

				topOfStack = tempNode.next;

				//Decrease Size of Stack
				size--;

				return tempNode;
			}
			else{
				printf("ERROR: TRYING TO POP EMPTY STACK\n");
			}

		}
	private:
		Node* topOfStack;
		int size;
};



int main() {
	string input;
	while(cin)
	{
		// Here you would be reading the file line by line
		getline(cin, input);
		cout<<"The input is: "<<input;
		/*
		Here evaluate the current line and printout the result
		Using the class you implemented
		*/
	}
	return 0;
}

