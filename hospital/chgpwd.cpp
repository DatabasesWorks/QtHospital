#include "chgpwd.h"
#include "ui_chgpwd.h"
#include<QMessageBox>
#include<QString>
#include<QSqlQuery>
#include<QDebug>
#include"hos_main.h"
#include"login.h"
chgpwd::chgpwd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chgpwd)
{
    ui->setupUi(this);
    ui->usr_name->setText("");
    ui->old_pwd->setEchoMode(QLineEdit::Password);
    ui->new_pwd->setEchoMode(QLineEdit::Password);
    ui->confirm_pwd->setEchoMode(QLineEdit::Password);
}

chgpwd::~chgpwd()
{
    delete ui;
}

void chgpwd::on_affirm_clicked()
{
    if(!db.open())
        QMessageBox::about(this,"Message","connect to dd error");
    else{
        QString user=ui->usr_name->text().trimmed();
        QString old_pd=ui->old_pwd->text().trimmed();
        QString new_pd=ui->new_pwd->text().trimmed();
        QString confirm_pd=ui->confirm_pwd->text().trimmed();
        if(user.isEmpty()||old_pd.isEmpty()||new_pd.isEmpty()||confirm_pd.isEmpty()){
           QMessageBox::information(this,"提示","请输入完整信息!",QMessageBox::Ok);
           return;
          }
        if(new_pd!=confirm_pd){
            QMessageBox::information(this,"提示","密码不一致!",QMessageBox::Ok);
          }
        QSqlQuery query;
        query.prepare("select * from TMS where TMS_USER=:user and TMS_PWD=:pwd");

        query.bindValue(":user",user);
        query.bindValue(":pwd",old_pd);
        query.exec();
        if(query.next()){
            query.clear();
            query.prepare("update TMS set TMS_PWD=:new_pd where TMS_USER=:user");
            query.bindValue(":user",user);
            query.bindValue(":new_pd",new_pd);
            if(query.exec()){
                //qDebug()<< "hello!";调试用
                if(query.isActive()){
                    db.close();
                    QMessageBox::information(this,"提示","Update password successfully!",QMessageBox::Ok);
                    return;
                }
            else{
                    QMessageBox::information(this,"提示","Disable to Update Password!",QMessageBox::Ok);
                    return;
                }
            }

        }

        else{
            QMessageBox::information(this,"提示","uesr name or password wrong!",QMessageBox::Ok);
            ui->usr_name->clear();
            ui->old_pwd->clear();
            ui->new_pwd->clear();
            ui->confirm_pwd->clear();
            ui->usr_name->setFocus();

        }

     }
  }


void chgpwd::on_refresh_clicked()
{
    //ui->usr_name->setText("");
    ui->usr_name->clear();
    ui->old_pwd->clear();
    ui->new_pwd->clear();
    ui->confirm_pwd->clear();
}

void chgpwd::on_cancle_clicked()
{
    this->close();
    login *log=new login;
    log->show();
}
