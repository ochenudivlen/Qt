#include "BmApplication.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BmApplication w;
    w.show();
    return a.exec();
}
