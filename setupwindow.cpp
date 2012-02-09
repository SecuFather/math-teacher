#include "setupwindow.h"
#include "ui_setupwindow.h"
#include <QStringList>
#include <QCheckBox>
#include <QMessageBox>
#include <QPalette>

SetupWindow::SetupWindow(QStringList *sl, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetupWindow), succeed(true)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog);
    n = sl->count();
    op = new QCheckBox*[n];
    for(int i=0; i<n; ++i){
        op[i] = new QCheckBox();
        op[i]->setText(sl->at(i));
        ui->operationLayout->addWidget(op[i]);
        op[i]->setChecked(true);
    }
    QObject::connect(ui->goButton, SIGNAL(clicked()), this, SIGNAL(setupDone()));
}

SetupWindow::~SetupWindow(){
    for(int i=0; i<n; ++i){
    delete op[i];
    }
    delete[] op;
    delete ui;
}

int SetupWindow::getFrom(){
    int result = ui->fromEdit->text().toInt(&succeed);
    if(!succeed){
        ui->fromLabel->setStyleSheet("QLabel {color:red;}");
        emit wrongInput();        
    }else{
        ui->fromLabel->setStyleSheet("QLabel {color:green;}");
    }
    return result;
}

int SetupWindow::getTo(){
    int result = ui->toEdit->text().toInt(&succeed);
    if(!succeed){
        ui->toLabel->setStyleSheet("QLabel {color:red;}");
        emit wrongInput();
    }else{
        ui->toLabel->setStyleSheet("QLabel {color:green;}");
    }
    return result;
}

int SetupWindow::getTime(){
    int result = ui->timeEdit->text().toInt(&succeed);
    if(!succeed){
        ui->timeLabel->setStyleSheet("QLabel {color:red;}");
        emit wrongInput();
    }else{
        ui->timeLabel->setStyleSheet("QLabel {color:green;}");
    }
    return result;
}

bool SetupWindow::getOpValue(int at){
    return op[at]->isChecked();
}

