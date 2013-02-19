#ifndef DIAL_CONV_ORD_H
#define DIAL_CONV_ORD_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QListView>
#include <QStringListModel>
#include <QLayout>
#include <QScrollBar>
#include <QPushButton>



class DIAL_CONV_ORD : public QDialog
{
    Q_OBJECT
    public:
        DIAL_CONV_ORD(QStringList d, QWidget *parent);
    public slots:
        void editBarre(QModelIndex i);
        void editList(int i);
        void Press_OK();
    signals :
        void Ferme(QStringList t);

    private:
        QStringListModel *data;
        QScrollBar *barre;
        QLabel *legende;
        QPushButton *OK;

        QListView *liste;

        QHBoxLayout *layouth;
        QVBoxLayout *layout;

        int id_courant;
};

#endif // DIAL_CONV_ORD_H
