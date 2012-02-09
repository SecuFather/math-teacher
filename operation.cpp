#include "operation.h"
#include <QTime>

QString Addition::getProblem(double &result, int from, int to){
    QString problem;
    int x = random(from, to);
    int y = random(from, to);

    if(x+y < from || x+y > to){
        x/=2;
        y/=2;
    }
    result = static_cast<double>(x+y);
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
