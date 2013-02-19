#ifndef DIALASSISTANT_H
#define DIALASSISTANT_H

#include "LIS_QWidget.h"

class DIAL_ASSISTANT : public QDialog
{
    Q_OBJECT
public:
    DIAL_ASSISTANT(QWidget *p,bool pre = false, bool fin = false);

    void show();
    void setTitle(QString title);

    void AdSaisieTexte(QString title="", int mod=0);
    void AdChTexte(QString title,QStringList liste);
    void AdDescTexte(QString texte);
    void AdRadTexte(QString texte);

    QLabel *titleSaisie(int id=1);
    QLineEdit *saisie(int id=1);
        QString textSaisie(int id=1);
    QLabel *titleChoix(int id=1);
    QComboBox *choix(int id=1);
        QString textChoix(int id=1);
    QLabel *description(int id=1);
    QRadioButton *radio(int id=1);
        QString textRadio();
    QString resultat(int id=1);
    int nbResult;

    bool terminer;

    ~DIAL_ASSISTANT();

public slots:
    void modif(const QString & t);
    void bSuiv();
    void bPre();
signals:
    void renseignes(bool b);
    void suivant();
    void precedent();

private:

    QWidget *element(int id=1);
    void AdQWidget(QWidget *b);

    QVBoxLayout *layout;
    QHBoxLayout *layoutBout;
        QPushButton *boutonSuiv;
        QPushButton *boutonPre;

    LIS_QLineEdit *saisieTexte;
    LIS_QComboBox *chTexte;
    LIS_QLabel *descTexte;
    LIS_QRadioButton *radTexte;

    LIS_QWidget *elt;

};

#endif // DIALASSISTANT_H
