#include "mainwindow.h"
#include "palette.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setPalette(a);
    MainWindow w;
    w.show();
    return a.exec();
}
