#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "judge.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "plant_expert_system_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    init_tree();
    MainWindow w;
    w.setWindowTitle("植物识别系统");
    w.show();


    return a.exec();
}
