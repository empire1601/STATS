#include "POPULATION.h"
#include "qdebug.h"

POPULATION::POPULATION(QWidget *parent, int nbVar, int tpop) : QStandardItemModel(parent)
{
    qDebug()<<"Création d'une population";

    if(!nbVar)
    {
        Dialog_CreationPop *createpop=new Dialog_CreationPop;
        QObject::connect(createpop,SIGNAL(Fermer(QIntList*)),this,SLOT(init_Pop(QIntList*)));
        createpop->exec();
        qDebug()<<"Sortie de l'execution du dialog";
    }
    else
    {
        if(tpop)
        {
            this->setColumnCount(nbVar);
            this->setRowCount(tpop);
            table.setTaille(tpop);
            for(int i =0;i<nbVar;i++)
            {
                table.AdVar();
            }
        }
    }
    nom = "Population";
}
void POPULATION::init_Pop(QIntList *parametre)
{
    qDebug()<<"Creation d'une population à partir des paramètres utilisateur";
    int nbVar=parametre->operator [](0);
    int tpop=parametre->operator [](1);
    delete parametre;

    this->setColumnCount(nbVar);
    this->setRowCount(tpop);
    table.setTaille(tpop);
    for(int i =0;i<nbVar;i++)
    {
        table.AdVar();
    }
    nom = "Population";
}
ResumMulti *POPULATION::Resumes(QIntList id)
{
    return this->table.Resum(id);
}

int POPULATION::Taille()
{
    return rowCount();
}
QString POPULATION::Nom()
{
    return nom;
}
void POPULATION::setNom(QString n)
{
    nom=n;
}
int POPULATION::rowCount(const QModelIndex &parent) const
{
    return table.Taille();
}
int POPULATION::NbValide(int i)
{
    return table[i].NbValide();
}
QString POPULATION::NbValideString(int i)
{
    QString t;
    t.setNum(NbValide(i));
    return t;
}
double POPULATION::Somme(int i)
{
    return table[i].Somme();
}
double POPULATION::Moyenne(int i)
{
    return table[i].Moyenne();
}
double POPULATION::Variance(int i)
{
    return table[i].Variance();
}
double POPULATION::Max(int i)
{
    return QVar(table.at(i)).Max();
}
double POPULATION::Min(int i)
{
    return table[i].Min();
}
int POPULATION::columnCount(const QModelIndex &parent) const
{
    return table.NbVar();
}
int POPULATION::columnType(const int id) const
{
    return table[id].Type();
}
QVar POPULATION::Var(int id)
{
    return this->table[id];
}
QVar *POPULATION::pVar(int id)
{
    return this->table.Variable(id);
}

QVariant POPULATION::data(const QModelIndex &index, int role) const
{
    if(not index.isValid())
    {return QVariant();}
    if(role==Qt::BackgroundRole)
    {
        if(QVar(table.at(index.column())).isValide(index.row()))
        {
            return QColor(Qt::white);
        }
        else
        {
            return QColor(Qt::gray);
        }
    }
    if(role != Qt::DisplayRole)
    {return QVariant();}
    if(index.row() >= rowCount() or index.column() >= columnCount())
    {return QVariant();}
    return QVariant(table.Value(index.column(),index.row()));
}
QVariant POPULATION::headerData(int section, Qt::Orientation orientation, int role) const
{
    QString sec;
    sec.setNum(section+1);
    if(role==Qt::BackgroundRole and orientation == Qt::Horizontal)
    {
        switch(table[section].Type())
        {
            case TYPES::INCONNU :
                        return QColor(Qt::white);
                        break;
            case TYPES::BINOMIAL :
                        return QColor(Qt::cyan);
                        break;
            case TYPES::QUALITATIF_ORDINAL :
                        return QColor(Qt::blue);
                        break;
            case TYPES::QUALITATIF_PURE :
                        return QColor(Qt::green);
                        break;
            case TYPES::QUANTITATIF_DISCRET :
                        return QColor(Qt::yellow);
                        break;
            case TYPES::QUANTITATIF_CONTINU_PURE :
                        return QColor(Qt::red);
                        break;
            case TYPES::QUANTITATIF_CONTINU_BORNE :
                        return QColor(Qt::magenta);
                        break;

        }
    }
    if(role != Qt::DisplayRole)
    {return QVariant();}
    if(orientation == Qt::Horizontal)
    {
         if(table.at(section).Nom()=="Variable")
            {return QVariant("Variable "+sec);}
         else
            {return table.at(section).Nom();}
    }
    else
    {return QVariant("Individu "+ sec);}
}
Qt::ItemFlags POPULATION::flags(const QModelIndex &index) const
{
    if(not index.isValid())
    {return Qt::ItemIsEnabled;}
    return (QAbstractItemModel::flags(index) | Qt::ItemIsEditable);
}
bool POPULATION::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() and role == Qt::EditRole)
    {
        table[index.column()].setRow(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    else
    {
        return false;
    }
}
bool POPULATION::setData(const int x, const int y, const QVariant &value, int role)
{
    if(role == Qt::EditRole and x<columnCount() and y<rowCount())
    {
        table[x].setRow(y,value.toString());
        emit dataChanged(this->index(x,y), this->index(x,y));
        return true;
    }
    else
    {
        return false;
    }
}
QModelIndex POPULATION::createIndex(int row, int column, int id) const
{
    return QAbstractItemModel::createIndex(row, column, id);
}
int POPULATION::ValideValues(int id_var, QStringList val, QBoolList b)
{
    return table[id_var].Ch_Valide_Values(val, b);
}

QVar & POPULATION::Table(int id)
{
    return table[id];
}
QStringList POPULATION::Modalites(int id)
{
    return table[id].Modalites();
}
QStringList POPULATION::AllModalites(int id)
{
    return table[id].AllModalites();
}
QBoolList POPULATION::AllAllow(int id)
{
    return table[id].AllAllow();
}
VAL_GROUP * POPULATION::Grouped_Values(int id)
{
    return table[id].Val_Group();
}


void POPULATION::addRows(int rows, const QModelIndex &index)
{
    beginInsertRows(QModelIndex(),rowCount(),rowCount()+rows-1);
        table.AdRows(rows);
    endInsertRows();
    emit dataChanged(QModelIndex(), QModelIndex());
}
bool POPULATION::addColumn()
{
    beginInsertColumns(QModelIndex(),columnCount(), columnCount());
        table.AdVar();
    endInsertColumns();
    return true;
}

bool POPULATION::insertRows(int position, int rows, const QModelIndex &index)
{
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for(int row=0; row<rows; row++)
    {
        string_list.insert(position, "");
    }
    endInsertRows();
    return true;
}
bool POPULATION::removeRows(int position, int rows, const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);
    for(int row=0; row<rows; row++)
    {
        table.SupRow(position);
    }
    endRemoveRows();
    return true;
}
bool POPULATION::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(QModelIndex(), column, column+count-1);
    for(int c=0; c<count; c++)
    {
        table.SupVar(column);
    }
    endRemoveColumns();
    return true;
}
int POPULATION::Type(int i)
{
    return table[i].Type();
}

void POPULATION::setNomVar(int id, QString n)
{
    table[id].setNom(n);
    emit dataChanged(QModelIndex(), QModelIndex());
}
void POPULATION::setTypeVar(int id, int v)
{
    table[id].setType(v);
    emit dataChanged(QModelIndex(), QModelIndex());
}
void POPULATION::setTypeVar(int id, int v, QStringList m)
{
    table[id].setType(v, m);
    emit dataChanged(QModelIndex(), QModelIndex());
}
