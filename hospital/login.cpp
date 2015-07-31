#include "login.h"
#include "ui_login.h"
#include"hos_main.h"
#include <QMessageBox>
#include <QString>
#include<QtSql/QSqlQuery>
#include"chgpwd.h"
login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->usr_pwd->setEchoMode(QLineEdit::Password);
    ui->usr_name->setText("");
   // ui->graphicsView->setPalette();
}

login::~login()
{
    delete ui;
}


void login::on_login_it_clicked()
{
    bool success=false;//标识是否成功打开数据库
    if(!db.open()){//打开不成功
        QMessageBox::about(this,"Message","connect error!");
        return;
    }
    else{
        QString user=ui->usr_name->text().trimmed();//获取用户名
        QString pwd=ui->usr_pwd->text().trimmed();//用户密码
        if(""==user)//若输入的用户名空
            QMessageBox::about(this,"Message","Please input user name");
        else if(""==pwd)//若输入的密码为空
            QMessageBox::about(this,"Msssage","Please input password");
        else{
           QSqlQuery query;
           if(query.exec("select*from TMS")){//从保存用户名和密码的表TMS中选择元组
               while(query.next()){
                   if(user==query.value(0).toString() && pwd==query.value(1).toString()){
                       success=true;//注value从0开始。
                       db.close();
                       break;
                   }
               }
               if(success){//用户名和密码匹配成功
                   hos_main *w=new hos_main;
                   w->show();
                   this->close();
               }
               else
                   QMessageBox::about(this,"Message","Logining error");
           }
        }
    }
}

void login::on_exit_clicked()
{
    this->close();
}

void login::on_chgnpwd_clicked()
{
  chgpwd *pwd=new chgpwd;
  pwd->show();
  //this->close();
}
