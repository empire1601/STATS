#ifndef LIS_QWIDGET_H
#define LIS_QWIDGET_H

#include <QtGui>

//QWidget
class LIS_QWidget
{
public:
    LIS_QWidget(QWidget *b);
    void AdQWidget (QWidget *b);
    QWidget *RechQWidget(int id);
    LIS_QWidget *pNext;

    int nb(int n=1);

private:
    QWidget *elt;
};

//QLineEdit
class LIS_QLineEdit:public QObject
{
    Q_OBJECT
public:
    LIS_QLineEdit(QString t, int mod=0);
    void setTitle(QString t);
    void AdQLineEdit(QString t,int mod=0);
    QLineEdit *RechLineEdit(int id);
    QLabel *RechTitle(int id);
    LIS_QLineEdit *pNext;

    QString ct();

    int nb(int n=1);
public slots:
    void ControlText(const QString &t);

private:
    QLabel *title;
    QLineEdit *elt;
    QString text;
};

//QComboBox
class LIS_QComboBox
{
public:
    LIS_QComboBox(QString t, QStringList l);
    void setTitle(QString t);
    void AdQComboBox (QString t, QStringList l);
    QComboBox *RechComboBox(int id);
    QLabel *RechTitle(int id);
    LIS_QComboBox *pNext;

    QString ct();

    int nb(int n=1);

private:
    QLabel *title;
    QComboBox *elt;
};

//QLabel
class LIS_QLabel
{
public:
    LIS_QLabel(QString t);
    void AdQLabel (QString t);
    QLabel *RechQLabel(int id);
    LIS_QLabel *pNext;

    QString ct();

    int nb(int n=1);

private:
    QLabel *elt;
};

//QRadioButton
class LIS_QRadioButton
{
public:
    LIS_QRadioButton(QString t);
    void AdQRadioButton (QString t);
    QRadioButton *RechQRadioButton(int id);
    LIS_QRadioButton *pNext;

    QString ct();

    int nb(int n=1);

private:
    QRadioButton *elt;
};


#endif // LIS_QWIDGET_H
