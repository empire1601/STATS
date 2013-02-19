#include "POP_EDITION_TYPE.h"

POP_EDITION_TYPE::POP_EDITION_TYPE(int t, QWidget *parent) : QDialog(parent,Qt::Popup)
{
    QStringList ch;
        ch+="Inconnu";
        ch+="Binaire";
        ch+="Qualitatif pure";
        ch+="Qualitatif ordinal";
        ch+="Quantitatif discret";
        ch+="Quantitatif continu";
        ch+="Quantitatif continu borné";
    choix = new QListWidget(this);
    choix->addItems(ch);
    choix->setCurrentRow(t);
    choix->setMaximumSize(150,200);
    choix->setMinimumSize(150,200);

    QObject::connect(this, SIGNAL(finished(int)), this, SLOT(Valid_id(int)));
}
void POP_EDITION_TYPE::Valid_id(int t)
{
    emit Ferme(choix->currentRow());
}
void POP_EDITION_TYPE::show()
{
    choix->activateWindow();
    QDialog::show();
}
void POP_EDITION_TYPE::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Return)
    {
        close();
    }
}
