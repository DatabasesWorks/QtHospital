#include "salary.h"
#include "ui_salary.h"
#include<QSqlRelationalTableModel>
#include<QSqlQuery>
#include<QMessageBox>
#include<QSqlTableModel>
#include<QSqlQueryModel>
#include<QSqlRecord>
#include<QSqlRelationalDelegate>
#include<QSqlRelation>
Salary::Salary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Salary)
{
    model=new QSqlRelationalTableModel(this);
    ui->setupUi(this);
   // ui->view_t->setEditTriggers(QAbstractItemView::NoEditTriggers);
    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    ui->view_t->setItemDelegate(new QSqlRelationalDelegate(ui->view_t));
    QSqlQuery query;
    if(query.exec("select * from personnel ")){
        int i=0;
        while(query.next()){
            ui->id->insertItem(i,query.record().value("emp_no").toString());
        }
    }
}

Salary::~Salary()
{
    delete ui;
}

void Salary::on_salary_all_clicked()
{
    model->setTable("salary");
    model->setRelation(0,QSqlRelation("personnel","emp_no","emp_name"));
    model->setHeaderData(0,Qt::Horizontal,"Personnel ID");
    model->setHeaderData(1,Qt::Horizontal,"Salary");
    model->select();
    ui->view_t->setModel(model);
    ui->view_t->show();

}

void Salary::on_query_clicked()
{
    QString name=ui->input->text().trimmed();
    if(name.isEmpty()){
        QMessageBox::about(this,"Notice","Please input  personnel name!");
          return;
   }
    QSqlQueryModel *model_q=new QSqlQueryModel;
    model_q->setQuery("select * from personnel where EMP_name='"+name+"'");
    if(!model_q->query().next()){
        QMessageBox::information(this,"Notice","The personnel id is not exist!",QMessageBox::Ok);
            return;
    }
   // model_q->setHeaderData(0,Qt::Horizontal,"Personnel ID");
   // model_q->setHeaderData(1,Qt::Horizontal,"Salary");
    model->setTable("salary");
    model->setRelation(0,QSqlRelation("personnel","emp_no","emp_name"));
    model->setHeaderData(0,Qt::Horizontal,"Personnel name");
    model->setHeaderData(1,Qt::Horizontal,"Salary");
   // model->setFilter("");
    //重点在这里。
    model->setFilter("salary.emp_no=personnel.emp_no where personnel.emp_name='"+name+"'");
    model->select();
    ui->view_t->setModel(model);
}

void Salary::on_affirm_clicked()
{
    QString id=ui->id->currentText();
    QString salary=ui->salary->text().trimmed();
    if(id.isEmpty()||salary.isEmpty()){
        QMessageBox::about(this,"Notice","Please input  full message!");
          return;
    }
    QSqlQueryModel *model_q=new QSqlQueryModel;
    model_q->setQuery("select EMP_NO as ID from personnel where EMP_NO="+id+"");
    if(model_q->query().next()){
        model_q->setQuery("insert into salary values('"+id+"','"+salary+"')");
        QMessageBox::about(this,"Notice","Update successfully!");
          return;
    }
    else{
        QMessageBox::about(this,"Notice","Please input  correct ID!");
          return;
    }
}

void Salary::on_commit_clicked()
{
    model->database().transaction();
    int ok=QMessageBox::warning(this,"Notice","Do You Want to Update it?",QMessageBox::Yes,QMessageBox::No);
    if(ok==QMessageBox::Yes){
        if(model->submitAll()){
            model->database().commit();
            QMessageBox::information(this,"Notice","Update Successfully!",QMessageBox::Ok);
        }
        else{
            model->database().rollback();
            QMessageBox::information(this,"Notice","Database  Error!",QMessageBox::Ok);
        }
    }
    else{
        model->revertAll();
        QMessageBox::information(this,"Notice","Doesn't commit!",QMessageBox::Ok);
    }
}

void Salary::on_cancle_clicked()
{
    model->revertAll();
}

void Salary::on_del_clicked()
{
    int cur=ui->view_t->currentIndex().row();
    QString name=model->record(cur).value("EMP_NO").toString();
    if(name.isEmpty()){
       QMessageBox::information(this,"Notice","You didn't choose!",QMessageBox::Ok);
       return;
    }
    model->removeRow(cur);
    int ok=QMessageBox::warning(this,"Notice","Do you want to delete it?",QMessageBox::Yes,QMessageBox::No);
    if(ok==QMessageBox::Yes){
        model->submitAll();
        QMessageBox::about(this,"Notice","Delete successfully!");
    }
    else{
        model->revertAll();
        QMessageBox::about(this,"Notice","Undo deletion!");
    }

}
