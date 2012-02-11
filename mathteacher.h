#ifndef MATHTEACHER_H
#define MATHTEACHER_H

#include <QObject>
#include <QVector>

class QStringList;
class SetupWindow;
class ActionWindow;
class Operation;
class QTimer;
class QMainWindow;
class QFile;

class MathTeacher : public QObject{
    Q_OBJECT
private:
    int from, to, time, opCount, chosenOpCount, *chosenOp, correctAns, ansCount, *goodAns, *allAns;
    bool setupSucceed;
    int result, randO;
    QString problem;
    QStringList *sl;    
    SetupWindow *sw;
    ActionWindow *aw;
    QVector<Operation*> opVector;
    QTimer *timer;    
    QFile *file;

public:
    MathTeacher();
    ~MathTeacher();

    void show();
    void addOp(Operation *op);
    void loadStats();
    void saveStats();

public slots:
    void init();
    void error();
    void go();
    void goBack();
};


#endif // MATHTEACHER_H
