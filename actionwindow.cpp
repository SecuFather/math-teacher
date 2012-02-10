#include "actionwindow.h"
#include "ui_actionwindow.h"
#include "windowutil.h"

ActionWindow::ActionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActionWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->checkButton, SIGNAL(clicked()), this, SIGNAL(check()));
    QObject::connect(ui->backButton, SIGNAL(clicked()), this, SIGNAL(goBack()));
}

ActionWindow::~ActionWindow()
{
    delete ui;
}

void ActionWindow::setProblem(QString problem){
    ui->problemLabel->setText(problem);
}

bool ActionWindow::setPrevious(QString prev, int result){
    bool ok;
    if(result == getResult(ok) && ok){
        changeLabelColor(ui->prevLabel, Qt::green);
    }else{
        ok = false;
        changeLabelColor(ui->prevLabel, Qt::red);
    }
    ui->prevLabel->setText(prev + QString::number(result));
    ui->resultEdit->setText("");
    return ok;
}

void ActionWindow::setStats(int correct, int all){
    ui->statsLabel->setText(QString::number(correct) + "/" + QString::number(all));
}

int ActionWindow::getResult(bool &b){
    int res = ui->resultEdit->text().toInt(&b);
    ui->resultEdit->setFocus();
    return res;
}
