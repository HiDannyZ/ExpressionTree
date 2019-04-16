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
		friend class PostOrder_ExpressionTree;
	};



class Interface{

	public:
		virtual TNode* build(string List) = 0;
		virtual int eval(TNode* tree) = 0;
		virtual void printExpression(TNode* tree) = 0;

};

class PostOrder_ExpressionTree : public Interface{

	public:
		TNode* build(string List){
			//cout << "This is the Given Input: " << posfixLisst << endl;

			//Stack
			LinkedListStack TheStack;


			//By Changing CharCopyOfStr[1024] to this one, There is no longer an error. Why? Was it because of Stackoverflow due to large allocation of size?
			// Can I delete This Once I'm done with it then? Though, online says that Delete should only be used with New and char *, not just char. Thanks!
			char CharCopyOfStr[List.length()];
			
			strcpy(CharCopyOfStr, List.c_str());

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

			if (((Tree->left) == NULL) && ((Tree->right) == NULL)) {

				return ((int) Tree->value - ((int)48));
			}

			int leftVal = eval(Tree->left);

			int rightVal = eval(Tree->right);

			// cout << Tree->value << " ";
			
			if ((Tree->value) == '+'){
				return leftVal + rightVal;
			}
			
			if (Tree->value == '-'){
				return leftVal - rightVal;
			}
			
			if (Tree->value == '*'){
				return leftVal * rightVal;
			}

			if (Tree->value == '/'){
				return leftVal / rightVal;
			}

		}

		void printExpression(TNode* Tree){

			if(Tree == NULL){
				return;
			}

			printExpression(Tree->left);

			cout << Tree->value << " ";

			printExpression(Tree->right);

		}

		string toPostfix(string infix){

			LinkedListStack operatorStack;
			std::string postfix;

			char CharCopyOfStr[infix.length()];
			
			strcpy(CharCopyOfStr, infix.c_str());

			char* SplitedCharacter;

			SplitedCharacter = strtok(CharCopyOfStr, " ");

			while(SplitedCharacter!= NULL){

				if((*SplitedCharacter == '+') || (*SplitedCharacter == '-') || (*SplitedCharacter == '*') || (*SplitedCharacter == '/')){

					//Needs to check if there's anything in the stack
					//If not just automatically push the operator into it
					if(operatorStack.topOfStack == NULL){

						TNode* opNode = new TNode;
						opNode->value = *SplitedCharacter;
						operatorStack.push(opNode);

					}
					else{

						//Just a temp for the top of the stack
						TNode* topNode = operatorStack.topOfStack ->subTree;


						//Chcking to see if incoming operator's precedence is greater than the top of stack's
						//If it is add to the stack
						if(precedenceCheck(*SplitedCharacter) > precedenceCheck(topNode->value)){
							TNode* opNode = new TNode;
							opNode->value = *SplitedCharacter;
							operatorStack.push(opNode);
						}

						//If the incoming ooperator precedence is less than the top of stack one
						//Pop stack and append the operator to string, run the whole precedence check operatation again
						//This only going to happen at most 2 times
						else if(precedenceCheck(*SplitedCharacter) < precedenceCheck(topNode->value)){

							TNode* temp = operatorStack.pop();
							postfix += temp->value;
		

							//rerunning the precedence check for the new topOfStack
							if(operatorStack.topOfStack == NULL){

								TNode* opNode = new TNode;
								opNode->value = *SplitedCharacter;
								operatorStack.push(opNode);

							}
							else{

								//Just a temp for the top of the stack
								TNode* topNode = operatorStack.topOfStack ->subTree;
								
								if(precedenceCheck(*SplitedCharacter) > precedenceCheck(topNode->value)){
									TNode* opNode = new TNode;
									opNode->value = *SplitedCharacter;
									operatorStack.push(opNode);
								}

								else{
									TNode* temp = operatorStack.pop();
									postfix += temp->value;
									TNode* opNode = new TNode;
									opNode->value = *SplitedCharacter;
									operatorStack.push(opNode);
								}

							}
					}
						//case when they're equal in precedence: pop the top of the stack, add it to string and push new op
						else{
							TNode* temp = operatorStack.pop();
							postfix += temp->value;
							TNode* opNode = new TNode;
							opNode->value = *SplitedCharacter;
							operatorStack.push(opNode);
						}
					}
				}

				else{
					postfix += *SplitedCharacter;
				}
		
			}
		}

		int precedenceCheck(char op){

			if(op == '+' || op == '-'){
				return 1;
			}
			if(op == '*' || op == '/'){
				return 2;
			}
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
			break;
		}
		cout<<"The input is: "<< input << endl;
		cout << input[input.length()-1]<< endl;

		//Predefine the Tree
		PostOrder_ExpressionTree Tree;
		Interface *Base = &Tree;

		//check to see if the input is in infix notation: if in infix notation, change it to postfix then eval
		bool isInfix = false;
		if (input[input.length()-1] != '+' &&  input[input.length()-1] != '-' && input[input.length()-1] != '*' && input[input.length()-1] != '/'){
			isInfix = true;
			input = Tree.toPostfix(input);
			cout << input << endl;
		}
		

		TNode* Mytree= Base->build(input);

		cout<< "The inorder traversal is: ";
		Base->printExpression(Mytree);
		cout << endl;

		int value = Base->eval(Mytree);
		cout << "The output of the expression is: "<< value << endl << endl;

		/*
		Here evaluate the current line and printout the result
		Using the class you implemented
		*/
	}
	return 0;
}
