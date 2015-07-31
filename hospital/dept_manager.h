#ifndef DEPT_MANAGER_H
#define DEPT_MANAGER_H

#include <QDialog>
#include<QSqlRelationalTableModel>
namespace Ui {
class Dept_manager;
}

class Dept_manager : public QDialog
{
    Q_OBJECT

public:
    explicit Dept_manager(QWidget *parent = 0);
    ~Dept_manager();

private slots:
    void on_all_clicked();
    void on_query_clicked();
    void on_submit_clicked();
    void on_cancle_clicked();
    void on_add_clicked();
    void on_del_clicked();
private:
    QSqlRelationalTableModel *model;
    Ui::Dept_manager *ui;
};

#endif // DEPT_MANAGER_H
