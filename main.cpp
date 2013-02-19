/* Main.cpp */

#include "Fenetre/FENETRE_PRINCIPALE.h"

int main(int argc, char *argv[])
{
    qDebug()<<"Début";
    QApplication app(argc, argv);


   QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    //Création d'une fenêtre
    FENETRE_PRINCIPALE maFenetre;

    // Affichage de la fenêtre
    maFenetre.show();

    return app.exec();


    qDebug()<<"Fin";
}
