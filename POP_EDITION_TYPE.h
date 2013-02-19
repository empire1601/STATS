#ifndef POP_EDITION_TYPE_H
#define POP_EDITION_TYPE_H

#include <QtGui>

class POP_EDITION_TYPE : public QDialog
{
    Q_OBJECT
    public:
        POP_EDITION_TYPE(int t, QWidget *parent);
        void show();
    public slots:
        void Valid_id(int t);
    signals:
        void Ferme(int type);
    private:
        QListWidget *choix;
        void keyPressEvent(QKeyEvent *event);
};

#endif // POP_EDITION_TYPE_H
