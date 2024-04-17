
#include "widget.h"
#include "qboxlayout.h"
#include "ui_widget.h"
#include <QSettings>
#include <QApplication>
#include <QJsonDocument>
#include <QApplication>
#include <QLabel>
#include <QMovie>
#include <QGraphicsDropShadowEffect>
#include <QDesktopServices>
#include <QUrl>
#include <QLineEdit>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QImage>
#include <QPixmap>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>
#include <QStyle>
#include <QAction>
#include <QGraphicsView>
int px=200;
int py=100;
int x1=0,x2=0,x3=0,x4=0,speed=0;
int progress,eat,clear,fat;
      QString ves="V3.0";
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\YANG-PCpetV3.0", QSettings::NativeFormat);
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    QPixmap img(":/Win11.jpg");

    connect(ui->pushButton_5, &QPushButton::clicked, this, &Widget::on_pushButton_5_clicked);

    QIcon icon = QApplication::style()->standardIcon((QStyle::StandardPixmap)0);
    QIcon icon1 = QApplication::style()->standardIcon((QStyle::StandardPixmap)9);

    //设置通知栏的图标
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);

    //设置通知栏的单击事件
    // connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(stTrayIconActive(QSystemTrayIcon::ActivationReason)));

    //设置通知栏的右键菜单
    //QMenu * menu = new QMenu();

    //设置菜单项目
    // QAction *actionHide = new QAction(icon, "Hide", menu);

    //menu->addAction(actionHide);
    //  trayIcon->setContextMenu(menu);
    // 设置Action的响应
    //connect(actionHide, SIGNAL(triggered()), this, SLOT(stActionHide()));
    trayIcon->show();

    ui->setupUi(this);
    // 读取注册表数据
    x1= settings.value("x1").toInt();
    x2= settings.value("x2").toInt();
    x3= settings.value("x3").toInt();
    x4= settings.value("x4").toInt();
    px= settings.value("px").toInt();
    py = settings.value("py").toInt();
     speed = settings.value("speed").toInt();
        progress= settings.value("progress").toInt();
     ui->progressBar->setValue(progress);
    if((settings.value("py").toString())==""||(settings.value("py").toInt())==0){
        px=200;
        py=100;
    }
    if((settings.value("speed").toString())==""||(settings.value("speed").toInt())==0){
        speed=20;
    }
   qDebug() << "Alt key pressed"+settings.value("py").toString();
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    ui->pushButton->setStyleSheet("QPushButton:focus { outline: none; box-shadow: none; }");
    // 添加宠物GIF图片
    m_movie1 = new QMovie(".\\512.gif");
    m_movie2 = new QMovie(".\\511.gif");
    m_movie3 = new QMovie(".\\513.gif");

    m_petLabel = new QLabel(this);
    m_petLabel->setMovie(m_movie3);
    m_petLabel->setFixedSize(px, py); // 设置宠物的大小
    m_petLabel->setScaledContents(true);

    m_movie3->start();
    // 创建布局管理器

    centerPet(); // 图片居中


//ui->progressBar->raise();
    // 提升文本框到最前面


    // 获取屏幕信息
    QScreen *screen = qApp->primaryScreen();
    m_screenRect = screen->availableGeometry();

    // 计时器用于检测鼠标靠近和边界检测
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Widget::moveAwayFromCursor);
    m_timer->start(speed); // 每隔50毫秒检测一次


    checkNewVersion();
    timer = new QTimer(this);
    int interval = 60000; // 5 minutes (300000 milliseconds)
    timer->setInterval(interval);

    connect(timer, &QTimer::timeout, this, &Widget::executeCode);

    timer->start();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setVes(int &newVes1,int &newVes2,int &newVes3,int &newVes4,int &newVes5,int &newVes6,int &newVes7)
{
  x1 = newVes1; // 设置版本信息值
      x2 = newVes2;
    x3 = newVes3;
        x4 = newVes4;
    px=newVes5;
            py=newVes6;
    speed=newVes7;
    // 写入注册表数据
    settings.setValue("x1", newVes1);
    settings.setValue("x2", newVes2);
    settings.setValue("x3", newVes3);
    settings.setValue("x4", newVes4);
    settings.setValue("px", newVes5);
    settings.setValue("py", newVes6);
   settings.setValue("speed", newVes7);

}
void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragStartPosition = event->pos();
    }

}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QPoint distance = event->pos() - m_dragStartPosition;
        moveWithBoundaries(pos() + distance); // 添加边界限制
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
int x31=1;
void Widget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Alt) {
        // 当按下Alt键时执行的代码
        qDebug() << "Alt key pressed";
        xx = 1;
    }

  //  if (event->key() == Qt::Key_Shift&&x31%2==0) {
        // 当按下Alt键时执行的代码
    //    qDebug() << "Alt key pressedSS";
    //    GPT();

   // }

}

