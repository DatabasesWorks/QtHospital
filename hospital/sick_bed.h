#ifndef SICK_BED_H
#define SICK_BED_H

#include <QDialog>
#include <QtSql/QSqlRelationalTableModel>
namespace Ui {
class sick_bed;
}

class sick_bed : public QDialog
{
    Q_OBJECT

public:
    explicit sick_bed(QWidget *parent = 0);
    ~sick_bed();

private slots:
    void on_query_clicked();
    void on_submit_clicked();
    void on_cancle_clicked();
    void on_del_clicked();
    void on_add_clicked();
    void on_all_clicked();
    void on_exit_clicked();

private:
    QSqlRelationalTableModel *model;
    Ui::sick_bed *ui;
};

#endif // SICK_BED_H
