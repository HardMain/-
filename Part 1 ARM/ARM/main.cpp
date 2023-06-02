#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(540,380);
    w.setWindowTitle("Товаровед");
    w.setStyleSheet("QMainWindow { background-color: yellow; }");
    QIcon icon("C:/Users/Владимир/Desktop/iconfinder_253_Shopping_Cart_Product_2124194-_1_.png");
    w.setWindowIcon(icon);
    w.show();

    return a.exec();
}
