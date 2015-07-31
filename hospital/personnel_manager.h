#ifndef PERSONNEL_MANAGER_H
#define PERSONNEL_MANAGER_H

#include <QDialog>
#include<QSqlRelationalTableModel>
#include<QComboBox>
namespace Ui {
class Personnel_manager;
}

class Personnel_manager : public QDialog
{
    Q_OBJECT

public:
    explicit Personnel_manager(QWidget *parent = 0);
    ~Personnel_manager();

private slots:
    void on_all_personnel_clicked();

    void on_query_clicked();

    void on_commit_clicked();

    void on_cancle_2_clicked();

    void on_del_clicked();

    void on_affirm_clicked();

    void on_refresh_clicked();

private:
    Ui::Personnel_manager *ui;
    QSqlRelationalTableModel *model;
    QString Getinfo(const QComboBox *combobox, const QString &table,const QString &search,const QString &condition="");
};

#endif // PERSONNEL_MANAGER_H
