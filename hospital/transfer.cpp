#include "transfer.h"
#include "ui_transfer.h"
#include<QSqlRelationalTableModel>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QMessageBox>
#include"hos_main.h"
#include<QSqlError>
#include<QSqlRecord>
#include<QSqlRelationalDelegate>
#include"hos_main.h"
Transfer::Transfer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Transfer)
{
    ui->setupUi(this);
    //model=new QSqlRelationalTableModel;
    model_q=new QSqlQueryModel(this);
    QSqlQuery query;
    if(query.exec("select * from personnel")){
        int i=0;
        while(query.next()){
            ui->id->insertItem(i,query.record().value("emp_no").toString());
        }
    }
}

Transfer::~Transfer()
{
    delete ui;
}

void Transfer::on_view_all_clicked()
{
    model_q->setQuery("select EMP_NO as personnel_ID,EMP_DEPT_ID as dept_ID from PERSONNEL");
    ui->view_T->setModel(model_q);
    //model_q->setQuery();

}

void Transfer::on_query_clicked()
{
    QString ID=ui->input->text().trimmed();
    if(ID.isEmpty()){
        QMessageBox::information(this,"Notice","Please input something",QMessageBox::Ok);
        return;
    }
    model_q->setQuery("select EMP_NO as personnel_ID,EMP_DEPT_ID as dept_I from PERSONNEL where EMP_NO="+ID+"");
    if(!model_q->query().next()){
        QMessageBox::information(this,"Notice","The personnel id is not exist!",QMessageBox::Ok);
            return;
    }
    ui->view_T->setModel(model_q);
}

void Transfer::on_affirm_clicked()
{
    QString id=ui->id->currentText();
    QString dept=ui->DEPT->text().trimmed();
    if(id.isEmpty()||dept.isEmpty()){
        QMessageBox::information(this,"Notice","Please input fully",QMessageBox::Ok);
        return;
    }
    model_q->setQuery("select * from PERSONNEL WHERE EMP_NO="+id+"");
    if(!model_q->query().next()){
        QMessageBox::information(this,"Notice","The personnel id is not exist!",QMessageBox::Ok);
            return;
    }
    model_q->setQuery("Update PERSONNEL SET EMP_DEPT_ID="+dept+" WHERE EMP_NO="+id+"");
    if(model_q->query().isActive()){
        QMessageBox::information(this,"Notice","Update successfully",QMessageBox::Ok);
        model_q->setQuery("select EMP_NO as personnel_ID,EMP_DEPT_ID as dept_ID from PERSONNEL");
        ui->view_T->setModel(model_q);
        return;
    }
    else{
        QMessageBox::information(this,"Notice","Update Error!",QMessageBox::Ok);
        return;
    }
}

void Transfer::on_cancle_clicked()
{
    ui->id->setCurrentIndex(0);
    ui->DEPT->clear();
}
