
#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QMovie>
#include <QTimer>
#include <QScreen>
#include <QLabel>
#include <QMouseEvent>
#include <QShortcut>
#include <QKeyEvent>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QStyle>
#include <QJsonDocument>
#include <QMessageBox>
#include <cmath>
#include <QString>
#include <QWidget>
#include <QDialog>
#include <QDialog>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>
#include <QAction>

#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void keyPressEvent2(QKeyEvent* event2) ;

void setVes(int &newVes1,int &newVes2,int &newVes3,int &newVes4,int &newVes5,int &newVes6,int &newVes7); // 设置版本信息的函数
   void GPT(QString message);
    QSystemTrayIcon *trayIcon;
signals:
    void vesChanged(int &newVes1,int &newVes2,int &newVes3,int &newVes4,int &newVes5,int &newVes6,int &newVes7); // 版本信息变化的信号


private slots:


void executeCode();
    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
 void stTrayIconActive(QSystemTrayIcon::ActivationReason acReason);
    Ui::Widget *ui;
    void centerPet();
    void moveAwayFromCursor();
    void moveWithBoundaries(const QPoint &newPos);

    QPoint m_dragStartPosition;
    QLabel *m_petLabel;
    QTimer *m_timer;
    QRect m_screenRect;
    QMovie *m_movie1;
    QMovie *m_movie2;
        QMovie *m_movie3;
    int xx;
 QTimer* timer;

    void checkNewVersion();
};

#endif // WIDGET_H
