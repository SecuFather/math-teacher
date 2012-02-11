#include "mathteacher.h"

#include <QStringList>
#include <QTime>
#include <QTimer>
#include <QFile>
#include <QTextStream>

#include "setupwindow.h"
#include "actionwindow.h"
#include "operation.h"

MathTeacher::MathTeacher() :    
    opCount(0),
    setupSucceed(true), sl(new QStringList()), aw(new ActionWindow()),
    opVector(QVector<Operation*>()), timer(new QTimer()), file(new QFile("stats.txt"))
{
    qsrand(QTime::currentTime().msecsTo(QTime(0,0)));

    addOp(new Addition());
    addOp(new Subtraction());
    addOp(new Multiplication());
    addOp(new Division());
    addOp(new Modulation());
    addOp(new SquareRoot());

    chosenOp = new int[opCount];
    goodAns = new int[opCount];
    allAns = new int[opCount];
    sw = new SetupWindow(sl);    
    loadStats();

    sw->setGeometry(500, 300, sw->width(), sw->height());
    aw->setGeometry(500, 300, aw->width(), aw->height());

    QObject::connect(sw, SIGNAL(setupDone()), this, SLOT(init()));
    QObject::connect(sw, SIGNAL(wrongInput()), this, SLOT(error()));
    QObject::connect(aw, SIGNAL(check()), this, SLOT(go()));
    QObject::connect(aw, SIGNAL(goBack()), this, SLOT(goBack()));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(go()));
}

MathTeacher::~MathTeacher(){
    saveStats();
    delete file;
    delete[] allAns;
    delete[] goodAns;
    delete[] chosenOp;
    for(int i=0; i<opCount; ++i){
        delete opVector.back();
        opVector.pop_back();
    }
    delete sw;
    delete aw;
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
    if(aw->setPrevious(problem, result)){
        ++correctAns;        
        ++goodAns[chosenOp[randO]];
    }
    randO = Operation::random(0, chosenOpCount);
    problem = opVector.at(chosenOp[randO])->getProblem(result, from, to);
    aw->setProblem(problem);
    aw->setStats(correctAns, ++ansCount);
    ++allAns[chosenOp[randO]];
    timer->start(time*1000);
}

void MathTeacher::goBack(){
    aw->hide();
    sw->show();
    saveStats();
}

void MathTeacher::addOp(Operation *op){
    opVector.push_back(op);
    sl->append(op->getName());
    ++opCount;
}

void MathTeacher::loadStats(){
    if(file->open(QFile::ReadOnly)){
        QTextStream ts(file);
        QString buf;
        for(int i=0; i<opCount; ++i){
            if((buf = ts.readLine()).isEmpty()){
                goodAns[i]=0;
                allAns[i]=0;
            }else{
                QStringList tmp = buf.split(" ");
                goodAns[i] = tmp.at(1).toInt();
                allAns[i] = tmp.at(2).toInt();
            }
        }
        file->close();
    }else{
        for(int i=0; i<opCount; ++i){
            goodAns[i]=0;
            allAns[i]=0;
        }
    }
}

void MathTeacher::saveStats(){
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    QString out;
    QTextStream ts(file);

    for(int i=0; i<opCount; ++i){
        out.append(sl->at(i) + " " +
                   QString::number(goodAns[i]) + " " +
                   QString::number(allAns[i]) + "\n");
    }
    ts<<out;
    file->close();

}

