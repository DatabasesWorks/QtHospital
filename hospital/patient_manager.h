#ifndef PATIENT_MANAGER_H
#define PATIENT_MANAGER_H
#include<QSqlRelationalTableModel>
#include <QDialog>
#include<QComboBox>
namespace Ui {
class Patient_manager;
}
class Patient_manager : public QDialog
{
    Q_OBJECT
public:
    explicit Patient_manager(QWidget *parent = 0);
    ~Patient_manager();

private slots:
    void on_all_clicked();
    void on_query_clicked();
    void on_commit_clicked();
    void on_cancle_clicked();
    void on_del_clicked();
    void on_affirm_clicked();
    void on_refresh_clicked();
private:
    QString Getinfo(const QComboBox *combobox, const QString &table,const QString &search,const QString &condition="");
    QSqlRelationalTableModel *model;
    Ui::Patient_manager *ui;
};

#endif // PATIENT_MANAGER_H
