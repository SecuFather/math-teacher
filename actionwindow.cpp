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

void ActionWindow::setPrevious(QString prev, bool correct){
    if(correct){
        changeLabelColor(ui->prevLabel, Qt::green);
    }else{
        changeLabelColor(ui->prevLabel, Qt::red);
    }
    ui->prevLabel->setText(prev + ui->resultEdit->text());
    ui->resultEdit->setText("");
}

void ActionWindow::setStats(int correct, int all){
    ui->statsLabel->setText(QString::number(correct) + "/" + QString::number(all));
}

int ActionWindow::getResult(bool &b){
    int res = ui->resultEdit->text().toInt(&b);
    ui->resultEdit->setFocus();
    return res;
}
