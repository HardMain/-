#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QTableView>
#include <QPushButton>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QSqlRecord>
#include <QSqlError>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QDateEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void onBackButtonClick();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_OrderManualButton_clicked();

    void on_orderAutomatically_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;

    QSqlTableModel *model;
    QTableView *tableView;
    QPushButton *button;
    QPushButton *button2;
    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* orderManually;
    QPushButton* orderAutomatically;

    QLabel* nameLabel;
    QLineEdit* nameEdit;

    QLabel* quantityLabel;
    QSpinBox* quantitySpinBox;

    QLabel* deliveryDateLabel;
    QDateEdit* dateEdit;

    QPushButton* makeOrderButton;

    QPushButton *dayButton;
    QPushButton *weekButton;
    QPushButton *monthButton;
    QPushButton *halfYearButton;
    QPushButton *YearButton;
};

#endif // MAINWINDOW_H
