#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(375,260);
    w.setWindowTitle("Товаровед");
    w.setStyleSheet("QMainWindow { background-color: yellow; }");
    w.show();
    return a.exec();
}
