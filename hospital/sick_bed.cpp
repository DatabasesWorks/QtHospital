#include "sick_bed.h"
#include "ui_sick_bed.h"
#include<QtSql/QSqlRelationalTableModel>
#include<QMessageBox>
//#include"database.h"
#include"hos_main.h"
#include<QSqlRecord>
sick_bed::sick_bed(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sick_bed)
{
    ui->setupUi(this);
    model=new QSqlRelationalTableModel(this);
    model->setHeaderData(0,Qt::Horizontal,"Bed ID");
    model->setHeaderData(1,Qt::Horizontal,"Bed state");
    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
}

sick_bed::~sick_bed()
{
    delete ui;
}

void sick_bed::on_query_clicked()
{

    QString bed_id=ui->input->text().trimmed();
    if(bed_id.isEmpty()){
      QMessageBox::about(this,"Notice","Please input bed id");
      return;
    }
    model->setTable("sick_bed");
    model->setFilter("BED_ID="+bed_id+"");
    model->select();
    ui->view_a->setModel(model);
}

void sick_bed::on_submit_clicked()
{
    model->database().transaction();
    if(model->submitAll()){
       model->database().commit();
    QMessageBox::information(this,"Notice","Successful",QMessageBox::Ok);
    }
    else{
       model->database().rollback();
       QMessageBox::information(this,"Notice","database error",QMessageBox::Ok);
    }
}

void sick_bed::on_cancle_clicked()
{

    model->revertAll();
}

void sick_bed::on_del_clicked()
{

    int cur=ui->view_a->currentIndex().row();
    QString bed_id=model->record(cur).value("bed_id").toString();
    if(bed_id.isEmpty()){
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

void sick_bed::on_add_clicked()
{
    int currow=model->rowCount();
    model->insertRow(currow);
}

void sick_bed::on_all_clicked()
{
    model->setTable("sick_bed");
    model->select();
    ui->view_a->setModel(model);
}

void sick_bed::on_exit_clicked()
{
    this->close();
}
