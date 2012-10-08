/*
 * Expression_Tree.cc    2012-10-05
 */
#include "Expression_Tree.h"
#include <string>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <typeinfo>
#include <iostream>
#include <cmath>


// INKLUDERA FÖR DET SOM KOMMER ATT ANVÄNDAS I DENNA FIL!
using namespace std;

// SEPARATA DEFINITIONER FÖR FÖR EXPRESSION_TREE-KLASSERNA DEFINIERAS HÄR.



// ----------------- Binary_Operator ------------------

Binary_Operator::Binary_Operator(Expression_Tree* newLeftNode, Expression_Tree* newRightNode)
{
	leftNode = newLeftNode;
	rightNode = newRightNode;
}

Binary_Operator::~Binary_Operator()
{
	delete leftNode;
	delete rightNode;
	leftNode = nullptr;
	rightNode = nullptr;
}

void Binary_Operator::print(ostream& os, int depth) const
{	
	rightNode->print(os, depth+2);
	os << setw(depth+2) << "/" << endl << setw(depth+1) << str() << endl << setw(depth+2)<< "\\" << endl;
	leftNode->print(os,depth+2);
}

string Binary_Operator::get_postfix() const
{
	return (leftNode->get_postfix() + " " + rightNode->get_postfix() + " " + str());
}

// ----------------- Operand ------------------

void Operand::print(ostream& os, int depth) const
{
	string valueString = str();
	os << setw(depth+1+valueString.size()) << valueString << endl;
}

string Operand::get_postfix() const
{
	return str();
}


// ----------------- Plus ------------------

Plus::Plus(Expression_Tree* newLeftNode, Expression_Tree* newRightNode)
	: Binary_Operator(newLeftNode, newRightNode)
{
}

Expression_Tree* Plus::clone() const
{
	return new Plus(*this);
}
double Plus::evaluate()
{ 
	return (leftNode->evaluate() + rightNode->evaluate());
}

string Plus::str() const
{
	return "+";
}

// ----------------- Minus ------------------

Minus::Minus(Expression_Tree* newLeftNode, Expression_Tree* newRightNode)
	: Binary_Operator(newLeftNode, newRightNode)
{	
}

Expression_Tree* Minus::clone() const
{
	return new Minus(*this);
}

double Minus::evaluate()
{ 
	return (leftNode->evaluate() - rightNode->evaluate());
}

string Minus::str() const
{
	return "-";
}

// ----------------- Times ------------------

Times::Times(Expression_Tree* newLeftNode, Expression_Tree* newRightNode)
	: Binary_Operator(newLeftNode, newRightNode)
{
}

Expression_Tree* Times::clone() const
{
	return new Times(*this);
}
double Times::evaluate()
{ 
	return (leftNode->evaluate() * rightNode->evaluate());
}

string Times::str() const
{
	return "*";
}

// ----------------- Divide ------------------

Divide::Divide(Expression_Tree* newLeftNode, Expression_Tree* newRightNode)
	: Binary_Operator(newLeftNode, newRightNode)
{
}

Expression_Tree* Divide::clone() const
{
	return new Divide(*this);
}
double Divide::evaluate()
{ 
	return (leftNode->evaluate() / rightNode->evaluate());
}

string Divide::str() const
{
	return "/";
}

// ----------------- Power ------------------

Power::Power(Expression_Tree* newLeftNode, Expression_Tree* newRightNode)
	: Binary_Operator(newLeftNode, newRightNode)
{
}

Expression_Tree* Power::clone() const
{
	return new Power(*this);
}
double Power::evaluate()
{ 
	return pow(leftNode->evaluate(), rightNode->evaluate());
}

string Power::str() const
{
	return "^";
}


// ----------------- Assign ------------------

// Måste vara en variabel i leftNode, annars är tilldelningen fel!
Assign::Assign(Expression_Tree* newLeftNode, Expression_Tree* newRightNode)
	: Binary_Operator(newLeftNode, newRightNode)
{
	if(isalpha(leftNode->str()[0]))
	{
		cout << "TEST Assign's leftnode is a variable" << endl;
	}
	else
	{
		//Ska ge fel! FIXA SENARE!
		cout << "ERROR: Assign's leftnode is not a variable" << endl;
	}
}



Expression_Tree* Assign::clone() const
{
	return new Assign(*this);
}
double Assign::evaluate()
{
	Variable* leftVariable = dynamic_cast<Variable*>(leftNode);
	double rightNodeValue = rightNode->evaluate(); 
	leftVariable->set_value(rightNodeValue);
	return rightNodeValue;
}

string Assign::str() const
{
	return "=";
}


// ----------------- Integer ------------------

Integer::Integer(int newValue)
{
	value = newValue;
}

Expression_Tree* Integer::clone() const
{
	return new Integer(*this);
}
		
double Integer::evaluate()
{
	return value;
}

string Integer::str() const
{
	stringstream ss;
	ss << value;
	string str = ss.str();
	return str;
}

// ----------------- Real ------------------

Real::Real(double newValue)
{
	value = newValue;
}

Expression_Tree* Real::clone() const
{
	return new Real(*this);
}
		
double Real::evaluate()
{
	return value;
}

string Real::str() const
{
	stringstream ss;
	ss << value;
	string str = ss.str();
	return str;
}

// ----------------- Variable ------------------

Variable::Variable(string newVariableName, int newValue)
{
	value = newValue;
	variableName = newVariableName;
}

Expression_Tree* Variable::clone() const
{
	return new Variable(*this);
}
		
double Variable::evaluate()
{
	return value;
}

string Variable::str() const
{
	return variableName;
}

double Variable::get_value() const
{
	return value;
}

void Variable::set_value(double newValue)
{
	value = newValue;
}
