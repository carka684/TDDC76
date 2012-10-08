/*
 * TESTFIL FÖR EXPRESSION
 */

#include <iostream>
#include "Expression_Tree.h"
#include "Expression.h"
#include <cmath>

using namespace std;

int main()
{	
	Expression X = make_expression("5+3*12-2^3");
	Expression Y = make_expression("3+7");
	swap(X,Y);
	X.print_tree(cout);
	Y.print_tree(cout);
}
