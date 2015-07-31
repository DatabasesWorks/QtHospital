#include "personnel_manager.h"
#include "ui_personnel_manager.h"
#include<QSqlRelationalTableModel>
#include<QSqlQuery>
#include<QMessageBox>
#include<QSqlRecord>
#include<QDebug>
#include<QDate>
#include<QSqlError>
#include<QSqlRelation>
#include"hos_main.h"
#include<QSqlRelationalDelegate>
#include<QComboBox>
#include<QString>
Personnel_manager::Personnel_manager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Personnel_manager)
{
    ui->setupUi(this);
    model=new QSqlRelationalTableModel;
    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    QSqlQuery query;
    if(query.exec("select * from dept ")){
        int i=0;
        while(query.next()){
            ui->emp_dept->insertItem(i,query.record().value("dept_name").toString());
        }
    }
    if(query.exec("select * from job ")){
        int i=0;
        while(query.next()){
            ui->job_id->insertItem(i,query.record().value("job_name").toString());
        }
    }
    ui->view_T->setItemDelegate(new QSqlRelationalDelegate(ui->view_T));

}

Personnel_manager::~Personnel_manager()
{
    delete ui;
}

void Personnel_manager::on_all_personnel_clicked()
{
    model->setTable("personnel");
    model->setRelation(18,QSqlRelation("job","job_id","job_name"));
    model->setRelation(2,QSqlRelation("dept","dept_id","dept_name"));
    model->select();
    ui->view_T->setModel(model);
    ui->view_T->show();
}

void Personnel_manager::on_query_clicked()
{
    QString name=ui->input_q->text().trimmed();
    if(name.isEmpty()){
        QMessageBox::about(this,"Notice","Please input  personnel name!");
          return;
    }
    QSqlQuery query;
    query.exec("select * from PERSONNEL where EMP_NAME='"+name+"'");
    if(!query.next()){
         QMessageBox::information(this,"Notice","The personnel name is not exist!",QMessageBox::Ok);
             return;
     }
    model->setTable("personnel");
    model->setRelation(18,QSqlRelation("job","job_id","job_name"));
    model->setRelation(2,QSqlRelation("dept","dept_id","dept_name"));
    model->setFilter("EMP_NAME='"+name+"'");
    model->select();
    ui->view_T->setModel(model);
    ui->view_T->show();
}

void Personnel_manager::on_commit_clicked()
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

void Personnel_manager::on_cancle_2_clicked()
{
    model->revertAll();
}

void Personnel_manager::on_del_clicked()
{
    int cur=ui->view_T->currentIndex().row();
    QString id=model->record(cur).value("EMP_NO").toString();
    if(id.isEmpty()){
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

void Personnel_manager::on_affirm_clicked()
{
    QString emp_id=ui->emp_id->text().trimmed();
    QString name=ui->name->text().trimmed();

    QString table="dept";
    QString search="dept_id";
    QString dept=this->Getinfo(ui->emp_dept,table,search);
    QString duty=ui->duty->text().trimmed();
    QString xl=ui->XL->currentText().trimmed();
    qDebug()<<xl;
    QString gender=ui->gender->currentText().trimmed();
    QString birthday=ui->Birthday->date().toString("dd.MM.yyyy");
    qDebug()<<birthday;
    QString hometown=ui->hometown->text().trimmed();
    QString country=ui->conuntry->text().trimmed();
    QString nation=ui->nation->text().trimmed();
    QString id=ui->id->text().trimmed();
    QString marriage=ui->marriage_state->currentText().trimmed();
    qDebug()<<marriage;
    QString health=ui->health->text().trimmed();
    QString start_work=ui->start_time->date().toString("dd.MM.yyyy");

    QString state=ui->state->currentText().trimmed();
    QString home_address=ui->address->text().trimmed();
    QString tel=ui->teleno->text().trimmed();
    QString email=ui->e_mail->text().trimmed();

    table="job";
    search="job_id";
    QString job_id=this->Getinfo(ui->job_id,table,search);
    if(name.isEmpty()||emp_id.isEmpty()||gender.isEmpty()){
        QMessageBox::information(this,"Notice","item with * must not be empty!",QMessageBox::Ok);
        return;
    }
    QString insertstr="insert into personnel values('"+emp_id+"','"+name+"','"+dept+"','"+duty+"','"+xl+"','"+gender+"','"+birthday+"','"+hometown+"','"+country+"','"+nation+"','"+id+"','"+marriage+"','"+health+"','"+start_work+"','"+state+"','"+home_address+"','"+tel+"','"+email+"','"+job_id+"')";
    QSqlQuery query;
    query.exec(insertstr);
    qDebug()<<query.lastError();
    if(query.isActive()){
        QMessageBox::about(this,"Notice","Add successfull!");
    }
    else{
        QMessageBox::about(this,"Notice","Add not successfull!");
    }
}

void Personnel_manager::on_refresh_clicked()
{
    ui->emp_id->clear();
    ui->name->clear();
    ui->duty->clear();
    ui->emp_dept->setCurrentIndex(0);
    ui->Birthday->setDate(QDate::currentDate());

    ui->hometown->clear();
    ui->conuntry->clear();
    ui->nation->clear();
    ui->id->clear();
    ui->health->clear();

    ui->start_time->setDate(QDate::currentDate());
    ui->state->setCurrentIndex(0);
    ui->address->clear();
    ui->teleno->clear();
    ui->e_mail->clear();

    ui->job_id->setCurrentIndex(0);
    ui->XL->setCurrentIndex(0);
    ui->gender->setCurrentIndex(0);
    ui->marriage_state->setCurrentText(0);
}
//*********************************************
//自定义函数，将combox中currentindex()i所指向table表的值
//转化成QString
//*********************************************
QString Personnel_manager::Getinfo(const QComboBox *combobox, const QString &table,const QString &search,const QString &condition)
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
