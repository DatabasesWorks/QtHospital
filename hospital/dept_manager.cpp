#include "dept_manager.h"
#include "ui_dept_manager.h"
#include <QSqlRelationalTableModel>
#include<QMessageBox>
#include<QSqlRecord>
#include"hos_main.h"
Dept_manager::Dept_manager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dept_manager)
{
    ui->setupUi(this);
    model=new QSqlRelationalTableModel(this);//为model申请内存。
    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);//设置model模型策略为提交更改模式
}

Dept_manager::~Dept_manager()//析构函数
{
    delete ui;
}

//*********************************
//函数名：on_all_clicked
//函数作用：显示所有部门信息
//********************************
void Dept_manager::on_all_clicked()//
{
    model->setTable("dept");//为model设置表dept
    model->setHeaderData(0,Qt::Horizontal,"dept id");//设置表弟0列为dept id
    model->setHeaderData(1,Qt::Horizontal,"dept name");//同上
    model->setHeaderData(2,Qt::Horizontal,"manager");
    model->setHeaderData(3,Qt::Horizontal,"vice manager");
    model->select();//相当于select * from dept;
    ui->view_a->setModel(model);//为view_a(table view)设置模型model
    ui->view_a->show();//显示view_a;
}
//***********************************
//函数名：on_query_clicked
//函数作用：根据部门名字查询相关部门信息
//***********************************
void Dept_manager::on_query_clicked()
{
    QString dept_name=ui->input->text().trimmed();//获取输入的部门名字
    if(dept_name.isEmpty()){//若没有输入，则报错。
      QMessageBox::about(this,"Notice","Please input job name");
      return;
    }
    model->setTable("dept");//设置model的表
    model->setHeaderData(0,Qt::Horizontal,"dept id");
    model->setHeaderData(1,Qt::Horizontal,"dept name");
    model->setHeaderData(2,Qt::Horizontal,"manager");
    model->setHeaderData(3,Qt::Horizontal,"vice manager");
    model->setFilter("DEPT_NAME='"+dept_name+"'");//相当于select * from dept where DEPT_NAME=dept_name
    model->select();//根据setFliter语句进行选择查询
    ui->view_a->setModel(model);
    ui->view_a->show();

}
//***************************
//函数作用：提交对表的修改
//***************************
void Dept_manager::on_submit_clicked()
{
    model->database().transaction();//进行事物操作
    int ok=QMessageBox::warning(this,"Notice","Do You Want to Update it?",QMessageBox::Yes,QMessageBox::No);
    if(ok==QMessageBox::Yes){//确认删除
        if(model->submitAll()){//提交成功
            model->database().commit();//提交事物操作
            QMessageBox::information(this,"Notice","Update Successfully!",QMessageBox::Ok);
        }
        else{//提交不成功
            model->database().rollback();//数据库事物回滚操作
            QMessageBox::information(this,"Notice","Database  Error!",QMessageBox::Ok);
        }
    }
    else{//若不删除，撤销所有更改
        model->revertAll();//撤销所有更改语句
        QMessageBox::information(this,"Notice","Doesn't commit!",QMessageBox::Ok);
    }
}

//***********************************
//函数作用：撤销所有更改
//***********************************
void Dept_manager::on_cancle_clicked()
{
    model->revertAll();
}

//**********************************
//函数作用：添加一条数据库记录
//*********************************
void Dept_manager::on_add_clicked()
{
    int currow=model->rowCount();//获取当前行
    model->insertRow(currow);//增加一行记录
}

//*********************************
//函数作用：删除一行记录
//*********************************
void Dept_manager::on_del_clicked()
{
    int cur=ui->view_a->currentIndex().row();//获取当前指定的行
    QString dept_name=model->record(cur).value("DEPT_NAME").toString();
    if(dept_name.isEmpty()){//若没有选中
        QMessageBox::information(this,"Notice","You didn't choose!",QMessageBox::Ok);
        return;
    }
    model->removeRow(cur);//删除行
    int ok=QMessageBox::warning(this,"Notice","Do you want to delete it?",QMessageBox::Yes,QMessageBox::No);
    if(ok==QMessageBox::Yes){//确定删除
        model->submitAll();
        QMessageBox::about(this,"Notice","Delete successfully!");
    }
    else{//取消删除
        model->revertAll();
        QMessageBox::about(this,"Notice","Undo deletion!");
    }

}
