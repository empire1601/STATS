#include "dialog_creationpop.h"
#include "ui_dialog_creationpop.h"
#include "qdebug.h"


Dialog_CreationPop::Dialog_CreationPop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_CreationPop)
{
    ui->setupUi(this);

    QObject::connect(this,SIGNAL(accepted()),this,SLOT(fermeture()));

}
void Dialog_CreationPop::fermeture()
{
    this->resu=new QIntList;
    qDebug()<<resu->count();
    resu->operator +=(this->ui->nbVar->value());
    resu->operator +=(this->ui->taillepop->value());

    emit Fermer(resu);
}

Dialog_CreationPop::~Dialog_CreationPop()
{

    delete ui;
}

