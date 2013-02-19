/*#ifndef TAP_CROISE_H
#define TAP_CROISE_H
#include "QtGui"

class MODALITE : public QStringList
{
    public:
    MODALITE()
    {

    }
    void Ad_Mod(QString mod)
    {
        var.append(mod);
    }


    private:
    QString nom;
};
class TAP_Croise
{
    public:
    VARIABLE()
    {

    }
    void Ad_Var(QString nom)
    {
        var.append(MODALITE());
    }
    void Ad_Mod(int id, QString mod)
    {
        var[id].Ad_Mod(mod);
    }
    operator [](int id)
    {
        int p=id%
        return  var[]
    }

    private:
    QList<MODALITE> var;

};




#endif // TAP_CROISE_H*/
