/*
 * 6.088 IAP 2010
 * Assignment #5: Inheritance and Polymorphism
 *
 * Expression.h
 * Header file for the abstract base class Expression
 */

#ifndef EXPRESSION
#define EXPRESSION

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
/*
 * Expression
 */
class Expression {

 public:
  virtual ~Expression() {}

  // Returns the result of evaluating this expression.
  virtual float eval() const = 0;

  // Prints the expression. DO NOT evaluate before printing.
  virtual void print() const = 0;
};

class fExpression:public Expression
{
public:
    fExpression(){}
    ~fExpression(){}
    fExpression(string str):mstr(str){}
    virtual float eval() const
    {
        return 0.0;
    }

    virtual void print() const
    {
        cout << this->mstr << endl;

    }
private:
    string mstr;

};

#endif  // EXPRESSION