void Widget::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Alt) {
        // 当释放Alt键时执行的代码
        qDebug() << "Alt key released";
        xx = 0;
        //m_petLabel->movie()->start(); // 恢复GIF播放
        m_movie3->start();
        m_petLabel->setMovie(m_movie3);
        m_petLabel->setScaledContents(true);
        if(fat>0){
            fat-=1;
             settings.setValue("fat", fat);
        }
        if(progress<100){
             progress+=1;
             settings.setValue("progress", progress);
        }
        ui->progressBar->setValue(progress);
        trayIcon->showMessage("YANG-PCpet", "运动后我感到开心");
    }
    else {
        QWidget::keyPressEvent(event);
    }
}

void Widget::centerPet()
{
    int x = (width() / 2 - m_petLabel->width() / 2)-11;
    int y = height() / 2 - m_petLabel->height() / 2;
    m_petLabel->move(x, y);
}

void Widget::moveAwayFromCursor()
{
    QPoint cursorPos = QCursor::pos();
    QPoint widgetPos = mapToGlobal(rect().topLeft());

    int dx = cursorPos.x() - widgetPos.x() - m_petLabel->width() / 2;
    int dy = cursorPos.y() - widgetPos.y() - m_petLabel->height() / 2;

    int distance = std::sqrt(dx * dx + dy * dy);

    if (xx == 1) {
        if (distance > 10) {
            int moveStep = std::min(8, distance / 10); // 控制移动
QPoint moveBy(dx * moveStep / distance, dy * moveStep / distance);

        if (dx < 0) { // 向左移动时切换到另一个GIF
            m_movie2->start();
            m_petLabel->setMovie(m_movie2);
            m_petLabel->setScaledContents(true);
        } else {
            m_movie1->start();
            m_petLabel->setMovie(m_movie1);
            m_petLabel->setScaledContents(true);
        }

        moveWithBoundaries(pos() - moveBy); // 添加边界限制
    }
}
}

void Widget::moveWithBoundaries(const QPoint &newPos)
{
QPoint boundedPos(newPos);

// 获取屏幕几何信息
const QRect screenRect = QGuiApplication::primaryScreen()->availableGeometry();
const int frameThickness = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);

// 设置边界限制
boundedPos.setX(qMax(screenRect.left()+x3, boundedPos.x()));
boundedPos.setY(qMax(screenRect.top() +x1, boundedPos.y()));
boundedPos.setX(qMin(screenRect.right() - width()+x4, boundedPos.x()));
boundedPos.setY(qMin(screenRect.bottom() - height()+x2, boundedPos.y()));

move(boundedPos);
}

void Widget::checkNewVersion()
{
QNetworkAccessManager *manager = new QNetworkAccessManager(this);
QUrl url("https://api.vvhan.com/api/qqsc?key=c4c63feac2129cb548942c31dfb8badf");
QNetworkRequest request(url);

// Set unsafe SSL configuration
QSslConfiguration config = request.sslConfiguration();
config.setPeerVerifyMode(QSslSocket::VerifyNone);
request.setSslConfiguration(config);

QNetworkReply *reply = manager->get(request);

// Connect to the finished signal
connect(reply, &QNetworkReply::finished, [=]() {
    if (reply->error() == QNetworkReply::NoError) {
        // Read the JSON data
        QByteArray data = reply->readAll();

        // Display the JSON data in a message box
        QJsonDocument jsonDoc = QJsonDocument::fromJson(QString(data).toUtf8());
        QJsonObject jsonObj = jsonDoc.object();

        // 获取数据
        QString info = jsonObj["content"].toString();
        if (info != ves) {
            QMessageBox::warning(this, "Error", "已发布新版本\"" + info + "\"。\n点击\"设置\"下载最新版本。");
            // ui->pushButton_4->setText("发现新版本");
            QUrl url("https://github.com/JasonYANG170/YANG-PCpet/releases");
            QDesktopServices::openUrl(url);
        }
        else {
            //  ui->pushButton_4->setText("暂无更新");
        }
    }
    else {
        // Display an error message
        QMessageBox::warning(this, "Error", reply->errorString());
    }

    // Clean up
    reply->deleteLater();
    manager->deleteLater();
});
}

