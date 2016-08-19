#ifndef MEASURELIST_H
#define MEASURELIST_H

#include <iostream>
#include <QDebug>
#include <QList>
#include <QDate>

#include "measure.h"
#include "log.h"

class MeasureList : public QList<Measure *>
{
public:
    MeasureList();
    ~MeasureList();

    int isExistByStaId(const QString &id);
    void printMeasure(int index);

    QDate getDate() const;
    void setDate(const QDate &value);

    QString getCn() const;
    void setCn(const QString &value);

private:
    QString cn;
    QDate date;
};

#endif // MEASURELIST_H
