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

void MainWindow::on_orderAutomatically_clicked()
{
    // Получить список товаров и количества продаж из таблицы day_sales
    QSqlQuery query("SELECT Наименование_товара, SUM(Количество_продаж) AS Количество_продаж FROM day_sales GROUP BY Наименование_товара");

    if (!query.next()) { // проверяем, есть ли строки для обновления
        QMessageBox::warning(this, "Ошибка!", "Добавьте статистику продаж!");
        return;
    }
    else
        query.seek(-1);

    while (query.next()) {
        QString productName = query.value(0).toString();
        int salesCount = query.value(1).toInt();

        // Обновить количество продаж для существующего товара или добавить новый товар
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE products SET Количество = Количество + :salesCount WHERE Наименование_товара = :productName");
        updateQuery.bindValue(":salesCount", salesCount);
        updateQuery.bindValue(":productName", productName);
        if (!updateQuery.exec()) {
            qWarning() << "Не удалось обновить запись в таблице products" << updateQuery.lastError().text();
            continue;  // перейти к следующей записи
        }
        if (updateQuery.numRowsAffected() == 0) {
            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO products (Наименование_товара, Количество, Срок_годности) VALUES (:productName, :salesCount, '')");
            insertQuery.bindValue(":productName", productName);
            insertQuery.bindValue(":salesCount", salesCount);
            if (!insertQuery.exec()) {
                qWarning() << "Не удалось добавить запись в таблицу products" << insertQuery.lastError().text();
            }
        }
    }
    QMessageBox::information(this, "Успешно!", "Заказ успешно выполнен!");
}
