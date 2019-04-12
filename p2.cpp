#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;


struct TNode {
	char value;
	TNode* right;
	TNode* left;
};

struct SNode {
	SNode* next;
	TNode* subTree;
};

//For use in Creating Tree
class LinkedListStack
{
	//Constructor
	LinkedListStack() {
		SNode* topOfStack = NULL;
		int size = 0;
	}
	//Deconstructor
	//~LinkedListStack() {
		//delete topOfStack;
	//}

	public:
		//Takes a Node and Pushes it into the stack
		void push(TNode* GivenNode) {
			//Creates new Node and pushes it
			SNode* newNode = new SNode;
			newNode->subTree = GivenNode;
			newNode->next = topOfStack;

			//Sets New Top of Stack as Most Recent Pushed in Node
			topOfStack = newNode;

			//Increment size of Stack
			size++;

		}
		TNode* pop() {

			//Checks that we don't pop on empty stack

			if (topOfStack != NULL) {

				//topOfStack = topOfStack->left;
				//return topOfStack;
				TNode* tempNode = topOfStack->subTree;
				

				//Since Cpp Doesn't have auto garbage collecter, we have to delete it ourselves.
				//delete topOfStack;

				topOfStack = topOfStack -> next;

				//Decrease Size of Stack
				size--;
				return tempNode;
			}
			else {
				cout << ("ERROR: TRYING TO POP EMPTY STACK")<< endl;
				return NULL;
			}


		}
	private:
		SNode* topOfStack;
		int size;

		//Allows This Class to be used in Expression Tree
		friend class ExpressionTree;
	};



class Interface{

	public:
		virtual TNode* build(string posfixList) = 0;
		virtual int eval(TNode* tree) = 0;
};

class ExpressionTree : public Interface{

	public:
		TNode* build(string posfixList){
			//cout << "This is the Given Input: " << posfixLisst << endl;

			//Stack
			LinkedListStack TheStack;


			//By Changing CharCopyOfStr[1024] to this one, There is no longer an error. Why? Was it because of Stackoverflow due to large allocation of size?
			// Can I delete This Once I'm done with it then? Though, online says that Delete should only be used with New and char *, not just char. Thanks!
			char CharCopyOfStr[posfixList.length()];
			
			strcpy(CharCopyOfStr, posfixList.c_str());

			char* SplitedCharacter;

			SplitedCharacter = strtok(CharCopyOfStr, " ");

			while(SplitedCharacter!= NULL){

				if((*SplitedCharacter == '+') || (*SplitedCharacter == '-') || (*SplitedCharacter == '*') || (*SplitedCharacter == '/')){

					TNode* rightChildNode = TheStack.pop();

					TNode* leftChildNode = TheStack.pop();

					TNode* rootNode = new TNode;

					rootNode->value = *SplitedCharacter;

					rootNode->right = rightChildNode;
					rootNode->left = leftChildNode;

					TheStack.push(rootNode);
					

				}
				else{
					TNode* tempNode = new TNode;

					tempNode->value = *SplitedCharacter;
					TheStack.push(tempNode);
					
				}

				//Goes to next Character
				SplitedCharacter = strtok(NULL, " ");
			}
			TNode* PostFixTree;
			PostFixTree = TheStack.pop();

			return PostFixTree;
		}

		int eval(TNode* Tree) {
			if (Tree == NULL){
				return 0;
			}

			if (Tree->left == NULL && Tree->right == NULL) {
				return (int) Tree->value;
			}

			int leftVal = eval(Tree->left);

			int rightVal = eval(Tree->right);

			// cout << Tree->value << " ";
			
			if ((Tree->value) == '+')
				return leftVal + rightVal;
			
			if (Tree->value == '-')
				return leftVal - rightVal;
			
			if (Tree->value == '*')
				return leftVal * rightVal;

			if (Tree->value == '/')
				return leftVal / rightVal;
			

		}
};

int main(int argc, char* argv[]) {
	string input;
	int type = atoi(argv[1]);
	cout<<type << endl;
	//while(cin)
	while(getline(cin, input))
	{
		// Here you would be reading the file line by line
		//getline(cin, input);
		
		if(input.length() == 0){
			cout << "We were given an empty Line" << endl;
			break;
		}
		cout<<"The input is: "<< input << endl;

		ExpressionTree Tree;

		Interface *Base = &Tree;

		TNode* Mytree= Base->build(input);

		int value = Base->eval(Mytree);
		cout << endl<< value << endl;

		/*
		Here evaluate the current line and printout the result
		Using the class you implemented
		*/
	}
	return 0;
}
