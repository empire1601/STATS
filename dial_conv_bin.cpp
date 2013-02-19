#include "dial_conv_bin.h"
#include "ui_dial_conv_bin.h"

DIAL_CONV_BIN::DIAL_CONV_BIN(QWidget *parent) : QDialog(parent), ui(new Ui::DIAL_CONV_BIN)
{
    m1="";
    m2="";
    ui->setupUi(this);
    QObject::connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(Ed_Val1(QString)));
    QObject::connect(ui->lineEdit_2, SIGNAL(textChanged(QString)), this, SLOT(Ed_Val2(QString)));
    QObject::connect(this, SIGNAL(accepted()), this, SLOT(Press_OK()));
}
void DIAL_CONV_BIN::Press_OK()
{
    QStringList ch;
    ch+=m1;
    ch+=m2;

    emit Ferme(ch);
}
void DIAL_CONV_BIN::Ed_Val1(QString t)
{
    m1=t;
}
void DIAL_CONV_BIN::Ed_Val2(QString t)
{
    m2=t;
}

DIAL_CONV_BIN::~DIAL_CONV_BIN()
{
    delete ui;
}
