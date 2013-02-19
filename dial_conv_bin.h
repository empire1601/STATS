#ifndef DIAL_CONV_BIN_H
#define DIAL_CONV_BIN_H

#include <QtGui>

namespace Ui
{
    class DIAL_CONV_BIN;
}

class DIAL_CONV_BIN : public QDialog
{
    Q_OBJECT

public:
    explicit DIAL_CONV_BIN(QWidget *parent = 0);
    ~DIAL_CONV_BIN();
public slots:
    void Ed_Val1(QString t);
    void Ed_Val2(QString t);

    void Press_OK();
signals:
    void Ferme(QStringList m);

private:
    Ui::DIAL_CONV_BIN *ui;
    QString m1;
    QString m2;
};

#endif // DIAL_CONV_BIN_H
