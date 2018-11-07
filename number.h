#ifndef NUMBER_H
#define NUMBER_H
#include <functional>
#include <iostream>
#include <cmath>


using namespace std;

enum numberErrors {IS_MEMORY};
enum NUMTYPE {DOUBLO, MEMO_SLOT};


struct number
{
    char memorySlot;
    double dValue;

    NUMTYPE dataType;
    number();
    number(double num);
    number(char memory);
    number(int num);
    ~number();
    void setType(NUMTYPE newType);
    NUMTYPE getType();

    void setData(double num);
    void setData(int num);
    void setData(char memory);

    bool hasMemory();

    double returnData();

    friend double operator+(const number& one, const number &two);
    friend double operator-(const number& one, const number &two);
    friend double operator*(const number& one, const number &two);
    friend double operator/(const number& one, const number &two);
    friend double operator^(const number& one, const number &two);
    friend ostream& operator<<(ostream &out, const number &toStream);


    number(const number &other);
    number& operator=(const number &other);
    private:
    void copy(const number &other);

};

number::~number()
{

}
void number::setType(NUMTYPE newType)
{
    dataType = newType;
}

NUMTYPE number::getType()
{
    return dataType;
}

number::number()
{
    dValue = double();
    memorySlot = char();

}
number::number(double num)
{
    setData(num);
}
number::number(int num)
{
    double temp = num;
    setData(temp);
}
number::number(char memory)
{
    setData(memory);
}
number::number(const number &other)
{
    copy(other);
}

number& number::operator=(const number &other)
{
    if(this != &other)
        copy(other);
    return *this;
}

void number::copy(const number &other)
{
    dataType = other.dataType;
    if(other.dataType == DOUBLO)
        dValue = other.dValue;
    else
        memorySlot = other.memorySlot;
}

void number::setData(double num)
{
    dValue = num;
    memorySlot = char();
    dataType = DOUBLO;
}

void number::setData(char memory)
{
    memorySlot = memory;
    dValue = double();
    dataType = MEMO_SLOT;
}

bool number::hasMemory()
{
    return dataType == MEMO_SLOT;
}

double number::returnData()
{
    if(dataType == DOUBLO)
        return dValue;
    else
        throw IS_MEMORY;
}

double operator+(const number& one, const number &two)
{
    return one.dValue + two.dValue;
}
double operator-(const number& one, const number &two)
{
    return one.dValue - two.dValue;
}
double operator*(const number& one, const number &two)
{
    return one.dValue * two.dValue;
}
double operator/(const number& one, const number &two)
{
    return one.dValue / two.dValue;
}
double operator^(const number& one, const number &two)
{
    return pow(one.dValue,two.dValue);
}
ostream& operator<<(ostream &out, const number &toStream)
{
    out << toStream.dValue;
    return out;
}

#endif // NUMBER_H
