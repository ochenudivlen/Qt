#pragma once

#include <QtWidgets/QMainWindow>
#include <QtSql/QSqlDatabase>
#include "ui_BmApplication.h"

class BmApplication : public QMainWindow
{
    Q_OBJECT

public:
    BmApplication(QWidget *parent = Q_NULLPTR);

public slots:
    void onAdd();
    void onDelete();
    void onCalculate();

private:
    Ui::BmApplicationClass ui;
    QSqlDatabase db;
};
