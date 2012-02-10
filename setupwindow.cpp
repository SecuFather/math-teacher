#include "setupwindow.h"
#include "ui_setupwindow.h"
#include "windowutil.h"
#include <QStringList>
#include <QCheckBox>
#include <QMessageBox>


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
        changeLabelColor(ui->fromLabel, Qt::red);
        emit wrongInput();        
    }else{
        changeLabelColor(ui->fromLabel, Qt::green);
    }
    return result;
}

int SetupWindow::getTo(){
    int result = ui->toEdit->text().toInt(&succeed);    
    if(!succeed){        
        changeLabelColor(ui->toLabel, Qt::red);
        emit wrongInput();
    }else{        
        changeLabelColor(ui->toLabel, Qt::green);
    }
    return result;
}

int SetupWindow::getTime(){
    int result = ui->timeEdit->text().toInt(&succeed);
    if(!succeed){
        changeLabelColor(ui->timeLabel, Qt::red);
        emit wrongInput();
    }else{
        changeLabelColor(ui->timeLabel, Qt::green);
    }
    return result;
}

bool SetupWindow::getOpValue(int at){
    return op[at]->isChecked();
}

