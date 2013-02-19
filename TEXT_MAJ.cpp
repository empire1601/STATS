#include "TEXT_MAJ.h"

TEXT_MAJ::TEXT_MAJ(const QString t) : QString(t)
{
    this->setUnicode(toUpper().data(),size());
}
TEXT_MAJ::TEXT_MAJ()
{

}
