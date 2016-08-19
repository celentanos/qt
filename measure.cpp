#include "measure.h"

Measure::Measure()
{
    staId = "";
    souId = "";
    staName = "";
    cn = "";
    tg = 0.0;
    tgq = 0;
    rr = 0.0;
    rrq = 0;
    lat = 0.0;
    lon = 0.0;
    high = 0.0;
}

QString Measure::getStaName() const
{
    return staName;
}

void Measure::setStaName(const QString &value)
{
    staName = value;
}

QString Measure::getCn() const
{
    return cn;
}

void Measure::setCn(const QString &value)
{
    cn = value;
}

QDate Measure::getDate() const
{
    return date;
}

void Measure::setDate(const QDate &value)
{
    date = value;
}

double Measure::getLat() const
{
    return lat;
}

void Measure::setLat(double value)
{
    lat = value;
}

double Measure::getLon() const
{
    return lon;
}

void Measure::setLon(double value)
{
    lon = value;
}

double Measure::getHigh() const
{
    return high;
}

void Measure::setHigh(double value)
{
    high = value;
}

QString Measure::getStaId() const
{
    return staId;
}

void Measure::setStaId(const QString &value)
{
    staId = value;
}

QString Measure::getSouId() const
{
    return souId;
}

void Measure::setSouId(const QString &value)
{
    souId = value;
}

double Measure::getTg() const
{
    return tg;
}

void Measure::setTg(double value)
{
    tg = value;
}

int Measure::getTgq() const
{
    return tgq;
}

void Measure::setTgq(int value)
{
    tgq = value;
}

double Measure::getRr() const
{
    return rr;
}

void Measure::setRr(double value)
{
    rr = value;
}

int Measure::getRrq() const
{
    return rrq;
}

void Measure::setRrq(int value)
{
    rrq = value;
}
