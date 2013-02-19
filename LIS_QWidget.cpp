#include "LIS_QWidget.h"

//QAbstractButton
LIS_QWidget::LIS_QWidget(QWidget *b)
{
    elt = b;
    pNext=0;
}
void LIS_QWidget::AdQWidget(QWidget *b)
{
    if(!pNext)
    {
        pNext = new LIS_QWidget(b);
    }
    else
    {
        pNext->AdQWidget(b);
    }
}
QWidget *LIS_QWidget::RechQWidget(int id)
{
    if(!id)
    {return elt;}
    else
    {
       if(pNext)
       {
          return pNext->RechQWidget(id-1) ;
       }
       else
       {
           return 0;
       }
    }
}
int LIS_QWidget::nb(int n)
{
    if(pNext)
    {return pNext->nb(n+1);}
    else
    {return n;}
}

//QLineEdit
LIS_QLineEdit::LIS_QLineEdit(QString t, int mod)
{
    setTitle(t);
    pNext=0;
    text="";
    if(mod==1)
    {
        QObject::connect(elt, SIGNAL(textEdited(QString)), this, SLOT(ControlText(QString)));
    }
}
void LIS_QLineEdit::setTitle(QString t)
{
    elt = new QLineEdit();
    title = new QLabel();
            title->setText(t);
}
QString LIS_QLineEdit::ct()
{
    return elt->text();
}
void LIS_QLineEdit::AdQLineEdit(QString t, int mod)
{
    if(!pNext)
    {
        pNext = new LIS_QLineEdit(t,mod);
    }
    else
    {
        pNext->AdQLineEdit(t,mod);
    }
}
QLineEdit *LIS_QLineEdit::RechLineEdit(int id)
{
    if(!id)
    {return elt;}
    else
    {
       if(pNext)
       {
          return pNext->RechLineEdit(id-1) ;
       }
       else
       {
           return 0;
       }
    }
}
QLabel *LIS_QLineEdit::RechTitle(int id)
{
    if(!id)
    {return title;}
    else
    {
       if(pNext)
       {
          return pNext->RechTitle(id-1) ;
       }
       else
       {
           return 0;
       }
    }
}
int LIS_QLineEdit::nb(int n)
{
    if(pNext)
    {return pNext->nb(n+1);}
    else
    {return n;}
}
void LIS_QLineEdit::ControlText(const QString &t)
{
    bool ok;
    int i=t.toInt(&ok);
    if((ok) or (t==""))
    {text=t;}
    else
    {elt->setText(text);}
}

//QComboBox
LIS_QComboBox::LIS_QComboBox(QString t, QStringList l)
{
    setTitle(t);
    elt = new QComboBox();
    elt->addItems(l);
    pNext=0;
}
void LIS_QComboBox::setTitle(QString t)
{
    title = new QLabel();
            title->setText(t);
}
QString LIS_QComboBox::ct()
{
    return elt->currentText();
}
void LIS_QComboBox::AdQComboBox(QString t, QStringList l)
{
    if(!pNext)
    {
        pNext = new LIS_QComboBox(t,l);
    }
    else
    {
        pNext->AdQComboBox(t,l);
    }
}
QComboBox *LIS_QComboBox::RechComboBox(int id)
{
    if(!id)
    {return elt;}
    else
    {
       if(pNext)
       {
          return pNext->RechComboBox(id-1) ;
       }
       else
       {
           return 0;
       }
    }
}
QLabel *LIS_QComboBox::RechTitle(int id)
{
    if(!id)
    {return title;}
    else
    {
       if(pNext)
       {
          return pNext->RechTitle(id-1) ;
       }
       else
       {
           return 0;
       }
    }
}
int LIS_QComboBox::nb(int n)
{
    if(pNext)
    {return pNext->nb(n+1);}
    else
    {return n;}
}

//QLabel
LIS_QLabel::LIS_QLabel(QString t)
{
    elt = new QLabel;
    elt->setText(t);
    pNext=0;
}
QString LIS_QLabel::ct()
{
    if(elt)
    {    return elt->text();}
    else
    {return 0;}
}
void LIS_QLabel::AdQLabel(QString t)
{
    if(!pNext)
    {
        pNext = new LIS_QLabel(t);
    }
    else
    {
        pNext->AdQLabel(t);
    }
}
QLabel *LIS_QLabel::RechQLabel(int id)
{
    if(!id)
    {return elt;}
    else
    {
       if(pNext)
       {
          return pNext->RechQLabel(id-1) ;
       }
       else
       {
           return 0;
       }
    }
}
int LIS_QLabel::nb(int n)
{
    if(pNext)
    {return pNext->nb(n+1);}
    else
    {return n;}
}

//QRadioButton
LIS_QRadioButton::LIS_QRadioButton(QString t)
{
    elt = new QRadioButton(t);
    pNext=0;
}
QString LIS_QRadioButton::ct()
{
    if(elt->isChecked())
    {
        return elt->text();
    }
    else
    {
        if(pNext)
        {return pNext->ct();}
        else
        {return "";}
    }
}
void LIS_QRadioButton::AdQRadioButton(QString t)
{
    if(!pNext)
    {
        pNext = new LIS_QRadioButton(t);
    }
    else
    {
        pNext->AdQRadioButton(t);
    }
}
QRadioButton *LIS_QRadioButton::RechQRadioButton(int id)
{
    if(!id)
    {return elt;}
    else
    {
       if(pNext)
       {
          return pNext->RechQRadioButton(id-1) ;
       }
       else
       {
           return 0;
       }
    }
}
int LIS_QRadioButton::nb(int n)
{
    if(pNext)
    {return pNext->nb(n+1);}
    else
    {return n;}
}
