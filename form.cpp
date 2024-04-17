#include "form.h"
#include "ui_form.h"

#include "widget.h"
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{


    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    int x1=ui->lineEdit->text().toInt();
      int x2=ui->lineEdit_2->text().toInt();
      int x3=ui->lineEdit_3->text().toInt();
        int x4=ui->lineEdit_4->text().toInt();
      int x5=ui->lineEdit_5->text().toInt();
      int x6=ui->lineEdit_6->text().toInt();
         int x7=ui->lineEdit_6->text().toInt();
    Widget widget;
    connect(this, &Form::vesChanged, &widget, &Widget::setVes); // Connect the signal from Form to the slot in Widget

    emit vesChanged(x1,x2,x3,x4,x5,x6,x7); // Emit the signal to set the version information in Widget

    QMessageBox::warning(this, "Error", "设置成功，重启程序后生效。");

}


void Form::on_pushButton_2_clicked()
{
    Widget widget;
    connect(this, &Form::vesChanged, &widget, &Widget::setVes); // Connect the signal from Form to the slot in Widget
    int x=0;
    int x2=0;
    int x3=0;
    int x4=0;
    int x5=200;
    int x6=100;
    int x7=20;
    emit vesChanged(x,x2,x3,x4,x5,x6,x7); // Emit the signal to set the version information in Widget

    QMessageBox::warning(this, "Error", "设置成功，重启程序后生效。");
}


void Form::on_pushButton_3_clicked()
{

}

