#include "measure_list.h"

MeasureList::MeasureList()
{

}

MeasureList::~MeasureList()
{
    qDeleteAll(this->begin(), this->end());
    this->clear();
}

int MeasureList::isExistByStaId(const QString &id)
{
    for (int i = 0; i < this->size(); ++i)
        if(this->at(i)->getStaId() == id)
            return -1;
    return 0;
}

QDate MeasureList::getDate() const
{
    return date;
}

void MeasureList::setDate(const QDate &value)
{
    date = value;
}

void MeasureList::printMeasure(int index)
{
    if(index > this->size() - 1) {
        Log::getInstance()->log(Log::FAILURE, "MeasureList: printMeasure: wront list-index!");
        return;
    }
    QString s = "Station:\t\t" + this->at(index)->getStaId() +
                "\n\tName:\t" + this->at(index)->getStaName() +
                "\n\tCountry:\t" + this->at(index)->getCn();
    std::cout << s.toUtf8().constData() << std::endl;
}

QString MeasureList::getCn() const
{
    return cn;
}

void MeasureList::setCn(const QString &value)
{
    cn = value;
}
