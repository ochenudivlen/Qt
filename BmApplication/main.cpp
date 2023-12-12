#include "BmApplication.h"
#include <QtWidgets/QApplication>
#include <QSqlDriver.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

/*
    Worker* wrk = new Worker;       //!< создаем класс - обработчик, выполняющий свою работу в отдельном потоке
    QThread* thrOk = new QThread;   //!< создаем поток
    wrk->moveToThread(thrOk);       //!< передаём потоку владение объектом

    // "подписываем" слоты на сигналы
    QObject::connect(thrOk, &QThread::started, wrk, &Worker::handler);
    QObject::connect(wrk, &Worker::finished, thrOk, &QThread::quit);
    QObject::connect(wrk, &Worker::finished, wrk, &QObject::deleteLater);
    QObject::connect(thrOk, &QThread::finished, thrOk, &QObject::deleteLater);

    thrOk->start();
*/

/*
    MyHandler* mh = new MyHandler;
    QThread* thrOk = new QThread;
    mh->moveToThread(thrOk);

    QObject::connect(thrOk, &QThread::started, mh, &MyHandler::onNotify);
    QObject::connect(mh, &MyHandler::finished, thrOk, &QThread::quit);
    QObject::connect(mh, &MyHandler::finished, mh, &QObject::deleteLater);
    QObject::connect(thrOk, &QThread::finished, thrOk, &QObject::deleteLater);

    thrOk->start();
*/

/*
    // Указываем параметры соединения с СУБД ...
    QSqlDatabase db(QSqlDatabase::addDatabase("QPSQL"));    //!< Диалект СУБД
    db.setHostName("localhost");                //!< имя или IP-адрес для подключения
    db.setPort(5432);                           //!< номер порта
    db.setUserName("postgres");                 //!< имя пользователя
    db.setPassword("e9e72ff6f8");            //!< пароль
    db.setDatabaseName("postgres");         //!< название БД

    MyHandler h;

    bool ok = db.open();
    db.driver()->subscribeToNotification("my_handler_ins");
    db.driver()->subscribeToNotification("my_handler_upd");
    QObject::connect(db.driver(), SIGNAL(notification(const QString&)), &h, SLOT(onNotify(const QString&)));
*/

    BmApplication w;
    w.show();

    return a.exec();
}