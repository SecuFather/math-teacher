#include "mathteacher.h"

#include <QStringList>
#include <QTime>
#include <QTimer>

#include "setupwindow.h"
#include "actionwindow.h"
#include "operation.h"

MathTeacher::MathTeacher() :
    opCount(1), chosenOp(new int[opCount]),
    setupSucceed(true), sl(new QStringList()), aw(new ActionWindow()),
    opVector(QVector<Operation*>()), timer(new QTimer())
{
    qsrand(QTime::currentTime().msecsTo(QTime(0,0)));
    addOp(new Addition());
    sw = new SetupWindow(sl);

    QObject::connect(sw, SIGNAL(setupDone()), this, SLOT(init()));
    QObject::connect(sw, SIGNAL(wrongInput()), this, SLOT(error()));
    QObject::connect(aw, SIGNAL(check()), this, SLOT(go()));
    QObject::connect(aw, SIGNAL(goBack()), this, SLOT(goBack()));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(go()));
}

MathTeacher::~MathTeacher(){
    delete[] chosenOp;
    for(int i=0; i<opCount; ++i){
        delete opVector.back();
        opVector.pop_back();
    }
    delete aw;
    delete sw;
    delete sl;
}

void MathTeacher::show(){
    sw->show();
}

void MathTeacher::init(){
    from = sw->getFrom();
    to = sw->getTo();
    time = sw->getTime();

    if(setupSucceed){
        chosenOpCount=0;
        for(int i=0; i<opCount; ++i){
            if(sw->getOpValue(i)){
                chosenOp[chosenOpCount++] = i;
            }
        }
        if(chosenOpCount){
            ansCount = -1;
            correctAns = 0;
            go();
            sw->hide();
            aw->show();
        }
    }else{
        setupSucceed = true;
    }
}

void MathTeacher::error(){
    setupSucceed = false;
}

void MathTeacher::go(){
    bool ok;
    double ans = aw->getResult(ok);
    aw->setPrevious(problem, (ans == result) && ok);
    if((ans == result) && ok){
        ++correctAns;
    }
    problem = opVector.at(chosenOp[Operation::random(0, chosenOpCount)])->getProblem(result, from, to);
    aw->setProblem(problem);
    aw->setStats(correctAns, ++ansCount);
    timer->start(time*1000);
}

void MathTeacher::goBack(){
    aw->hide();
    sw->show();
}

void MathTeacher::addOp(Operation *op){
    opVector.push_back(op);
    sl->append(op->getName());
}