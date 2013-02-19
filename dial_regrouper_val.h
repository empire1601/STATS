#ifndef DIAL_REGROUPER_VAL_H
#define DIAL_REGROUPER_VAL_H

#include "VAL_GROUP.h"

namespace Ui {
class DIAL_REGROUPER_VAL;
}

class DIAL_REGROUPER_VAL : public QDialog
{
    Q_OBJECT
    
public:

    explicit DIAL_REGROUPER_VAL(VAL_GROUP *val, QWidget *parent = 0);
    ~DIAL_REGROUPER_VAL();

private slots:
    void on_Liste_clicked(QModelIndex p);
    void on_buttonBox_accepted();//Actions à faire à la fermeture de la fenêtre
    
private:
    Ui::DIAL_REGROUPER_VAL *ui;
    bool select;
    VAL_GROUP* val_grp;
    QStringList elementsSelectionnes;
};



#endif // DIAL_REGROUPER_VAL_H
