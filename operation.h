#ifndef OPERATION_H
#define OPERATION_H

#include <QString>

class Operation{
private:
    QString name;
public:
    Operation(QString name) : name(name) {}
    virtual QString getProblem(double &result, int from, int to)=0;
    inline QString getName()const{ return name; }

    static int random(int min, int max);
    static QString IntToStr(int x);
};

class Addition : public Operation{
public:
    Addition() : Operation("Addition"){}

    virtual QString getProblem(double &result, int from, int to);
};

#endif // OPERATION_H
