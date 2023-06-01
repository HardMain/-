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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = nullptr;
    tableView = nullptr;
    addButton = nullptr;
    deleteButton = nullptr;
    button = nullptr;

    // Устанавливаем соединение с базой данных
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Qt/QT my projects/ARM/BD/mydatabase2.db");
    if (!db.open()) {
        qDebug() << "Cannot open database";
    }

    // Создаем таблицу "products"
    QSqlQuery query;
    query.exec("CREATE TABLE products (id INTEGER PRIMARY KEY AUTOINCREMENT, Наименование_товара TEXT, Количество INTEGER, Срок_годности TEXT)");
}

MainWindow::~MainWindow()
{
    if (ui) delete ui;
    if (model) delete model;
    if (tableView) delete tableView;
    if (addButton) delete addButton;
    if (deleteButton) delete deleteButton;
    if (button) delete button;
}

void MainWindow::on_pushButton_clicked()
{
    // Создаем модель таблицы и настраиваем ее
    model = new QSqlTableModel(this);
    model->setTable("products");
    model->setHeaderData(1, Qt::Horizontal, tr("Наименование товара"));
    model->setHeaderData(2, Qt::Horizontal, tr("Количество"));
    model->setHeaderData(3, Qt::Horizontal, tr("Срок годности"));
    model->select();

    // Создаем представление таблицы и настраиваем его
    tableView = new QTableView(this);
    tableView->setModel(model);

    // Добавляем кнопку "Удалить"
    deleteButton = new QPushButton("Удалить", this);
    deleteButton->setGeometry(0,300,70,30);

    // Соединяем кнопку "Удалить" с обработчиком нажатия
    connect(deleteButton, &QPushButton::clicked, this, [this]() {
        // Получаем список выбранных индексов
        QModelIndexList selectedIndexes = tableView->selectionModel()->selectedIndexes();
        if (!selectedIndexes.isEmpty()) {
            QSet<int> rows; // множество номеров строк, которые будут обновлены
            foreach (const QModelIndex &index, selectedIndexes) {
                if (!rows.contains(index.row())) {
                    rows.insert(index.row());
                }
            }
            // Обрабатываем все выбранные строки и зануляем значение в третьем столбце
            foreach (int row, rows) {
                QModelIndex index = model->index(row, 2); // индекс ячейки в третьем столбце
                model->setData(index, 0, Qt::EditRole); // зануляем значение
            }
        }
    });
    // Настраиваем размеры таблицы
    tableView->resizeColumnsToContents();
    this->resize(482, 330);
    tableView->resize(482, 300);

    // Создаем кнопку "Назад"
    button = new QPushButton("Назад", this);
    button->setGeometry(412, 300, 70, 30);

    // Соединяем кнопку "Назад" с обработчиком нажатия
    connect(button, &QPushButton::clicked, this, &MainWindow::onBackButtonClick);

    // Отображаем таблицу и кнопки
    tableView->show();
    deleteButton->show();
    button->show();

    //скрыть кнопки на главном экране
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();

    // Устанавливаем ширину столбцов
    tableView->setColumnWidth(0, 50);
    tableView->setColumnWidth(1, 180);
    tableView->setColumnWidth(2, 100);
    tableView->setColumnWidth(3, 130);
    }

