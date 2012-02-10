#include "operation.h"
#include <QTime>
#include <cmath>

QString Addition::getProblem(int &result, int from, int to){
    QString problem;
    int x = random(from, to);
    int y = random(from, to);

    while(x+y < from || x+y > to){
        if(abs(y)>abs(x)){
            swap(x, y);
        }
        x/=2;
    }
    result = x+y;
    problem.append(IntToStr(x) + " + " + IntToStr(y) + " = ");
    return problem;
}

int Operation::random(int min, int max){    
    return min + (qrand()%(max-min));
}

QString Operation::IntToStr(int x){
    if(x < 0){
        return "(" + QString::number(x) + ")";
    }
    return QString::number(x);
}

void Operation::swap(int &x, int &y){
    int t = x;
    x = y;
    y = t;
}

int Operation::abs(int x){
    return (x>0 ? x : -x);
}

QString Subtraction::getProblem(int &result, int from, int to){
    QString problem;
    int x = random(from, to);
    int y = random(from, to);

    while(x-y < from || x-y > to){
        if(abs(y)>abs(x)){
            swap(x, y);
        }
        x/=2;
    }
    result = x-y;
    problem.append(IntToStr(x) + " - " + IntToStr(y) + " = ");
    return problem;
}

QString Multiplication::getProblem(int &result, int from, int to){
    QString problem;
    int x = random(from, to);
    int y = random(from, to);

    while(x*y < from || x*y > to){
        if(abs(y)>abs(x)){
            swap(x, y);
        }
        x = (x<0 ? -sqrt(-x) : sqrt(x));
    }
    result = x*y;
    problem.append(IntToStr(x) + " * " + IntToStr(y) + " = ");
    return problem;
}

QString Division::getProblem(int &result, int from, int to){
    QString problem;
    int p = random(0, 2);
    int x = random(4, from*(p-1)+to*p)*(1-p*2);
    p = random(0, 2);
    int y = random(1, abs(x)/2)*(1-p*2);

    result = x/y;
    problem.append(IntToStr(x) + " / " + IntToStr(y) + " = ");
    return problem;
}

QString Modulation::getProblem(int &result, int from, int to){
    QString problem;
    int p = random(0, 2);
    int x = random(4, from*(p-1)+to*p)*(1-p*2);
    p = random(0, 2);
    int y = random(1, abs(x)/2)*(1-p*2);

    result = x%y;
    problem.append(IntToStr(x) + " % " + IntToStr(y) + " = ");
    return problem;
}

QString SquareRoot::getProblem(int &result, int from, int to){
    QString problem;
    result = random(2, sqrt(abs(to))+1);
    int x = result*result + random(0, result);

    problem.append("sqrt( " +  IntToStr(x) + " ) = ");
    return problem;
}
