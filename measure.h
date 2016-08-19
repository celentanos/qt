#ifndef MEASURE_H
#define MEASURE_H

#include <QString>
#include <QDate>

class Measure
{
public:
    Measure();

    QString getStaName() const;
    void setStaName(const QString &value);

    QString getCn() const;
    void setCn(const QString &value);

    QDate getDate() const;
    void setDate(const QDate &value);

    double getLat() const;
    void setLat(double value);

    double getLon() const;
    void setLon(double value);

    double getHigh() const;
    void setHigh(double value);

    QString getStaId() const;
    void setStaId(const QString &value);

    QString getSouId() const;
    void setSouId(const QString &value);

    double getTg() const;
    void setTg(double value);

    int getTgq() const;
    void setTgq(int value);

    double getRr() const;
    void setRr(double value);

    int getRrq() const;
    void setRrq(int value);

private:
    QString staId;                  /// Station identifier
    QString souId;                  /// Source identifier
    QString staName;                /// Station name
    QString cn;                     /// country code (ISO3116 countrycodes): DE, ...
    QDate date;
    double tg;                      /// Mean temperature
    int tgq;                        /// Temperature quality
    double rr;                      /// Precipitation
    int rrq;                        /// Precipitation quality
    double lat;                     /// latitude
    double lon;                     /// longitude
    double high;                    /// Station elevation in meters

};

#endif // MEASURE_H
