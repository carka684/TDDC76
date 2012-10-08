/*
 * Calculator.h
 */
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "Expression.h"
#include <iosfwd>

/**
 * Calculator: klass f�r att l�sa in, lagra och bearbeta enkla aritmetiska
 * uttryck. F�r att anv�nda kalylatorn - skapa ett Calculator-objekt och 
 * anropa run().
 *
 * Anm: flyttkonstruktorn och flyttilldelningsoperatorn genereras inte om
 * en destruktor, kopieringskonstruktor eller kopieringstilldelnings-
 * operator deklareras ("deletea" aldrig dessa tv�!).
 */
class Calculator
{
public:
   Calculator() = default;
   Calculator(const Calculator&) = delete;
   ~Calculator() = default;
   Calculator& operator=(const Calculator&) = delete;
   // Flyttkonstruktor och flyttilldening genereras inte.

   void run();

private:
   static const std::string valid_command_;

   Expression current_expression_;

   char command_;

   static void print_help();

   void get_command();
   bool valid_command() const;
   void execute_command();

   void read_expression(std::istream&);
};

#endif
