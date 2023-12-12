#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>
#include <QtWidgets/qtablewidget.h>
#include "BmApplication.h"
#include <vector>
#include <algorithm>
#include <QSqlDriver.h>

BmApplication::BmApplication(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // Указываем параметры соединения с СУБД ...
    db = QSqlDatabase::addDatabase("QPSQL");    //!< Диалект СУБД
    db.setHostName("localhost");                //!< имя или IP-адрес для подключения
    db.setPort(5432);                           //!< номер порта
    db.setUserName("postgres");                 //!< имя пользователя
    db.setPassword("e9e72ff6f8");            //!< пароль
    db.setDatabaseName("postgres");         //!< название БД

    bool ok = db.open();
    printf("connection: %s\n\n", ok ? "SUCCESS" : "FAILED");

    MyHandler h;

    db.driver()->subscribeToNotification("my_handler_ins");
    db.driver()->subscribeToNotification("my_handler_upd");
    QObject::connect(db.driver(), SIGNAL(notification(const QString&)), &h, SLOT(onNotify(const QString&)));

    // TODO: загружаем данные из БД (если есть), пример загрузки данных из БД ниже
    #if 1
    QSqlQuery sql(db);
    ok = sql.prepare("select id, launchx, boomx, angle, t0 from flight_tasks");
    if (ok) ok = sql.exec();
    if (ok) {
        for (int r = 0, ok = sql.first(); ok; ok = sql.next(), ++r) {
            int    id = sql.value(0).toInt();
            idTasks.push_back(id);
            double sx = sql.value("launchx").toDouble();    //!< можно вычитывать значения по имени столбца таблицы ...
            double bx = sql.value(2).toDouble();            //!< ... а можно по индексу
            double an = sql.value(3).toDouble();
            double t0 = sql.value(4).toDouble();

            // TODO: сохранение в объекте требуемого типа в памяти приложения и 
            // добавление на форму
            int rows = ui.twFlightTasks->rowCount();
            ui.twFlightTasks->insertRow(rows);

            QTableWidgetItem* cell;

            cell = new QTableWidgetItem(QString::number(id));
            ui.twFlightTasks->setItem(r, 0, cell);
                
            cell = new QTableWidgetItem(QString::number(sx));
            ui.twFlightTasks->setItem(r, 1, cell);

            cell = new QTableWidgetItem(QString::number(bx));
            ui.twFlightTasks->setItem(r, 2, cell);
 
            cell = new QTableWidgetItem(QString::number(t0));
            ui.twFlightTasks->setItem(r, 3, cell);
 
            cell = new QTableWidgetItem(QString::number(an));
            ui.twFlightTasks->setItem(r, 4, cell);
        }
    }
    #endif
}

void BmApplication::onAdd() {
    int rows = ui.twFlightTasks->rowCount();
    ui.twFlightTasks->insertRow(rows);
    // TODO: здесь можно добавлять ячейки в добавленную строку таблицы,
    // например:
    #if 0
    for (int c = 0, n = ui.twFlightTasks->columnCount(); c < n; ++c) {
        QTableWidgetItem* cell = new QTableWidgetItem("some-value " + QString::number(rows + 1) + "x" + QString::number(c + 1));
        ui.twFlightTasks->setItem(rows, c, cell);
    }
    #endif
}

void BmApplication::onDelete() {
    ui.twFlightTasks->setRowCount(ui.twFlightTasks->rowCount() - 1);
}

void BmApplication::onCalculate() {
    QSqlQuery sql(db);
    bool ok;

    for (int r = 0; r < ui.twFlightTasks->rowCount(); ++r) {
        if (std::find(idTasks.begin(), idTasks.end(), (ui.twFlightTasks->item(r, 0)->text()).toInt()) != idTasks.end()) {
            ok = sql.prepare("update flight_tasks set launchx = :lx, boomx = :bx, t0 = :t0, angle = :an where id = :_id");
            printf("prepare: %s\n\n", ok ? "OK, update" : "ERROR");

            sql.bindValue(":_id", ui.twFlightTasks->item(r, 0)->text());
        }
        else {
            ok = sql.prepare("insert into flight_tasks(launchy, boomy, type, launchx, boomx, t0, angle) values(0, 0, 1, :lx, :bx, :t0, :an)");
            printf("prepare: %s\n\n", ok ? "OK, insert" : "ERROR");
        }

        sql.bindValue(":lx", ui.twFlightTasks->item(r, 1)->text());
        sql.bindValue(":bx", ui.twFlightTasks->item(r, 2)->text());
        sql.bindValue(":t0", ui.twFlightTasks->item(r, 3)->text());
        sql.bindValue(":an", ui.twFlightTasks->item(r, 4)->text());

        ok = sql.exec();
        if (!ok) {
            printf("exec: %s , %s\n", ok ? "OK" : "ERROR", sql.lastError().databaseText().toLocal8Bit().constData());
        }
    }
}
