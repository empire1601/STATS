#include "DIAL_CONV_ORD.h"

DIAL_CONV_ORD::DIAL_CONV_ORD(QStringList d, QWidget *parent) : QDialog(parent)
{
    id_courant=0;
    data=new QStringListModel();
    data->setStringList(d);
    liste = new QListView;
    liste->setModel(data);
    legende = new QLabel("<i>Classez les valeurs possibles <b>de la plus petite à la plus grande</b></i>");
    barre = new QScrollBar(Qt::Vertical);
    barre->setMinimum(0);
    barre->setMaximum(d.size()-1);
    layout = new QVBoxLayout();
    layouth = new QHBoxLayout();
    layout->addWidget(legende);
    layouth->addWidget(liste);
    layouth->addWidget(barre);
    layout->addLayout(layouth);
    OK = new QPushButton("Ok");
    layout->addWidget(OK);
    setLayout(layout);
    QObject::connect(liste, SIGNAL(pressed(QModelIndex)), this, SLOT(editBarre(QModelIndex)));
    QObject::connect(barre, SIGNAL(valueChanged(int)), this, SLOT(editList(int)));
    QObject::connect(OK, SIGNAL(clicked()), this, SLOT(Press_OK()));
}
void DIAL_CONV_ORD::Press_OK()
{
    emit Ferme(data->stringList());
    close();
}
void DIAL_CONV_ORD::editBarre(QModelIndex i)
{
    id_courant = i.row();
    barre->setValue(id_courant);
}
void DIAL_CONV_ORD::editList(int i)
{
    if(id_courant!=i)
    {
        QStringList ch = data->stringList();
        QString t = ch.at(i);
        ch.replace(i, ch.at(id_courant));
        ch.replace(id_courant, t);
        data->setStringList(ch);
        id_courant=i;
    }
}

