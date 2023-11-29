#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>
#include <QtWidgets/qtablewidget.h>
#include "BmApplication.h"

BmApplication::BmApplication(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // ��������� ��������� ���������� � ���� ...
    db = QSqlDatabase::addDatabase("QPSQL");    //!< ������� ����
    db.setHostName("localhost");                //!< ��� ��� IP-����� ��� �����������
    db.setPort(5432);                           //!< ����� �����
    db.setUserName("postgres");                 //!< ��� ������������
    db.setPassword("your-password");            //!< ������
    db.setDatabaseName("your-db-name");         //!< �������� ��

    bool ok = db.open();
    printf("connection: %s\n\n", ok ? "SUCCESS" : "FAILED");

    // TODO: ��������� ������ �� �� (���� ����), ������ �������� ������ �� �� ����
    #if 0
    QSqlQuery sql(db);
    bool ok = sql.prepare("select launchx, boomx, angle, t0 from flight_tasks");
    if (ok) ok = sql.exec();
    if (ok) {
        for (ok = sql.first(); ok; ok = sql.next()) {
            double sx = sql.value("launchx").toDouble();    //!< ����� ���������� �������� �� ����� ������� ������� ...
            double bx = sql.value(1).toDouble();            //!< ... � ����� �� �������
            double an = sql.value(2).toDouble();
            double t0 = sql.value(3).toDouble();
            // TODO: ���������� � ������� ���������� ���� � ������ ���������� � 
            // ���������� �� �����
        }
    }
    #endif
}

void BmApplication::onAdd() {
    int rows = ui.twFlightTasks->rowCount();
    ui.twFlightTasks->insertRow(rows);
    // TODO: ����� ����� ��������� ������ � ����������� ������ �������,
    // ��������:
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
    bool ok = sql.prepare("insert into flight_tasks(launchy, boomy, type, launchx, boomx, t0, angle) values(0, 0, 1, :lx, :bx, :t0, :an)");
    printf("prepare: %s\n\n", ok ? "OK" : "ERROR");

    for (int r = 0; r < ui.twFlightTasks->rowCount(); ++r) {
        sql.bindValue(":lx", ui.twFlightTasks->item(r, 0)->text());
        sql.bindValue(":bx", ui.twFlightTasks->item(r, 1)->text());
        sql.bindValue(":t0", ui.twFlightTasks->item(r, 2)->text());
        sql.bindValue(":an", ui.twFlightTasks->item(r, 3)->text());

        ok = sql.exec();
        if (!ok) {
            printf("exec: %s , %s\n", ok ? "OK" : "ERROR", sql.lastError().databaseText().toLocal8Bit().constData());
        }
    }
}
