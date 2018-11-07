#include "calculator.h"
#include "gstack.cpp"
#include "myqueue.cpp"

calculate::calculate()
{
  load();
}

void calculate::load()
{

  toDo['+'] = add;
  toDo['-'] = subtract;
  toDo['/'] = divide;
  toDo['^'] = power;
  toDo['*'] = multiply;
  path['+'] = regularCase;
  path['-'] = regularCase;
  path['/'] = regularCase;
  path['^'] = regularCase;
  path['*'] = regularCase;
  path[')'] = leftParen;
  path['('] = rightParen;
  castType[NUMBER] = printNumber;
  castType[OPERATOR] = printOperator;

}

bool calculate::comparison(math_operator &one, math_operator &two)
{
  return one > two;
}


void calculate::OrderOfOp(vector<math_operator> &toSort)
{
  sort(toSort.begin(), toSort.end(), [](math_operator &x, math_operator &y) {  return  x >= y;  });
}

void calculate::perform(vector<math_operator> &use)
{

  for(int i = 0; i < use.size();++i)
  {
      string temp = "";
      temp+=use[i].op;
      postfix+=(temp + " ");
      (this->*(toDo[use[i].op]))(tempNum.pop(),tempNum.pop());
  }
}

void calculate::burstPop()
{
  vector<math_operator> temp;
  tempOp.pop();
  while(!tempOp.peek().isThis('('))
  {
      temp.push_back(tempOp.pop());
  }
  tempOp.pop();
  perform(temp);
}

void calculate::regularPop(math_operator& toPlace)
{
  math_operator hold;
  while(tempOp.peek() >= toPlace && (tempOp.peek().op != '('))
  {
      if(toPlace.op == '^' && tempOp.peek().op == '^')
           break;
      hold = tempOp.pop();
      (this->*(toDo[hold.op]))(tempNum.pop(),tempNum.pop());
      postfix+=hold.op;
      postfix = postfix + " ";
  }
  tempOp.push(toPlace);
}

void calculate::endPop()
{
  vector<math_operator> temp;
  while(!tempOp.isEmpty())
  {
      temp.push_back(tempOp.pop());
  }
  OrderOfOp(temp);
  perform(temp);


}

string calculate::finalAnswer()
{
  postfix.clear();
  if(floor(tempNum.peek().dValue) == tempNum.peek().dValue)
      return (to_string((int)floor(tempNum.pop().dValue)));
  else
      return (to_string(tempNum.peek().dValue));
}

string calculate::rpnize(GStack<number> &operands, GStack<math_operator> &operators, myQueue<void*>& expression, myQueue<TOKEN_TYPES>& token)
{
  TOKEN_TYPES determiner;
  void *move;
  while(!expression.empty())
  {
      token.dequeue(determiner);
      expression.dequeue(move);
      if(determiner == NUMBER)
          printNumber(move,operands,operators);
      else
          printOperator(move,operands,operators);

  }
  endPop();
  return postfix;
}


void calculate::printNumber(void* toPrint, GStack<number>& operands, GStack<math_operator>& operators)
{
  number temp = *(static_cast<number*>(toPrint));
  tempNum.push(temp);
  if(floor(tempNum.peek().dValue) == tempNum.peek().dValue)
      postfix+= (to_string((int)floor(tempNum.peek().dValue)) + " ");
  else
      postfix+= (to_string(tempNum.peek().dValue) + " ");
}
void calculate::printOperator(void *toPrint, GStack<number>& operands, GStack<math_operator>& operators)
{
  math_operator temp = *(static_cast<math_operator*>(toPrint));
  (this->*(path[temp.op]))(operands, operators, temp);

}

void calculate::regularCase(GStack<number>& operands, GStack<math_operator>& operators, math_operator &temp)
{
  if((temp > tempOp.peek()) ||(tempOp.peek().op == '(' ) || tempOp.isEmpty())
      tempOp.push(temp);
  else
      regularPop(temp);
}
void calculate::leftParen(GStack<number> &operands, GStack<math_operator>& operators, math_operator &temp)
{
  tempOp.push(temp);
  withinParen.pop_back();
  burstPop();
}

void calculate::rightParen(GStack<number> &operands, GStack<math_operator>& operators, math_operator &temp)
{
  tempOp.push(temp);
  withinParen.push_back(true);
}

void calculate::add(const number &one, const number &two)
{
  tempNum.push(one + two);
}
void calculate::divide(const number &one, const number &two)
{
  tempNum.push(one / two);
}
void calculate::multiply(const number &one, const number &two)
{
  tempNum.push(one * two);
}
void calculate::subtract(const number &one, const number &two)
{
  tempNum.push(one - two);
}
void calculate:: power(const number &one, const number &two)
{
  tempNum.push(one ^ two);
}



