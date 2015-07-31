#ifndef JOB_MANAGER_H
#define JOB_MANAGER_H

#include <QDialog>
#include<QSqlRelationalTableModel>
namespace Ui {
class Job_Manager;
}

class Job_Manager : public QDialog
{
    Q_OBJECT

public:
    explicit Job_Manager(QWidget *parent = 0);
    ~Job_Manager();

private slots:void on_query_clicked();

    void on_all_clicked();
    void on_submit_clicked();
    void on_cancle_clicked();
    void on_add_clicked();
    void on_del_clicked();
private:
    QSqlRelationalTableModel *model;
    Ui::Job_Manager *ui;
};

#endif // JOB_MANAGER_H
