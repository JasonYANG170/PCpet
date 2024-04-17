#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
signals:
    void vesChanged(int &newVes1,int &newVes2,int &newVes3,int &newVes4,int &newVes5,int &newVes6,int &newVes7); // 版本信息变化的信号

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H