void MainWindow::on_pushButton_2_clicked()
{
    // Создаем модель таблицы и настраиваем её
    model = new QSqlTableModel(this);
    model->setTable("products");
    model->removeColumns(2,2); // Удаляем столбцы Количество и Срок годности
    model->setHeaderData(1, Qt::Horizontal, tr("Наименование товара"));
    model->select();

    // Создаем представление таблицы и настраиваем его
    tableView = new QTableView(this);
    tableView->setModel(model);

    // Настраиваем размеры таблицы
    tableView->resizeColumnsToContents();
    this->resize(292, 330);
    tableView->resize(292, 300);

    // Устанавливаем ширину столбца
    tableView->setColumnWidth(0, 50);
    tableView->setColumnWidth(1, 220);

    // Добавляем кнопку "Добавить"
    addButton = new QPushButton("Добавить", this);
    addButton->setGeometry(0,300,70,30);
    tableView->setIndexWidget(model->index(model->rowCount(), 0), addButton);

    // Соединяем кнопку "Добавить" с обработчиком нажатия
    connect(addButton, &QPushButton::clicked, this, [this]() {
        model->insertRow(model->rowCount());
    });

    // Добавляем кнопку "Удалить"
    deleteButton = new QPushButton("Удалить", this);
    deleteButton->setGeometry(70,300,70,30);

    // Соединяем кнопку "Удалить" с обработчиком нажатия
    connect(deleteButton, &QPushButton::clicked, this, [this]() {
        // Получаем список выбранных индексов
        QModelIndexList selectedIndexes = tableView->selectionModel()->selectedIndexes();
        if (!selectedIndexes.isEmpty()) {
            // Удаляем все выбранные строки в цикле, начиная с последней
            for (int i = selectedIndexes.count() - 1; i >= 0; --i) {
                model->removeRow(selectedIndexes.at(i).row());
            }
        }
        model->setTable("products");
        model->removeColumns(2,2); // Удаляем столбцы Количество и Срок годности
        model->setHeaderData(1, Qt::Horizontal, tr("Наименование товара"));
        tableView->setColumnWidth(0, 50);
        tableView->setColumnWidth(1, 220);
        model->select();
    });

    // Создаем кнопку "Назад"
    button = new QPushButton("Назад", this);
    button->setGeometry(222, 300, 70, 30);

    // Соединяем кнопку "Назад" с обработчиком нажатия
    connect(button, &QPushButton::clicked, this, [&]() {
        // Настройки размеров окна
        this->resize(375, 260);

        // Закрываем текущую таблицу
        tableView->hide();
        button->hide();

        // Удаляем объекты
        if (tableView) delete tableView;
        if (button) delete button;
        if (addButton) delete addButton;
        if (deleteButton) delete deleteButton;
        if (model) delete model;
        model = nullptr;
        tableView = nullptr;
        deleteButton = nullptr;
        button = nullptr;
        addButton = nullptr;

        //отобразить кнопки на главном экране, после выхода из таблицы
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
    });

    // Отображаем таблицу и кнопку "Назад"
    tableView->show();
    addButton->show();
    deleteButton->show();
    button->show();

    //скрыть кнопки на главном экране
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
}

void MainWindow::on_pushButton_3_clicked()
{
    //скрыть кнопки на главном экране
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();

    // Добавляем кнопку "Заказать вручную"
    orderManually = new QPushButton("Ручной\nзаказ", this);
    QFont font("MS Shell Dlq 2", 12); // создаем объект QFont с указанным размером шрифта
    orderManually->setFont(font); // устанавливаем шрифт для кнопки
    orderManually->setGeometry(10,10,270,60);
    orderManually->show();

    // Добавляем кнопку "Заказать автоматически на завтра"
    orderAutomatically = new QPushButton("Автоматический\nзаказ", this);
    orderAutomatically->setFont(font); // устанавливаем шрифт для кнопки
    orderAutomatically->setGeometry(10,90,270,60);
    orderAutomatically->show();

    // Создаем кнопку "Назад"
    button = new QPushButton("Вернуться в главное меню", this);
    button->setFont(font); // устанавливаем шрифт для кнопки
    button->setGeometry(10, 170, 270, 30);
    button->show();

    // Соединяем кнопку "Назад" с обработчиком нажатия
    connect(button, &QPushButton::clicked, this, [&]() {
        // Настройки размеров окна
        this->resize(375, 260);

        // Удаляем объекты
        if (orderAutomatically) delete orderAutomatically;
        if (orderManually) delete orderManually;
        if (button) delete button;
        orderAutomatically = nullptr;
        orderManually = nullptr;
        button = nullptr;

        //отобразить кнопки на главном экране, после выхода из таблицы
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
    });

    // Настройки размеров окна
    this->resize(290, 210);

    //Соединяем кнопку "Заказать вручную" с обработчиком нажатия
    connect(orderManually, &QPushButton::clicked, this, &MainWindow::on_OrderManualButton_clicked);

    //Соединяем кнопку "Заказать автоматически" с обработчиком нажатия
    connect(orderAutomatically, &QPushButton::clicked, this, &MainWindow::on_orderAutomatically_clicked);
}

