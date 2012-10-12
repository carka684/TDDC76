/*
 * TESTFIL FÖR EXPRESSION_TREE
 */

#include <iostream>
#include "Expression_Tree.h"
#include <cmath>

using namespace std;

int main()
{
	// TEST evaluate()
	cout << endl;
	double varde;
	Real* valueOne = new Real(2.3);
	Integer* valueTwo = new Integer(5);
	Integer* valueThree = new Integer(-6);
	Real* valueFour = new Real(3.14);
	Integer* valueFive = new Integer(2);
	Variable* variable = new Variable("x",7);
	Power* power = new Power(valueFour, valueFive);
	Plus* plus = new Plus(valueThree, power);
	Divide* divide = new Divide(valueTwo, plus);
	Times* times = new Times(valueOne, divide);
	Assign assign(variable, times);
	
	
	varde = assign.evaluate();
	
	cout << "TEST evaluate(): " << varde  << "    //Right value: "<< 2.3 * 5/(pow(3.14,2) + (-6))  << endl;
	
	// TEST get_postfix()
	cout << "TEST get_postfix(): " + assign.get_postfix() << endl;
	
	//TEST print()
	cout << "TEST print(): \n\n";
	assign.print(cout);
	cout << endl;
	
	//TEST clone()
	Expression_Tree* assignClone = assign.clone();
	cout << "TEST clone(): \n\n";
	
	assignClone->print(cout,0);
	cout << endl;
	
	//TEST Variable/Assign
	cout << "TEST Variable/Assign, print variable.get_value(): " << variable->str() << " " << variable->get_value() << endl;

	//TEST get_infix
	cout << "get_infix: " << assign.get_infix() << endl;
}
