#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMainWindow>
#include <QSqlTableModel>
#include <QDesktopWidget>
#include <QSqlRecord>
#include <QSqlError>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QDateEdit>
#include <QMessageBox>

void MainWindow::onBackButtonClick()
{
    // Сохраняем изменения в базе данных
    model->submitAll();

    // Закрываем текущую таблицу и удаляем объекты
    if (model) delete model;
    if (tableView) delete tableView;
    if (deleteButton) delete deleteButton;
    if (button) delete button;
    model = nullptr;
    tableView = nullptr;
    deleteButton = nullptr;
    button = nullptr;

    //отобразить кнопки на главном экране, после выхода из таблицы
    ui->pushButton->show();
    ui->pushButton_2->show();
    ui->pushButton_3->show();
    ui->pushButton_4->show();

    // Настройки размеров окна
    this->resize(540,380);
}
