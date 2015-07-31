#ifndef HOS_MAIN_H
#define HOS_MAIN_H
#include<QtSql/QSqlDatabase>
#include <QMainWindow>
extern QSqlDatabase db;
namespace Ui {
class hos_main;
}

class hos_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit hos_main(QWidget *parent = 0);
    void Show();
    ~hos_main();

private slots:
    void on_sickbed_clicked();
    //void on_patient_manage_clicked();
    void on_pesonnel_clicked();

    void on_salary_clicked();

    void on_transfer_per_clicked();

    void on_P_m_P_clicked();

    void on_job_clicked();

    void on_dept_clicked();

private:
    Ui::hos_main *ui;
};

#endif // HOS_MAIN_H
