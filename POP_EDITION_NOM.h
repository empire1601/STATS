#ifndef POP_EDITION_NOM_H
#define POP_EDITION_NOM_H

#include <QtGui>

class POP_EDITION_NOM : public QDialog
{
    Q_OBJECT
    public:
        POP_EDITION_NOM(int larg, QString n, QWidget *parent);
        void show();
    public slots:
        void Valid_Text(int n);
    signals:
        void Ferme(QString texte);
    private:
        QLineEdit *saisie;
        void keyPressEvent(QKeyEvent *event);
};

#endif // POP_EDITION_NOM_H
