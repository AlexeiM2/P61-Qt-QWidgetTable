#include "principal.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    Principal w;
    w.show();
    return a.exec();
}
