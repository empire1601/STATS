#include "DIAL_VAL_MANQUANTES.h"
#include "qdebug.h"

CHECK_ID::CHECK_ID(int i, QString nom, QWidget *parent) : QCheckBox(nom, parent)
{
    id=i;
    QObject::connect(this, SIGNAL(toggled(bool)), this, SLOT(t_select(bool)));
}
void CHECK_ID::t_select(bool b)
{
    emit select(id, b);
}

LIST_CHECK_MOD::LIST_CHECK_MOD(QStringList mod, QBoolList valide) : QListWidget()
{

       for (int i = 0; i < mod.size(); i++)
       {
           QListWidgetItem *item = new QListWidgetItem("", this);
           item->setSizeHint(QSize(200,40));

           addItem(item);

           QWidget* w = new QWidget();

           CHECK_ID* b = new CHECK_ID(i, mod.at(i), w);
            b->setChecked(valide.at(i));
            QObject::connect(b, SIGNAL(select(int,bool)), this, SLOT(t_select(int,bool)));

           QHBoxLayout* hlayout = new QHBoxLayout();
           hlayout->setMargin(10);
           hlayout->addWidget(b);

           w->setLayout(hlayout);

           setItemWidget(item, w);
       }

}
void LIST_CHECK_MOD::t_select(int id, bool b)
{
    emit select(id, b);
}

DIAL_VAL_MANQUANTES::DIAL_VAL_MANQUANTES(QStringList mod, QBoolList valide, QWidget *parent) : QDialog(parent)
{
    data=valide;
    liste = new LIST_CHECK_MOD(mod, valide);
    legende = new QLabel("<i>Décochez les valeurs que vous ne voulez pas prendre en compte</i>");
    layout = new QVBoxLayout();
    layout->addWidget(legende);
    layout->addWidget(liste);
    OK = new QPushButton("Ok");
    layout->addWidget(OK);
    setLayout(layout);
    QObject::connect(liste, SIGNAL(select(int,bool)), this, SLOT(Select_Check(int,bool)));
    QObject::connect(OK, SIGNAL(clicked()), this, SLOT(Valid_OK()));
}
void DIAL_VAL_MANQUANTES::Valid_OK()
{
    emit Ferme(data);
    close();
}
void DIAL_VAL_MANQUANTES::Select_Check(int id, bool b)
{
    data.replace(id, b);
}

