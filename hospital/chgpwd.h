#ifndef CHGPWD_H
#define CHGPWD_H

#include <QMainWindow>

namespace Ui {
class chgpwd;
}

class chgpwd : public QMainWindow
{
    Q_OBJECT

public:
    explicit chgpwd(QWidget *parent = 0);
    ~chgpwd();

private slots:
    void on_affirm_clicked();

    void on_refresh_clicked();

    void on_cancle_clicked();

private:
    Ui::chgpwd *ui;
};

#endif // CHGPWD_H
