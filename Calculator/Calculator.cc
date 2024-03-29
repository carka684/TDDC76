/*
 * Calculator.cc
 */
#include "Calculator.h"
#include "Expression.h"
#include "Calculator_Error.h"
#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

Calculator::Calculator()
{
	variable_table = new Variable_Table;
}

Calculator::~Calculator()
{
	delete variable_table;
	variable_table = nullptr;
}

const string Calculator::valid_command_("?HUBPTSIRAVXLN");

/**
 * run: Huvudfunktionen f�r kalkylatorn. Skriver ut hj�lpinformation
 * och l�ser sedan sedan in ett kommando i taget och utf�r det.
 */
void
Calculator::
run()
{
   cout << "V�lkommen till Kalkylatorn!\n\n";
   print_help();

   do 
   {
      try 
      {
	 get_command();
	 if (valid_command()) execute_command();
      }
      catch (const exception& e) 
      {
	 cout << e.what() << '\n';
      }
      // Of�rutsedda undantag avbryter programk�rningen, via main().
   }
   while (command_ != 'S');
}

/**
 * print_help: Skriver ut kommandorepertoaren.
 */
void
Calculator::
print_help()
{
   cout << "  H, ?  Skriv ut denna information\n";
   cout << "  U     Mata in ett nytt uttryck\n";
   cout << "  B     Ber�kna aktuellt uttryck\n";
   cout << "  B n   Ber�kna uttryck n\n";
   cout << "  P     Visa aktuellt uttryck som postfix\n";
   cout << "  P n   Visa uttryck n som postfix\n";
   cout << "  I     Visa aktuellt uttryck som infix\n";
   cout << "  I n   Visa uttryck n som infix\n";
   cout << "  L     Lista alla uttryck som infix\n";
   cout << "  T     Visa aktuellt uttryck som tr�d\n";
   cout << "  T n   Visa uttryck n som tr�d\n";
   cout << "  N     Visa antal lagrade uttryck\n";
   cout << "  A n   G�r uttryck n till aktuellt uttryck\n";
   cout << "  R     Radera aktuellt uttryck\n";
   cout << "  R n   Radera uttryck n\n";
   cout << "  V     Lista alla variabler\n";
   cout << "  X     Radera alla variabler\n";
   cout << "  S     Avsluta kalkylatorn\n";
}

/**
 * get_command: L�ser ett kommando (ett tecken), g�r om till versal och lagrar
 * kommandot i medlemmen command_, f�r vidare behandling av andra operationer. 
 * Ingen kontroll g�rs om det skrivits mer, i s� fall skr�p, p� kommandoraden.
 */
void
Calculator::
get_command()
{
   cout << ">> ";
   cin >> command_;
   position = 0;
   if(cin.peek() != '\n')
   {
   	string str;
   	cin >> str;
   	for(unsigned int i = 0; i < str.size(); ++i)
   	{
   		if(!isdigit(str[i]))
   		{
   			throw calculator_error("Andra argumentet m�ste best� av siffror");
   		}
   	}
   	
   	stringstream ss(str);
   	ss >> position;
   	if((position <= 0) or (position > (int) expression_vector.size()))
	{
   		throw calculator_error("Positionen �r f�r stor eller f�r liten");
	}
   	

   }
   command_ = toupper(command_);
}

/**
 * valid_command: Kontrollerar om kommandot som finns i medlemmen command_
 * tillh�r den till�tna kommandorepertoraren och returnerar antingen true
 * (giltigt kommando) eller false (ogiltigt kommando).
 */
bool
Calculator::
valid_command() const
{
   if (valid_command_.find(command_) == string::npos)
   {
      cout << "Otill�tet kommando: " << command_ << "\n";
      return false;
   }

   return true;
}

/**
 * execute_command: Utf�r kommandot som finns i medlemmen command_. Kommandot
 * f�ruts�tts ha kontrollerats med valid_command() och allts� �r ett giltigt 
 * kommando.
 */
void
Calculator::
execute_command()
{
   if (command_ == 'H' || command_ == '?')
      print_help();
   else if (command_ == 'U')
      read_expression(cin);
   else if (command_ == 'B' and position > 0)
   {
      cout << expression_vector[position-1].evaluate() << "\n";
   }
   else if (command_ == 'B')
      cout << current_expression_.evaluate() << "\n";
   else if (command_ == 'P' and position > 0)
   {
      cout << expression_vector[position-1].get_postfix() << "\n";
   }
   else if (command_ == 'P')
      cout << current_expression_.get_postfix() << "\n";
   else if (command_ == 'T' and position > 0)
   {
      expression_vector[position-1].print_tree(cout);
   }
   else if (command_ == 'T')
      current_expression_.print_tree(cout);
   else if (command_ == 'I' and position > 0)
   {
      cout << expression_vector[position-1].get_infix() << "\n";
   }
   else if (command_ == 'I')
      cout << current_expression_.get_infix() << "\n";
   else if (command_ == 'L')
      print_variables();
   else if (command_ == 'N')
      cout << expression_vector.size() << "\n";      
   else if (command_ == 'A' and position > 0)
   {
      current_expression_=expression_vector[position - 1];
      current_position_= position - 1;
   }
   else if (command_ == 'R' and position > 0)
   {
      erase_expression(position);
   }
   else if (command_ == 'R')
      erase_expression();
   else if (command_ == 'V')
      variable_table->list(cout);
   else if (command_ == 'X')
      variable_table->clear();
   else if (command_ == 'S')
      cout << "Kalkylatorn avlutas, v�lkommen �ter!\n";
   else
      cout << "Detta ska inte h�nda!\n";
}

/**
 * read_expression: l�ser ett infixuttryck fr�n instr�mmen is och ger detta 
 * till funktionen make_expression() som returnerar ett objekt av typen 
 * Expression, vilket lagras som "aktuellt uttryck" i current_expression_.
 */
void
Calculator::
read_expression(istream& is)
{
   string infix;

   is >> ws;

   if (getline(is, infix))
   {
      current_expression_ = make_expression(infix, variable_table);
      expression_vector.push_back(current_expression_);
      current_position_ = expression_vector.size() - 1;
   }
   else
   {
      cout << "Felaktig inmatning!\n";
   }
}

void Calculator::print_variables() const
{
	if(expression_vector.size() == 0)
	{
		throw calculator_error("Det finns inga uttryck definierade");
	}
	else
	{
		for(unsigned int i = 0; i < expression_vector.size(); ++i)
		{
			cout << expression_vector[i].get_infix() << "\n";
		}
	}
}

void Calculator::erase_expression()
{
	if(expression_vector.size() == 0)
	{
		throw calculator_error("Det finns inga mer uttryck");
	}
	expression_vector.erase(expression_vector.begin() + current_position_);
	current_position_ = expression_vector.size() - 1;
	current_expression_ = expression_vector.back();
}

void Calculator::erase_expression(int pos)
{
	if(pos - 1 == current_position_)
	{
		erase_expression();
	}
	else
	{
		expression_vector.erase(expression_vector.begin() + pos - 1);
		
		if(current_position_ > pos - 1)
		{
			current_position_ = current_position_ - 1;	
		}
	}

}
