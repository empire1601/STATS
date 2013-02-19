#include "dial_regrouper_val.h"
#include "ui_dial_regrouper_val.h"
#include "qdebug.h"

DIAL_REGROUPER_VAL::DIAL_REGROUPER_VAL(VAL_GROUP *val, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DIAL_REGROUPER_VAL)
{
    this->val_grp=val;
    select=false;
    ui->setupUi(this);
    ui->Liste->setModel(val);
    ui->Liste->header()->hide();
    ui->Liste->setSelectionMode(QAbstractItemView::ExtendedSelection);
    if(!ui->Liste->model()->rowCount())
    {
        qDebug()<<"Model vide";
    }
}

DIAL_REGROUPER_VAL::~DIAL_REGROUPER_VAL()
{
    delete ui;
}

void DIAL_REGROUPER_VAL::on_Liste_clicked(QModelIndex p)
{
        QItemSelectionModel *selection = this->ui->Liste->selectionModel();
        QModelIndexList listeSelections = selection->selectedIndexes();

        elementsSelectionnes.clear();
        for (int i = 0 ; i < listeSelections.size() ; i++)
        {
            QVariant elementSelectionne = val_grp->data(listeSelections[i], Qt::DisplayRole);
            elementsSelectionnes += elementSelectionne.toString();
        }

}
void DIAL_REGROUPER_VAL::on_buttonBox_accepted()
{
    for(int i=0;i<elementsSelectionnes.size();i++)
    {
        this->val_grp->Group(this->ui->lineEdit->text(), elementsSelectionnes[i]);
    }
}
