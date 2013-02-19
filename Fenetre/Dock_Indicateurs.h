#ifndef DOCK_INDICATEURS_H
#define DOCK_INDICATEURS_H

#include <QtGui>

class DOCK_INDICATEURS : public QDockWidget
{
    Q_OBJECT
    public:
        DOCK_INDICATEURS(QString Info, QWidget *parent=0);
    public slots:
        void setInfo(QString Info);
    private:
        QString information;
        QWidget *contenu;
        QHBoxLayout *layout;
        QLabel *texte;
};

#endif // DOCK_INDICATEURS_H
