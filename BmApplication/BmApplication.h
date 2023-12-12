#pragma once

#include <QtWidgets/QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QThread>
#include <iostream>
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
    //Вектор id полётных заданий
    std::vector<int> idTasks;
};

class Worker : public QObject {
    Q_OBJECT

signals:
    void finished();

public slots:
    void handler() {
        std::cout << "Hello! " << (int)QThread::currentThreadId() << " " << std::this_thread::get_id() << std::endl;
        emit finished();
    }
};

class MyHandler : public QObject {
    Q_OBJECT

public slots:
    void onNotify(QString p) {
        std::cout << "notifies: " << p.toLocal8Bit().constData() << std::endl;
    }
};