#ifndef TRANSFER_H
#define TRANSFER_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QSqlQueryModel>
namespace Ui {
class Transfer;
}

class Transfer : public QDialog
{
    Q_OBJECT

public:
    explicit Transfer(QWidget *parent = 0);
    ~Transfer();

private slots:
    void on_view_all_clicked();

    void on_query_clicked();

    void on_affirm_clicked();

    void on_cancle_clicked();

private:
    QSqlQueryModel *model_q;
    //QSqlRelationalTableModel *model;
    Ui::Transfer *ui;
};

#endif // TRANSFER_H
