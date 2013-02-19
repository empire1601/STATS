#include "POP_EDITION_NOM.h"
#include "qdebug.h"

POP_EDITION_NOM::POP_EDITION_NOM(int larg, QString n, QWidget *parent) : QDialog(parent,Qt::Popup)
{
    saisie = new QLineEdit(this);
    saisie->setText(n);
    saisie->setMaximumSize(larg,23);
    saisie->setMinimumSize(larg,23);
    saisie->selectAll();

    QObject::connect(this, SIGNAL(finished(int)), this, SLOT(Valid_Text(int)));
}
void POP_EDITION_NOM::Valid_Text(int n)
{
    emit Ferme(saisie->text());
}
void POP_EDITION_NOM::show()
{
    saisie->activateWindow();
    QDialog::show();
}
void POP_EDITION_NOM::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Return)
    {
        close();
    }
}
