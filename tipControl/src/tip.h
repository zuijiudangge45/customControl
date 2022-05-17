#ifndef TIP_H
#define TIP_H

#include <QWidget>
#include "ui_tip.h"

class tip : public QWidget
{
    Q_OBJECT

public:
    tip(QWidget * parent = 0);
    ~tip();

public slots:
    void on_pushButton_clicked();
    void on_pushButton_red_clicked();
    void on_pushButton_green_clicked();

    void on_pushButton_color_clicked();
    void on_pushButton_ok_clicked();

    void on_pushButton_left_clicked();
    void on_pushButton_top_clicked();
    void on_pushButton_right_clicked();
    void on_pushButton_bottom_clicked();

    void on_pushButton_success_clicked();
    void on_pushButton_warning_clicked();

private:
    Ui::tipClass ui;

    QColor m_color;
};

#endif // TIP_H
