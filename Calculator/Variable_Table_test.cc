/*
 * 
 *
 * 
 */
#include "Variable_Table.h"
#include <iostream>
#include <stdexcept>
using namespace std;

int main()
{
	Variable_Table x;
	x.insert("hej",5);
	x.insert("hesj",5);
	x.insert("heasdj",5);
	x.insert("heasdaj",5);
	x.insert("he113333367777j",5);
	x.set_value("hej", 1337);
	x.remove("hesj");
	cout << x.find("hej") << endl;
	cout << x.find("hesj") << endl;
	cout << "Skriv ut elit: " << x.get_value("hej") << endl;
	x.list(cout);	
	x.clear();
	x.list(cout);

	
	

}
