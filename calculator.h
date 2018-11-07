#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <iostream>
#include "parser.h"
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
using namespace std;

enum calculator_errors {ALGEBRA_BAD};

class calculate
{

  public:

  string postfix;
  calculate();

  void userInput(string data);
  void processInput();
  string rpnize(GStack<number> &operands, GStack<math_operator> &operators, myQueue<void*>& expression, myQueue<TOKEN_TYPES> &token);
  string finalAnswer();

  private:

  typedef void (calculate::*cFptr)(const number &one, const number &two);
  typedef void (calculate::*fCast)(void* toDereference, GStack<number> &operands, GStack<math_operator> &operators);
  typedef void (calculate::*fPath)(GStack<number> &operands, GStack<math_operator> &operators, math_operator &toJudge);

  vector<bool> withinParen;
  GStack<math_operator> tempOp;
  GStack<number>tempNum;

  map<char,fPath> path;
  map<char,cFptr> toDo;
  fCast castType[];

  void load();

  void add(const number &one, const number &two);
  void divide(const number &one, const number &two);
  void multiply(const number &one, const number &two);
  void subtract(const number &one, const number &two);
  void power(const number &one, const number &two);

  number& retreiveMemory();


  void regularCase(GStack<number>& operands, GStack<math_operator> &operators, math_operator &temp);
  void leftParen(GStack<number> &operands, GStack<math_operator> &operators,math_operator &temp);
  void rightParen(GStack<number> &operands, GStack<math_operator> &operators, math_operator &temp);


  void printNumber(void *toPrint, GStack<number> &operands, GStack<math_operator> &operators);
  void printOperator(void* toPrint, GStack<number> &operands, GStack<math_operator> &operators);

  void regularPop(math_operator& toPlace);
  void burstPop();
  void endPop();

  void OrderOfOp(vector<math_operator> &toSort);
  bool comparison(math_operator &one, math_operator &two);

  void perform(vector<math_operator> &use);

};
#endif // CALCULATOR_H


