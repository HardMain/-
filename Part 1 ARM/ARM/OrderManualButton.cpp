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

void MainWindow::on_OrderManualButton_clicked()
{
    //скрыть кнопки на втором экране
    orderAutomatically->hide();
    orderManually->hide();
    button->hide();

    this->resize(290,210);

    QFont font("MS Shell Dlq 2", 10);

    nameLabel = new QLabel(this);
    nameLabel->setText("Наименование товара:");
    nameLabel->setStyleSheet("background-color: Pink; color: Black;");
    nameLabel->setFont(font);
    nameLabel->setGeometry(0,5,290,20);
    nameLabel->show();

    nameEdit = new QLineEdit(this);
    nameEdit->setGeometry(0,30,290,20);
    nameEdit->show();

    quantityLabel = new QLabel(this);
    quantityLabel->setText("Количество:");
    quantityLabel->setStyleSheet("background-color: Pink; color: Black;");
    quantityLabel->setFont(font);
    quantityLabel->setGeometry(0,60,290,20);
    quantityLabel->show();

    quantitySpinBox = new QSpinBox(this);
    quantitySpinBox->setGeometry(0,85,290,20);
    quantitySpinBox->setMaximum(10000);
    quantitySpinBox->show();

    deliveryDateLabel = new QLabel(this);
    deliveryDateLabel->setText("Ожидаемая дата доставки:");
    deliveryDateLabel->setStyleSheet("background-color: Pink; color: Black;");
    deliveryDateLabel->setFont(font);
    deliveryDateLabel->setGeometry(0, 115, 290, 20);
    deliveryDateLabel->show();

    dateEdit = new QDateEdit(this);
    dateEdit->setGeometry(0,140,130,20);
    dateEdit->setCalendarPopup(true);
    dateEdit->show();

    makeOrderButton = new QPushButton("Заказать", this);
    makeOrderButton->setFont(font);
    makeOrderButton->setStyleSheet("background-color: #cdffdf; color: black;");
    makeOrderButton->setGeometry(95, 180, 100, 30);
    makeOrderButton->show();

    button2 = new QPushButton("Назад", this);
    button2->setFont(font); // устанавливаем шрифт для кнопки
    button2->setStyleSheet("background-color: black; color: white;");
    button2->setGeometry(230, 180, 60, 30);
    button2->show();

    connect(button2, &QPushButton::clicked, this, [&]() {
        // Удаляем объекты
        if (nameLabel) delete nameLabel;
        if (nameEdit) delete nameEdit;
        if (quantityLabel) delete quantityLabel;
        if (quantitySpinBox) delete quantitySpinBox;
        if (deliveryDateLabel) delete deliveryDateLabel;
        if (dateEdit) delete dateEdit;
        if (makeOrderButton) delete makeOrderButton;
        if (button2) delete button2;
        nameLabel = nullptr;
        nameEdit = nullptr;
        quantityLabel = nullptr;
        quantitySpinBox = nullptr;
        deliveryDateLabel = nullptr;
        dateEdit = nullptr;
        makeOrderButton = nullptr;
        button2 = nullptr;

        //отобразить кнопки на главном экране, после выхода из таблицы
        orderAutomatically->show();
        orderManually->show();
        button->show();

        this->resize(440,380);
    });

    // Добавляем запись в таблицу "products"
    connect(makeOrderButton, &QPushButton::clicked, this, [&]() {
        // Считываем данные из полей формы
        QString productName = nameEdit->text();
        int productQuantity = quantitySpinBox->value();

        if (productName.isEmpty() || productQuantity == 0)
            QMessageBox::warning(this, "Ошибка", "Заполните все поля для заказа товара!");
        else
        {
            QSqlQuery query;
            query.prepare("SELECT * FROM products WHERE Наименование_товара=:productName");
            query.bindValue(":productName", productName);

            if (!query.exec())
            {
                qDebug() << "Ошибка при выполнении запроса:" << query.lastError().text();
                QMessageBox::warning(this, "Ошибка", "Не удалось выполнить запрос к базе данных.");
            }
            else
            {
                if (query.next())
                {
                    // Товар с таким наименованием уже есть в базе данных
                    int existingQuantity = query.value("Количество").toInt();
                    int newQuantity = existingQuantity + productQuantity;

                    query.prepare("UPDATE products SET Количество=:newQuantity WHERE Наименование_товара=:productName");
                    query.bindValue(":newQuantity", newQuantity);
                    query.bindValue(":productName", productName);

                    if (!query.exec())
                    {
                        qDebug() << "Ошибка при выполнении запроса:" << query.lastError().text();
                        QMessageBox::warning(this, "Ошибка", "Не удалось обновить количество товара в базе данных.");
                    } else
                        QMessageBox::information(this, "Успешно!", "Заказ успешно выполнен!");
                }
                else
                    QMessageBox::warning(this, "Ошибка", "Добавьте товар в базу данных!");
             }
        }
    });
}
