#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


//    //  qus.bind(QHostAddress("127.0.0.1"), PORT+1);
//        QByteArray msg = "Hello world!";





    return a.exec();
}