void MainWindow::on_pushButton_4_clicked()
{
    this->resize(535, 330);

    //скрыть кнопки на главном экране
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();

    QFont font("MS Shell Dlg 2", 10);

    nameLabel = new QLabel(this);
    nameLabel->setText("Продано за последний:");
    nameLabel->setFont(font);
    nameLabel->setGeometry(0,5,290,25);
    nameLabel->show();

// ----------------------------------------------------------------------
    dayButton = new QPushButton("День", this);
    dayButton->setGeometry(0,35,107,30);
    dayButton->show();

    connect(dayButton, &QPushButton::clicked, this, [&]()
    {
        if (model) delete model;
        if (tableView) delete tableView;
        if (addButton) delete addButton;
        if (deleteButton) delete deleteButton;
        model = nullptr;
        tableView = nullptr;
        addButton = nullptr;
        deleteButton = nullptr;

        QSqlQuery query;
        query.exec("CREATE TABLE day_sales (id INTEGER PRIMARY KEY AUTOINCREMENT, Наименование_товара TEXT, Количество_продаж INTEGER, Дата DATE)");

        // Отображаем таблицу в TableView
        model = new QSqlTableModel(this);
        model->setTable("day_sales");
        model->setHeaderData(1, Qt::Horizontal, tr("Наименование товара"));
        model->setHeaderData(2, Qt::Horizontal, tr("Количество продаж"));
        model->setHeaderData(3, Qt::Horizontal, tr("Дата продажи"));
        model->select();

        // Размещаем элементы на экране
        tableView = new QTableView(this);
        tableView->setModel(model);
        tableView->setGeometry(0, 65, 535, 235);
        tableView->setColumnWidth(0, 49);
        tableView->setColumnWidth(1, 180);
        tableView->setColumnWidth(2, 160);

        addButton = new QPushButton("Добавить", this);
        addButton->setGeometry(0, 300, 70, 30);

        deleteButton = new QPushButton("Удалить", this);
        deleteButton->setGeometry(70, 300, 70, 30);

        // Соединяем кнопки с обработчиками
        connect(addButton, &QPushButton::clicked, this, [&]()
        {
            int row = model->rowCount();
            model->insertRow(row);
        });

        connect(deleteButton, &QPushButton::clicked, this, [&]()
        {
            QItemSelectionModel *select = tableView->selectionModel();
            QModelIndexList selectedRows = select->selectedIndexes();

            for (const auto& index : selectedRows)
                model->removeRow(index.row());

            model->setTable("day_sales");
            model->setHeaderData(1, Qt::Horizontal, tr("Наименование товара"));
            model->setHeaderData(2, Qt::Horizontal, tr("Количество продаж"));
            model->setHeaderData(3, Qt::Horizontal, tr("Дата продажи"));
            model->select();

            tableView->setModel(model);
            tableView->setGeometry(0, 65, 535, 235);
            tableView->setColumnWidth(0, 49);
            tableView->setColumnWidth(1, 180);
            tableView->setColumnWidth(2, 160);
        });

        // Отображаем элементы на экране
        tableView->show();
        addButton->show();
        deleteButton->show();
    });
// ----------------------------------------------------------------------
    weekButton = new QPushButton("Неделю", this);
    weekButton->setGeometry(107,35,107,30);
    weekButton->show();

    connect(weekButton, &QPushButton::clicked, this, [&]()
    {
        if (model) delete model;
        if (tableView) delete tableView;
        if (addButton) delete addButton;
        if (deleteButton) delete deleteButton;
        model = nullptr;
        tableView = nullptr;
        addButton = nullptr;
        deleteButton = nullptr;

        QSqlQuery query;
        query.exec("CREATE TABLE week_sales (id INTEGER PRIMARY KEY AUTOINCREMENT, Наименование_товара TEXT, Количество_продаж INTEGER, Дата DATE)");

        // Отображаем таблицу в TableView
        model = new QSqlTableModel(this);
        model->setTable("week_sales");
        model->setHeaderData(1, Qt::Horizontal, tr("Наименование товара"));
        model->setHeaderData(2, Qt::Horizontal, tr("Количество продаж"));
        model->setHeaderData(3, Qt::Horizontal, tr("Дата продажи"));
        model->select();

        // Размещаем элементы на экране
        tableView = new QTableView(this);
        tableView->setModel(model);
        tableView->setGeometry(0, 65, 535, 235);
        tableView->setColumnWidth(0, 49);
        tableView->setColumnWidth(1, 180);
        tableView->setColumnWidth(2, 160);

        addButton = new QPushButton("Добавить", this);
        addButton->setGeometry(0, 300, 70, 30);

        deleteButton = new QPushButton("Удалить", this);
        deleteButton->setGeometry(70, 300, 70, 30);

        // Соединяем кнопки с обработчиками
        connect(addButton, &QPushButton::clicked, this, [&]()
        {
            int row = model->rowCount();
            model->insertRow(row);
        });

        connect(deleteButton, &QPushButton::clicked, this, [&]()
        {
            QItemSelectionModel *select = tableView->selectionModel();
            QModelIndexList selectedRows = select->selectedIndexes();

            for (const auto& index : selectedRows)
                model->removeRow(index.row());

            model->setTable("week_sales");
            model->setHeaderData(1, Qt::Horizontal, tr("Наименование товара"));
            model->setHeaderData(2, Qt::Horizontal, tr("Количество продаж"));
            model->setHeaderData(3, Qt::Horizontal, tr("Дата продажи"));
            model->select();

            tableView->setModel(model);
            tableView->setGeometry(0, 65, 535, 235);
            tableView->setColumnWidth(0, 49);
            tableView->setColumnWidth(1, 180);
            tableView->setColumnWidth(2, 160);
        });

        // Отображаем элементы на экране
        tableView->show();
        addButton->show();
        deleteButton->show();
    });
// ----------------------------------------------------------------------
    monthButton = new QPushButton("Месяц", this);
    monthButton->setGeometry(214,35,107,30);
    monthButton->show();

    connect(monthButton, &QPushButton::clicked, this, [&]()
    {
        if (model) delete model;
        if (tableView) delete tableView;
        if (addButton) delete addButton;
        if (deleteButton) delete deleteButton;
        model = nullptr;
        tableView = nullptr;
        addButton = nullptr;
        deleteButton = nullptr;

        QSqlQuery query;
        query.exec("CREATE TABLE month_sales (id INTEGER PRIMARY KEY AUTOINCREMENT, Наименование_товара TEXT, Количество_продаж INTEGER, Дата DATE)");

        // Отображаем таблицу в TableView
        model = new QSqlTableModel(this);
        model->setTable("month_sales");
        model->setHeaderData(1, Qt::Horizontal, tr("Наименование товара"));
        model->setHeaderData(2, Qt::Horizontal, tr("Количество продаж"));
        model->setHeaderData(3, Qt::Horizontal, tr("Дата продажи"));
        model->select();

        // Размещаем элементы на экране
        tableView = new QTableView(this);
        tableView->setModel(model);
        tableView->setGeometry(0, 65, 535, 235);
        tableView->setColumnWidth(0, 49);
        tableView->setColumnWidth(1, 180);
        tableView->setColumnWidth(2, 160);

        addButton = new QPushButton("Добавить", this);
        addButton->setGeometry(0, 300, 70, 30);

        deleteButton = new QPushButton("Удалить", this);
        deleteButton->setGeometry(70, 300, 70, 30);

        // Соединяем кнопки с обработчиками
        connect(addButton, &QPushButton::clicked, this, [&]()
        {
            int row = model->rowCount();
            model->insertRow(row);
        });

        connect(deleteButton, &QPushButton::clicked, this, [&]()
        {
            QItemSelectionModel *select = tableView->selectionModel();
            QModelIndexList selectedRows = select->selectedIndexes();

            for (const auto& index : selectedRows)
                model->removeRow(index.row());

            model->setTable("month_sales");
            model->setHeaderData(1, Qt::Horizontal, tr("Наименование товара"));
            model->setHeaderData(2, Qt::Horizontal, tr("Количество продаж"));
            model->setHeaderData(3, Qt::Horizontal, tr("Дата продажи"));
            model->select();

            tableView->setModel(model);
            tableView->setGeometry(0, 65, 535, 235);
            tableView->setColumnWidth(0, 49);
            tableView->setColumnWidth(1, 180);
            tableView->setColumnWidth(2, 160);
        });

        // Отображаем элементы на экране
        tableView->show();
        addButton->show();
        deleteButton->show();
    });
// ----------------------------------------------------------------------
    halfYearButton = new QPushButton("Полгода", this);
    halfYearButton->setGeometry(321,35,107,30);
    halfYearButton->show();

    connect(halfYearButton, &QPushButton::clicked, this, [&]()
    {
        if (model) delete model;
        if (tableView) delete tableView;
        if (addButton) delete addButton;
        if (deleteButton) delete deleteButton;
        model = nullptr;
        tableView = nullptr;
        addButton = nullptr;
        deleteButton = nullptr;

        QSqlQuery query;
        query.exec("CREATE TABLE halfYearButton (id INTEGER PRIMARY KEY AUTOINCREMENT, Наименование_товара TEXT, Количество_продаж INTEGER, Дата DATE)");

        // Отображаем таблицу в TableView
        model = new QSqlTableModel(this);
        model->setTable("halfYearButton");
        model->setHeaderData(1, Qt::Horizontal, tr("Наименование товара"));
        model->setHeaderData(2, Qt::Horizontal, tr("Количество продаж"));
        model->setHeaderData(3, Qt::Horizontal, tr("Дата продажи"));
        model->select();

        // Размещаем элементы на экране
        tableView = new QTableView(this);
        tableView->setModel(model);
        tableView->setGeometry(0, 65, 535, 235);
        tableView->setColumnWidth(0, 49);
        tableView->setColumnWidth(1, 180);
        tableView->setColumnWidth(2, 160);

        addButton = new QPushButton("Добавить", this);
        addButton->setGeometry(0, 300, 70, 30);

        deleteButton = new QPushButton("Удалить", this);
        deleteButton->setGeometry(70, 300, 70, 30);

        // Соединяем кнопки с обработчиками
        connect(addButton, &QPushButton::clicked, this, [&]()
        {
            int row = model->rowCount();
            model->insertRow(row);
        });

        connect(deleteButton, &QPushButton::clicked, this, [&]()
        {
            QItemSelectionModel *select = tableView->selectionModel();
            QModelIndexList selectedRows = select->selectedIndexes();

            for (const auto& index : selectedRows)
                model->removeRow(index.row());

            model->setTable("halfYearButton");
            model->setHeaderData(1, Qt::Horizontal, tr("Наименование товара"));
            model->setHeaderData(2, Qt::Horizontal, tr("Количество продаж"));
            model->setHeaderData(3, Qt::Horizontal, tr("Дата продажи"));
            model->select();

            tableView->setModel(model);
            tableView->setGeometry(0, 65, 535, 235);
            tableView->setColumnWidth(0, 49);
            tableView->setColumnWidth(1, 180);
            tableView->setColumnWidth(2, 160);
        });

        // Отображаем элементы на экране
        tableView->show();
        addButton->show();
        deleteButton->show();
    });
// ----------------------------------------------------------------------
    YearButton = new QPushButton("Год", this);
    YearButton->setGeometry(428,35,107,30);
    YearButton->show();

    connect(YearButton, &QPushButton::clicked, this, [&]()
    {
        if (model) delete model;
        if (tableView) delete tableView;
        if (addButton) delete addButton;
        if (deleteButton) delete deleteButton;
        model = nullptr;
        tableView = nullptr;
        addButton = nullptr;
        deleteButton = nullptr;

        QSqlQuery query;
        query.exec("CREATE TABLE Year_sales (id INTEGER PRIMARY KEY AUTOINCREMENT, Наименование_товара TEXT, Количество_продаж INTEGER, Дата DATE)");

        // Отображаем таблицу в TableView
        model = new QSqlTableModel(this);
        model->setTable("Year_sales");
        model->setHeaderData(1, Qt::Horizontal, tr("Наименование товара"));
        model->setHeaderData(2, Qt::Horizontal, tr("Количество продаж"));
        model->setHeaderData(3, Qt::Horizontal, tr("Дата продажи"));
        model->select();

        // Размещаем элементы на экране
        tableView = new QTableView(this);
        tableView->setModel(model);
        tableView->setGeometry(0, 65, 535, 235);
        tableView->setColumnWidth(0, 49);
        tableView->setColumnWidth(1, 180);
        tableView->setColumnWidth(2, 160);

        addButton = new QPushButton("Добавить", this);
        addButton->setGeometry(0, 300, 70, 30);

        deleteButton = new QPushButton("Удалить", this);
        deleteButton->setGeometry(70, 300, 70, 30);

        // Соединяем кнопки с обработчиками
        connect(addButton, &QPushButton::clicked, this, [&]()
        {
            int row = model->rowCount();
            model->insertRow(row);
        });

        connect(deleteButton, &QPushButton::clicked, this, [&]()
        {
            QItemSelectionModel *select = tableView->selectionModel();
            QModelIndexList selectedRows = select->selectedIndexes();

            for (const auto& index : selectedRows)
                model->removeRow(index.row());

            model->setTable("Year_sales");
            model->setHeaderData(1, Qt::Horizontal, tr("Наименование товара"));
            model->setHeaderData(2, Qt::Horizontal, tr("Количество продаж"));
            model->setHeaderData(3, Qt::Horizontal, tr("Дата продажи"));
            model->select();

            tableView->setGeometry(0, 65, 535, 235);
            tableView->setColumnWidth(0, 49);
            tableView->setColumnWidth(1, 180);
            tableView->setColumnWidth(2, 160);
        });

        // Отображаем элементы на экране
        tableView->show();
        addButton->show();
        deleteButton->show();
    });
// ----------------------------------------------------------------------
    // Создаем кнопку "Назад"
    button = new QPushButton("Назад", this);
    button->setGeometry(465, 300, 70, 30);
    button->show();

    // Соединяем кнопку "Назад" с обработчиком нажатия
    connect(button, &QPushButton::clicked, this, [&]() {
        // Настройки размеров окна
        this->resize(375, 260);

        // Удаляем объекты
        if (nameLabel) delete nameLabel;
        if (dayButton) delete dayButton;
        if (weekButton) delete weekButton;
        if (YearButton) delete YearButton;
        if (monthButton) delete monthButton;
        if (halfYearButton) delete halfYearButton;
        if (button) delete button;
        if (model) delete model;
        if (tableView) delete tableView;
        if (addButton) delete addButton;
        if (deleteButton) delete deleteButton;
        model = nullptr;
        tableView = nullptr;
        nameLabel = nullptr;
        dayButton = nullptr;
        weekButton = nullptr;
        YearButton = nullptr;
        monthButton = nullptr;
        halfYearButton = nullptr;
        button = nullptr;
        addButton = nullptr;
        deleteButton = nullptr;

        //отобразить кнопки на главном экране, после выхода из таблицы
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
    });

}
