#include <iosfwd>
#include <stdexcept>
#include <string>
#include <map>
#include <iostream>
#include "Variable_Table.h"
#include "Variable_Table_error.h"

using namespace std;

void Variable_Table::insert(string name, double value)
{
	variableMap.insert(pair<string,double>(name,value));
}

void Variable_Table::remove(string name)
{
	if(!find(name))
	{
		throw variable_table_error("Det finns ingen variabel i tabellen med det namnet");
	}
	else
	{
		variableMap.erase(name);
	}
}

bool Variable_Table::find(string name) const
{
	return variableMap.count(name);
}

// SKA ÄNDRAS BEROENDE PÅ HUR VAD VÅRT BUS ERROR BEROR PÅ. I NULÄGET BEHÖVS EJ
// IF-SATSEN
void Variable_Table::set_value(string name, double value)
{
	if(find(name))
	{
		map<string,double>::iterator it = variableMap.find(name);
		it->second = value;
	}
	else
	{
		insert(name, value);
	}
}

double Variable_Table::get_value(string name)
{	
	if(!find(name))
	{
		throw variable_table_error("Det finns ingen variabel i tabellen med det namnet");
	}
	else
	{
		map<string,double>::iterator it = variableMap.find(name);
		return it->second;
	}
}

void Variable_Table::list(ostream& os)
{
	if(empty())
	{
		throw variable_table_error("Det finns inga variabler definierade");
	}
	else
	{
		map<string,double>::iterator it;
		for( it=variableMap.begin() ; it != variableMap.end(); it++ )
		{
			os << (*it).first << " = " << (*it).second << endl;	
		}
	}
}

void Variable_Table::clear()
{
	variableMap.clear();
}

bool Variable_Table::empty() const
{
	return variableMap.empty();
}
