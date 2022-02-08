#include "principal.h"

#include <QApplication>
#include <QTranslator>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QDateTime tiempo(QDateTime::currentDateTime());
    QApplication a(argc, argv);
    if(!tiempo.timeZoneAbbreviation().contains("Sudamérica")){
        QTranslator T;
        QStringList langs;
        langs << "Español" << "Ingles" << "Japones";
        const QString lang = QInputDialog::getItem(NULL,
                                                   "Idiomas",
                                                   "Selecciona un idioma",
                                                   langs);
        if(lang == "Ingles"){
            T.load(":/new/prefix1/MiPaint_en.qm");
        }else if(lang == "Japones"){
            T.load(":/new/prefix1/MiPaint_jp.qm");
        }
        if(lang != "Español"){
            a.installTranslator(&T);
        }
    }
    Principal w;
    w.show();
    return a.exec();
}
