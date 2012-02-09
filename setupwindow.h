#ifndef SETUPWINDOW_H
#define SETUPWINDOW_H

#include <QWidget>

namespace Ui {
class SetupWindow;
}
class QCheckBox;
class QStringList;

class SetupWindow : public QWidget{
    Q_OBJECT
    
public:
    SetupWindow(QStringList *sl=0, QWidget *parent=0);
    ~SetupWindow();

    int getFrom();
    int getTo();
    int getTime();
    bool getOpValue(int at);    
    
private:
    Ui::SetupWindow *ui;
    QCheckBox **op;
    bool succeed;
    int n;

signals:
    void setupDone();
    void wrongInput();
};

#endif // SETUPWINDOW_H
