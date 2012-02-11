#ifndef OPERATION_H
#define OPERATION_H

#include <QString>

class Operation{
private:
    QString name;
public:
    Operation(QString name) : name(name) {}
    virtual QString getProblem(int &result, int from, int to)=0;
    inline QString getName()const{ return name; }

    static int random(int min, int max);
    static QString IntToStr(int x);
    static void swap(int& x, int& y);
    static int abs(int x);
};

class Addition : public Operation{
public:
    Addition() : Operation("Addition"){}

    virtual QString getProblem(int &result, int from, int to);
};

class Subtraction : public Operation{
public:
    Subtraction() : Operation("Subtraction"){}

    virtual QString getProblem(int &result, int from, int to);
};

class Multiplication : public Operation{
public:
    Multiplication() : Operation("Multiplication"){}

    virtual QString getProblem(int &result, int from, int to);
};

class Division : public Operation{
public:
    Division() : Operation("Division"){}

    virtual QString getProblem(int &result, int from, int to);
};

class Modulation : public Operation{
public:
    Modulation() : Operation("Modulation"){}

    virtual QString getProblem(int &result, int from, int to);
};

class SquareRoot : public Operation{
public:
    SquareRoot() : Operation("Square-Root"){}

    virtual QString getProblem(int &result, int from, int to);
};

#endif // OPERATION_H
