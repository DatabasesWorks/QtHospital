#include "job_manager.h"
#include "ui_job_manager.h"
#include<QSqlRelationalTableModel>
#include<QSqlRecord>
#include<QMessageBox>
#include"hos_main.h"
#include<QSqlRelation>
#include<QSqlRelationalDelegate>
#include<QTableView>
Job_Manager::Job_Manager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Job_Manager)
{
    ui->setupUi(this);
    model=new QSqlRelationalTableModel(this);
    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);//设置提交策略为提交更改。
    //model->setTable("job");
   // model->setRelation(2,QSqlRelation("dept","dept_id","dept_name"));
    ui->view_a->setItemDelegate(new QSqlRelationalDelegate(ui->view_a));//为view_a设置一个委托。
}

Job_Manager::~Job_Manager()//析构函数
{
    delete ui;
}

void Job_Manager::on_all_clicked()
{
    model->setTable("job");//设置model的表
    model->setRelation(2,QSqlRelation("dept","dept_id","dept_name"));//将表job 和表 dept 进行关联。
    model->setHeaderData(0,Qt::Horizontal,"job id");
    model->setHeaderData(1,Qt::Horizontal,"job name");
    model->setHeaderData(2,Qt::Horizontal,"dept name");
    model->setSort(0,Qt::AscendingOrder);
    model->select();
    ui->view_a->setModel(model);
    ui->view_a->show();
}

void Job_Manager::on_query_clicked()
{
    QString job_name=ui->input->text().trimmed();
    if(job_name.isEmpty()){
      QMessageBox::about(this,"Notice","Please input job name");
      return;
    }
    model->setTable("job");
    model->setRelation(2,QSqlRelation("dept","dept_id","dept_name"));
    //QTableView *view = new QTableView;
    //view->setModel(model);
    model->setHeaderData(0,Qt::Horizontal,"job id");
    model->setHeaderData(1,Qt::Horizontal,"job name");
    model->setHeaderData(2,Qt::Horizontal,"dept name");
    model->setFilter("JOB_NAME='"+job_name+"'");
    model->select();
    //ui->view_a->setItemDelegate(new QSqlRelationalDelegate(ui->view_a));
    ui->view_a->setModel(model);
    ui->view_a->show();

}

void Job_Manager::on_submit_clicked()
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

void Job_Manager::on_cancle_clicked()
{
    model->revertAll();
}

void Job_Manager::on_add_clicked()
{
    int currow=model->rowCount();
    model->insertRow(currow);
    //model->setTable("job");
    //model->setRelation(2,QSqlRelation("dept","dept_id","dept_name"));
}

void Job_Manager::on_del_clicked()
{
    int cur=ui->view_a->currentIndex().row();
    QString job_name=model->record(cur).value("JOB_NAME").toString();
    if(job_name.isEmpty()){
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
