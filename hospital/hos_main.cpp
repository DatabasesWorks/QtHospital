#include "hos_main.h"
#include "ui_hos_main.h"
#include"sick_bed.h"
#include"patient_manager.h"
#include"personnel_manager.h"
#include"salary.h"
#include"transfer.h"
#include"job_manager.h"
#include"dept_manager.h"
#include"login.h"
#include"chgpwd.h"
hos_main::hos_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::hos_main)
{
    ui->setupUi(this);
}

void hos_main::Show()
{
    this->show();
}

hos_main::~hos_main()
{
    delete ui;
}

void hos_main::on_sickbed_clicked()
{
    sick_bed *bed=new sick_bed;//创建一个sick_bed窗口。
    bed->show();
}

void hos_main::on_pesonnel_clicked()
{
    Personnel_manager *p_m=new Personnel_manager;
    p_m->show();
}

void hos_main::on_salary_clicked()
{
    Salary *salary=new Salary;
    salary->show();
}

void hos_main::on_transfer_per_clicked()
{
    Transfer *transfer=new Transfer;
    transfer->show();
}

void hos_main::on_P_m_P_clicked()
{
    Patient_manager *p_r=new Patient_manager;
    p_r->show();
}

void hos_main::on_job_clicked()
{
    Job_Manager *job_mage=new Job_Manager;
    job_mage->show();

}

void hos_main::on_dept_clicked()
{
    Dept_manager *dept_mage=new Dept_manager;
    dept_mage->show();
}
