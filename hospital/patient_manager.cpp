#include "patient_manager.h"
#include "ui_patient_manager.h"
#include"hos_main.h"
#include<QSqlRelationalTableModel>
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlRecord>
#include<QSqlError>
#include<QDebug>
#include<QSqlRelationalDelegate>
#include<QSqlRelation>
#include<QComboBox>
Patient_manager::Patient_manager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Patient_manager)
{
    model=new QSqlRelationalTableModel(this);
    ui->setupUi(this);
    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    ui->patient_table->setItemDelegate(new QSqlRelationalDelegate(ui->patient_table));
    QSqlQuery query;
    if(query.exec("select * from sick_bed ")){
        int i=0;
        while(query.next()){
            ui->id->insertItem(i,query.record().value("bed_id").toString());
        }
    }
    //ui->doctor->setItemDelegate(
               // new QSqlRelationalDelegate(ui->doctor));
    if(query.exec("select * from personnel where emp_job_id=2")){
        int i=0;
        while(query.next()){
            ui->doctor->insertItem(i,query.record().value("emp_name").toString());
        }
    }
    //ui->patient_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Patient_manager::~Patient_manager()
{
    delete ui;
}

void Patient_manager::on_all_clicked()
{
    model->setTable("PATIENT");
    model->setRelation(5,QSqlRelation("personnel","emp_no","emp_name"));
    model->setRelation(7,QSqlRelation("sick_bed","bed_id","bed_id"));
    model->setHeaderData(0,Qt::Horizontal,"Name");
    model->setHeaderData(1,Qt::Horizontal,"Gender");
    model->setHeaderData(2,Qt::Horizontal,"Start time");
    model->setHeaderData(3,Qt::Horizontal,"Dept");
    model->setHeaderData(4,Qt::Horizontal,"State");
    model->setHeaderData(5,Qt::Horizontal,"Doctor");
    model->setHeaderData(6,Qt::Horizontal,"Room");
   // model->setHeaderData(7,Qt::Horizontal,"Bed");

    model->select();
    ui->patient_table->setModel(model);

}

void Patient_manager::on_query_clicked()
{
    QString name=ui->input->text().trimmed();
    if(name.isEmpty()){
          QMessageBox::about(this,"Notice","Please input  patient name!");
            return;
        }
     QSqlQuery query;
     query.exec("select * from PATIENT where PATIENT_NAME='"+name+"'");
     if(!query.next()){
          QMessageBox::information(this,"Notice","The patient id is not exist!",QMessageBox::Ok);
              return;
      }
     model->setTable("PATIENT");
     model->setRelation(5,QSqlRelation("personnel","emp_no","emp_name"));
     model->setRelation(7,QSqlRelation("sick_bed","bed_id","bed_id"));
     model->setFilter("PATIENT_NAME="+name+"");
     model->select();
     ui->patient_table->setModel(model);
}

void Patient_manager::on_commit_clicked()
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

void Patient_manager::on_cancle_clicked()
{
    model->revertAll();
}

void Patient_manager::on_del_clicked()
{
    int cur=ui->patient_table->currentIndex().row();
    QString name=model->record(cur).value("PATIENT_NAME").toString();
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

void Patient_manager::on_affirm_clicked()
{
    QString name=ui->name->text().trimmed();
    QString gender=ui->gender->currentText().trimmed();
    QString start=ui->start_time->text().trimmed();
    QString dept=ui->bel_dept->text().trimmed();
    QString state=ui->state->text().trimmed();
    QString personnel="personnel";
    QString emp_job_id="emp_job_id=2";
    QString emp_id="EMP_ID";
    QString doctor=this->Getinfo(ui->doctor,personnel,emp_job_id,emp_id);
    qDebug()<<doctor;
    QString room=ui->room->text().trimmed();
    QString id=ui->id->currentText();
    if(name.isEmpty()||gender.isEmpty()||start.isEmpty()||dept.isEmpty()||state.isEmpty()||doctor.isEmpty()){
       QMessageBox::about(this,"NOTICE","Item with* can't not be empty!");
       return;
     }
     QSqlQuery query;
     QString insertStr;
     insertStr="insert into PATIENT(PATIENT_NAME,PATIENT_GENDER,PATIENT_DATE_START,PATIENT_DEPT,PATIENT_DOC,PATIENT_STATE,PATIENT_ROOM,PATIENT_BED) VALUES('"+name+"','"+gender+"','"+start+"','"+dept+"','"+state+"','"+doctor+"','"+room+"','"+id+"');";
      query.exec(insertStr);
      qDebug()<<query.lastError();
      if(query.isActive()){
         QMessageBox::about(this,"Notice","Add successfull!");
      }
      else{
          QMessageBox::about(this,"Notice","Add not successfull!");
      }

}

void Patient_manager::on_refresh_clicked()
{
    ui->name->clear();
    ui->gender->setCurrentIndex(0);
    ui->start_time->clear();
    ui->bel_dept->clear();
    ui->state->clear();
    ui->doctor->setCurrentIndex(0);
    ui->room->clear();
    ui->id->setCurrentIndex(0);
}
//*********************************************
//自定义函数，将combox中currentindex()i所指向table表的值
//转化成QString
//*********************************************
QString Patient_manager::Getinfo(const QComboBox *combobox, const QString &table,const QString &search,const QString &condition)
{
    if(combobox==NULL){
        qDebug()<<"combobox is null";
        return "";
    }
    int i;
    i=combobox->currentIndex();
    QSqlQuery *query=new QSqlQuery;
    if(condition==""){
        if(query->exec("select * from "+table+"")){
            qDebug()<<"hello,this is condition==";
            for(int j=0;query->next();j++){
                if(j==i){
                    qDebug()<<"hello,this is condition==""";
                    return query->value(search).toString();
                }
            }
        }
    }
    else{

        if(query->exec("select * from "+table+" where "+condition+"")){
                qDebug()<<"hello,this is a";
                for(int j=0;query->next();j++){
                    if(j==i){
                        qDebug()<<"hello,this is bbbbb";
                        return query->value(search).toString();
                    }
                }
           }
    }
    return "";
}
