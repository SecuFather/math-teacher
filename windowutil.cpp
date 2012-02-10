#include "windowutil.h"

void changeLabelColor(QLabel *label, const QColor &color){
    QPalette palette = label->palette();
    palette.setColor(label->foregroundRole(), color);
    label->setPalette(palette);
}
