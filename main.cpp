
#include "widget.h"
#include "form.h"
#include <QApplication>
#include "widget.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLabel>
#include <QMovie>
#include <QGraphicsDropShadowEffect>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "YANG-PCpet_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    Form ss;
      Widget w;
    QGraphicsDropShadowEffect effect;
    effect.setBlurRadius(30);
    effect.setColor(Qt::black);
    effect.setOffset(0);

   w.setGraphicsEffect(&effect);

    ss.show();

    w.show();
    QString programDirPath = QCoreApplication::applicationDirPath();
    qDebug() << "程序所在目录：" << programDirPath;
    return a.exec();
}