void Widget::on_pushButton_clicked()
{
x31++;
if(x31%2==0){

ui->pushButton_6->raise();
ui->textEdit->raise();
}else{
ui->pushButton_6->lower();
ui->textEdit->lower();
ui->pushButton->setFocusPolicy(Qt::NoFocus);  // 禁用焦点
ui->pushButton->setFocusPolicy(Qt::NoFocus);  // 禁用焦点
}
}
void Widget::GPT(QString message)
{
QNetworkAccessManager manager;

// 创建POST请求
QUrl url("https://aigptx.top/api/v1/ai/chatgpt/chat"); // 更换为你要访问的API地址
QNetworkRequest request(url);
QString accessToken = "eyJhbGciOiJFUzUxMiIsInR5cCI6IkpXVCJ9.eyJpZCI6IjQ2ODYiLCJlbWFpbCI6InF3MjAwNDc3QDE2My5jb20iLCJwdXJwb3NlIjoid2ViIiwiaWF0IjoxNzAxNzQzMTcwLCJleHAiOjE3MDI5NTI3NzB9.AeFiM5wAbpFfR05cN-zu8UJX8Vg6nMjPWhNmafh9KFleOfxtSEfMXfswvjbS2KlWNGTdAguZDGDJkG-2aCLmSbh0AO-YbWTOcFEFqlENe1PucnH1XjRFqyab40eNkFk-mi1CadJ5UBIWtmzsURRlUTQSe0lZRFglfuT6Qe25z8CBJn6_";
QByteArray authHeader = "Bearer " + accessToken.toUtf8();

request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
request.setRawHeader("Authorization", authHeader);
// 准备POST数据
QByteArray postData;
postData.append("session_id=9a77571d-b687-4325-bbff-716ff1466ea2&content=[{\"role\":\"system\",\"content\":\"你是一只企鹅宠物，我是你的主人\"},{\"role\":\"user\",\"content\":\""+message.toUtf8()+"\"}]&max_context_length=5&params={\"model\":\"gpt-3.5-turbo\",\"temperature\":1,\"max_tokens\":2048,\"presence_penalty\":0,\"frequency_penalty\":0,\"max_context_length\":5,\"voiceShortName\":\"zh-CN-XiaoxiaoNeural\",\"rate\":1,\"pitch\":1}"); // 根据API要求，构建合适的POST参数

// 发送POST请求
QNetworkReply *reply = manager.post(request, postData);

// 等待请求完成
QEventLoop loop;
QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
loop.exec();


// 获取返回值
if(reply->error() == QNetworkReply::NoError) {
QString response = reply->readAll();

      trayIcon->showMessage("YANG-PCpet", response);

} else {
qDebug() << "Error:" << reply->errorString();
}

// 清理
reply->deleteLater();

}



void Widget::on_pushButton_6_clicked()
{
QString disscus=ui->textEdit->toPlainText();
     GPT(disscus);
}

void Widget::on_pushButton_5_clicked()
{
     QPushButton *button = qobject_cast<QPushButton *>(sender());
     if (button)
     {
button->setEnabled(false); // 禁用按钮
// 执行事件程序
// ...
trayIcon->showMessage("pet", "喂食中。。。");
if(progress<100){
    progress+=1;
                settings.setValue("progress", progress);
}
if(eat>0){
     eat-=1;
          settings.setValue("eat", eat);
}
     ui->progressBar->setValue(progress);
     GPT("主人对你喂食");
     button->setEnabled(true); // 禁用按钮
     }
}


void Widget::on_pushButton_4_clicked()
{
     if(progress<100){
     progress+=1;
     settings.setValue("progress", progress);
     }
     if(clear<100){
      clear+=1;
     }
        settings.setValue("clear", clear);
      ui->progressBar->setValue(progress);
      GPT("主人为你洗澡");
}


void Widget::on_pushButton_3_clicked()
{
     clear = settings.value("clear").toInt();
      eat = settings.value("eat").toInt();
     fat = settings.value("fat").toInt();

      trayIcon->showMessage("YANG-PCpet", "健康度："+QString::number(fat)+"\n饥饿度:"+QString::number(eat)+"\n干净度："+QString::number(clear));

}
void Widget::executeCode()
{
      if(progress>0){
     progress-=1;
     settings.setValue("progress", progress);

      }
      if(eat<100){
     eat+=1;
     settings.setValue("eat", eat);

      }
      if(fat<100){
     fat+=1;
     settings.setValue("fat", fat);

      }
      if(clear>0){
    clear-=1;
     settings.setValue("clear", clear);

      }
      // 在这个槽函数中执行需要定期执行的代码
      qDebug() << "Executing code every 5 minutes";
}

void Widget::on_pushButton_2_clicked()
{
      QNetworkAccessManager *manager = new QNetworkAccessManager(this);
      QUrl url("https://api.vvhan.com/api/weather");
      QNetworkRequest request(url);

      // Set unsafe SSL configuration
      QSslConfiguration config = request.sslConfiguration();
      config.setPeerVerifyMode(QSslSocket::VerifyNone);
      request.setSslConfiguration(config);

      QNetworkReply *reply = manager->get(request);

      // Connect to the finished signal
      connect(reply, &QNetworkReply::finished, [=]() {
          if (reply->error() == QNetworkReply::NoError) {
              // Read the JSON data
              QByteArray data = reply->readAll();

              // Display the JSON data in a message box
              QJsonDocument jsonDoc = QJsonDocument::fromJson(QString(data).toUtf8());
              QJsonObject jsonObj = jsonDoc.object();

              // 获取数据
              QString city = jsonObj["city"].toString();
               QJsonObject jObj2 = jsonDoc["info"].toObject();
              QString high = jObj2 ["high"].toString();
              QString type = jObj2 ["type"].toString();
              QJsonObject jObj23 = jObj2["air"].toObject();
                   QString aqiname = jObj23 ["aqi_name"].toString();
              QString tip =jObj2["tip"].toString();
                   QString info = "主人好呀，今天"+city+type+",温度"+high+"空气质量"+aqiname;
               trayIcon->showMessage(tip, info);
          }
          else {
              // Display an error message
              QMessageBox::warning(this, "Error", reply->errorString());
          }

          // Clean up
          reply->deleteLater();
          manager->deleteLater();
      });
}

