#ifndef TEST_MODEL_SIMPLE_H
#define TEST_MODEL_SIMPLE_H

#include <QtGui>

class MODEL_SIMPLE : public QStringListModel
{
    public:
        MODEL_SIMPLE(QStringList liste);
};

#endif // TEST_MODEL_SIMPLE_H
