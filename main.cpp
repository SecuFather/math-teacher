#include <QApplication>
#include "mathteacher.h"

int main(int argc, char **argv){
    QApplication app(argc, argv);    
    MathTeacher mt;
    mt.show();
    return app.exec();
}
