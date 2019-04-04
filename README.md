# ExpressionTree
For a given expression, you will build an expression tree and evaluate the result of the expression. The detailed steps are given below.
# Mandatory Guidelines
1) You will only use C++ functions.
2) You will incorporate the following C++ concepts in your program. a) pure
abstract class b) inheritance with virtual functions.
3) You will implement two virtual functions as shown below.
a. build_expression_tree(args) (5pts)
b. evaluate_expression_tree (args) (5pts)
4) You should use strtok function to parse the given postfix expression into
tokens. https://linux.die.net/man/3/strtok
5) You can use built-in functions like string manipulation functions. You should
not use built-in types (C++ STL) for vector, stack, lists and trees.

# Danny Ideas:

A virtual function a member function which is declared within base class and is re-defined (Overriden) by derived class.
https://en.wikibooks.org/wiki/C%2B%2B_Programming/Classes/Abstract_Classes/Pure_Abstract_Classes

# Notes:
- A postfix expression could of the following form “1 6 * 12 +”
- The in-order traversal of the expression tree would print 1 * 6 + 12
- The output of this evaluated expression would be “18”
- The postfix expression will contain only integer operands with the following
operations (+ - * /). You will follow regular arithmetic precedence for the
operations.
- The number of tokens in the input expression is limited to 100. Your input
expression can have floating point numbers as well.
- To use pure abstract classes, you can have a parent class which has the two
virtual functions. A second class would inherit the parent class and implement
the two virtual functions along with other auxiliary functions if needed.
