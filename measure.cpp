#include "measure.h"

Measure::Measure()
{
    staId = "";
    souIdTg = "";
    souIdRr = "";
    staName = "";
    cn = "";
    tg = MISSING_D_VAL;
    tgq = MISSING_I_Q;
    rr = MISSING_D_VAL;
    rrq = MISSING_I_Q;
    lat = MISSING_D_VAL;
    lon = MISSING_D_VAL;
    high = MISSING_D_VAL;
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

QString Measure::getSouIdTg() const
{
    return souIdTg;
}

void Measure::setSouIdTg(const QString &value)
{
    souIdTg = value;
}

QString Measure::getSouIdRr() const
{
    return souIdRr;
}

void Measure::setSouIdRr(const QString &value)
{
    souIdRr = value;
}
