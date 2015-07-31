#include "hos_main.h"
#include <QApplication>
#include<QtSql/QSqlDatabase>
#include"login.h"
QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
int main(int argc, char *argv[])
{
    db.setHostName("localhost");//设置数据库主机名
    db.setDatabaseName("hos");//设置数据库名
    db.setUserName("root");//设置账号
    db.setPassword("240286024");//设置密码
    if(!db.open())//如果打开数据库失败
        return false;
    QApplication a(argc, argv);
    login *log=new login;
    log->show();
    return a.exec();
}
