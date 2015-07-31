#ifndef SALARY_H
#define SALARY_H

#include <QDialog>
#include<QSqlRelationalTableModel>
namespace Ui {
class Salary;
}

class Salary : public QDialog
{
    Q_OBJECT

public:
    explicit Salary(QWidget *parent = 0);
    ~Salary();

private slots:
    void on_salary_all_clicked();

    void on_query_clicked();

    void on_affirm_clicked();

    void on_commit_clicked();

    void on_cancle_clicked();

    void on_del_clicked();

private:
    QSqlRelationalTableModel *model;
    Ui::Salary *ui;
};

#endif // SALARY_H
