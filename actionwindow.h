#ifndef ACTIONWINDOW_H
#define ACTIONWINDOW_H

#include <QWidget>

namespace Ui {
class ActionWindow;
}

class ActionWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit ActionWindow(QWidget *parent = 0);
    ~ActionWindow();

    void setProblem(QString problem);
    void setPrevious(QString prev, bool correct);
    void setStats(int correct, int all);

    double getResult(bool &b);
private:
    Ui::ActionWindow *ui;

signals:
    void goBack();
    void check();
};

#endif // ACTIONWINDOW_H
