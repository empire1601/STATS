/* Main.cpp */

#include "Fenetre/FENETRE_PRINCIPALE.h"

int main(int argc, char *argv[])
{
    qDebug()<<"D�but";
    QApplication app(argc, argv);


   QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    //Cr�ation d'une fen�tre
    FENETRE_PRINCIPALE maFenetre;

    // Affichage de la fen�tre
    maFenetre.show();

    return app.exec();


    qDebug()<<"Fin";
}
