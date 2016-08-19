#include "eca_parser.h"

void EcaParser::run()
{
    switch (proc) {
    case ECA_P_PARSE:
        processParse();
        break;
    case ECA_P_TEST_DATES:
        processTestDates();
        break;
    default:
        Log::getInstance()->log(Log::FAILURE, "EcaParser: run: empty process!");
    }
}

void EcaParser::processParse()
{
    if(tgPath == "" || rrPath == "") {
        Log::getInstance()->log(Log::FAILURE, "EcaParser: processParse: Paths is empty!");
        return;
    }
    if(dateMeasure == "") {
        Log::getInstance()->log(Log::FAILURE, "EcaParser: processParse: Date is empty!");
        return;
    }
    if(cn == "") {
        Log::getInstance()->log(Log::FAILURE, "EcaParser: processParse: Country is empty!");
        return;
    }

    QDir tgDir = QDir(tgPath);
    QDir rrDir = QDir(rrPath);

    QStringList tgFileList = tgDir.entryList();
    QStringList rrFileList = rrDir.entryList();

    if(!tgFileList.contains(STATIONS)) {
        Log::getInstance()->log(Log::FAILURE, "EcaParser: processParse: stationx.txt in tgFileList not found!");
        return;
    }

    // einzelne Messungen anlegen ----------------------------------------------
    if(initStations(measureList, tgFileList))
        return;
    emit signalStationNumber(QString::number(measureList->size()));

    // parse TG ----------------------------------------------------------------
    if(parseTg(measureList, tgFileList, dateMeasure))
        return;

    // parse RR ----------------------------------------------------------------

    // Ausgabe -----------------------------------------------------------------
    Log::getInstance()->log(Log::INFO, "parsing finished...");
}

void EcaParser::processTestDates()
{
    if(dateFrom == "" || dateTo == "") {
        Log::getInstance()->log(Log::FAILURE, "EcaParser: processTestDates: one of date is empty!");
        return;
    }
    QDate dfrom = QDate::fromString(dateFrom, DATE_FORMAT);
    QDate dto = QDate::fromString(dateTo, DATE_FORMAT);
    if(dfrom.daysTo(QDate::currentDate()) < dto.daysTo(QDate::currentDate())) {
        Log::getInstance()->log(Log::FAILURE, "EcaParser: processTestDates: dateFrom > dateTo!");
        return;
    }
    while (dfrom.daysTo(QDate::currentDate()) >= dto.daysTo(QDate::currentDate())) {
        QString sdate;
        if(getDateString(dfrom, sdate))
            return;

        dfrom = dfrom.addDays(1);
    }
}

int EcaParser::getDateString(const QDate &d, QString &s)
{
    if(!d.isValid()) {
        Log::getInstance()->log(Log::FAILURE, "EcaParser: getDateString: date is invalid!");
        return -1;
    }
    s = QString::number(d.year());
    if(QString::number(d.month()).size() < 2)
        s += "0";
    s += QString::number(d.month());
    if(QString::number(d.day()).size() < 2)
        s += "0";
    s += QString::number(d.day());
    return 0;
}

int EcaParser::initStations(MeasureList *measureList, const QStringList &tgFileList)
{
    QFile file(tgPath + tgFileList.at(tgFileList.indexOf(STATIONS)));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Log::getInstance()->log(Log::FAILURE, "EcaParser: initStations: can't open stationx.txt!");
        return -1;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QStringList lines;
    lines.append(in.readAll().split("\n"));

    if(lines.size() - 1 < STATIONS_OFFSET) {
        Log::getInstance()->log(Log::FAILURE, "EcaParser: initStations: to few lines in station.txt!");
        return -1;
    }
    QStringList line;
    for (int i = STATIONS_OFFSET; i < lines.size(); ++i) {
        line = lines.at(i).split(SPLIT_SIGN);
        line.replaceInStrings(" ", "");                                         // remove spaces
        if(line.size() == STA_NUMBER) {
            if(line.at(STA_CN) == cn) {
                if(!measureList->isExistByStaId(line.at(STA_STAID))) {
                    Measure *m = new Measure();
                    m->setStaId(line.at(STA_STAID));
                    m->setStaName(line.at(STA_STANAME));
                    double lat;
                    double lon;
                    if(getLatLonFromString(line.at(STA_LAT), lat))
                        return -1;
                    if(getLatLonFromString(line.at(STA_LAT), lon))
                        return -1;
                    m->setLat(lat);
                    m->setLon(lon);
                    bool b;
                    line.at(STA_HIGH).toDouble(&b);
                    if(!b) {
                        Log::getInstance()->log(Log::ERROR, "EcaParser: initStations: string to double convert failed!");
                        return -1;
                    }
                    m->setHigh(line.at(STA_HIGH).toDouble());
                    measureList->setCn(cn);
                    measureList->setDate(QDate::fromString(dateMeasure, DATE_FORMAT));
                    measureList->append(m);
                }
            }
        }
    }
    return 0;
}

int EcaParser::parseTg(MeasureList *measureList, const QStringList &tgFileList, const QString &date)
{
    for (int i = 0; i < measureList->size(); ++i) {
        // Dateiname aus STAID bilden
        QString station = TG_FILE;
        station = station.leftJustified(station.size() + STAID_LENGTH - measureList->at(i)->getStaId().size(), '0');
        station += measureList->at(i)->getStaId() + ".txt";

        if(tgFileList.contains(station)) {
            QFile file(tgPath + tgFileList.at(tgFileList.indexOf(station)));
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                Log::getInstance()->log(Log::FAILURE, "EcaParser: run: can't open stationx.txt!");
                return -1;
            }
            QTextStream in(&file);
            in.setCodec("UTF-8");
            QStringList lines;
            lines.append(in.readAll().split("\n"));

            if(lines.size() - 1 < TG_OFFSET) {
                Log::getInstance()->log(Log::FAILURE, "EcaParser: run: to few lines in TG_STAIDxx.txt!");
                return -1;
            }
            bool b;
            QStringList line;
            for (int j = TG_OFFSET; j < lines.size(); ++j) {
                line = lines.at(j).split(SPLIT_SIGN);
                line.replaceInStrings(" ", "");                                 // remove spaces
                if(line.size() == TG_NUMBER) {
                    if(line.at(TG_DATE) == date) {
                        measureList->at(i)->setSouId(line.at(TG_SOUID));
//                        if(line.at(TG_Q_TG) != MISSING_Q || line.at(TG_TG) != MISSING_VAL) {
                        line.at(TG_Q_TG).toInt(&b);                         // check int convert
                        if(!b)
                            Log::getInstance()->log(Log::FAILURE, "EcaParser: run: string to double convert failed!");
                        measureList->at(i)->setTgq(line.at(TG_Q_TG).toInt());

                        line.at(TG_TG).toDouble(&b);                        // check double convert
                        if(!b)
                            Log::getInstance()->log(Log::FAILURE, "EcaParser: run: string to double convert failed!");
                        if(line.at(TG_Q_TG) != MISSING_Q)
                            measureList->at(i)->setTg(line.at(TG_TG).toDouble() * 0.1); // normaler Wert * 0.1
                        else
                            measureList->at(i)->setTg(line.at(TG_TG).toDouble());       // fehlender Wert = -9999
//                        }
                    }
                }
            }
        } else
            Log::getInstance()->log(Log::FAILURE, "EcaParser: run: station " + measureList->at(i)->getStaId() + " not found!");
    }
    return 0;
}

int EcaParser::slotClearStations()
{
    if(!measureList) {
        Log::getInstance()->log(Log::ERROR, "EcaParser: clearStations: measureList = 0!");
        return -1;
    }
    qDeleteAll(measureList->begin(), measureList->end());
    measureList->clear();
    emit signalStationNumber(QString::number(measureList->size()));
    return 0;
}

QString EcaParser::getStationColumnName(EcaParser::STA e)
{
    switch (e) {
    case (STA_STAID):
        return "STAID";
    case (STA_STANAME):
        return "STANAME";
    case (STA_CN):
        return "CN";
    case (STA_LAT):
        return "LAT";
    case (STA_LON):
        return "LON";
    case (STA_HIGH):
        return "HGHT";
    default:
        Log::getInstance()->log(Log::ERROR, "EcaParser: getStationColumnName: wrong value!");
        return "";
    }
}

int EcaParser::getLatLonFromString(QString s, double &d)
{
    QStringList slist = s.split(":");
    if(slist.size() != 3) {
        Log::getInstance()->log(Log::ERROR, "EcaParser: getLonTatFromString: wrong lon-lat format!");
        return -1;
    }
    slist.replaceInStrings("+", "");

    bool b;                                     // check convert
    for (int i = 0; i < slist.size(); ++i) {
        slist.at(i).toDouble(&b);
        if(!b) {
            Log::getInstance()->log(Log::ERROR, "EcaParser: getLonTatFromString: string to double convert failed!");
            return -1;
        }
    }
    d = slist.at(0).toDouble();                 // deg
    d += (slist.at(1).toDouble() / 60.0);       // min
    d += (slist.at(2).toDouble() / 6000.0);     // sec
    return 0;
}

EcaParser::EcaParser()
{
    tgPath = "";
    rrPath = "";
    dateMeasure = "";
    cn = "";
    measureList = 0;
}

int EcaParser::setFilePaths(QStringList list)
{
    if (list.size() < 2) {
        Log::getInstance()->log(Log::ERROR, "EcaParser: setFilePath: less than 2argumentsin the path-list!");
        return -1;
    }
    tgPath = list.at(0);
    rrPath = list.at(1);
    return 0;
}

int EcaParser::process(MeasureList *measureList, ECA_PROCESS p)
{
    if (measureList == 0) {
        Log::getInstance()->log(Log::ERROR, "EcaParser: parse: measureList-reference = 0!");
        return -1;
    }
    proc = p;
    this->measureList = measureList;
    if(!measureList->isEmpty()) {
        qDeleteAll(measureList->begin(), measureList->end());
        measureList->clear();
    }
    emit signalStationNumber(QString::number(measureList->size()));
    Log::getInstance()->log(Log::INFO, "process...");
    this->start();
    return 0;
}

QString EcaParser::getTgPath() const
{
    return tgPath;
}

void EcaParser::setTgPath(const QString &value)
{
    if(value.at(value.size() - 1) != '/') {
        tgPath = value + "/";
        return;
    }
    tgPath = value;
}

QString EcaParser::getRrPath() const
{
    return rrPath;
}

void EcaParser::setRrPath(const QString &value)
{
    if(value.at(value.size() - 1) != '/') {
        rrPath = value + "/";
        return;
    }
    rrPath = value;
}

QString EcaParser::getDateMeasure() const
{
    return dateMeasure;
}

void EcaParser::setDateMeasure(const QString &value)
{
    dateMeasure = value;
}

QString EcaParser::getCn() const
{
    return cn;
}

void EcaParser::setCn(const QString &value)
{
    cn = value;
}

QString EcaParser::getDateFrom() const
{
    return dateFrom;
}

void EcaParser::setDateFrom(const QString &value)
{
    dateFrom = value;
}

QString EcaParser::getDateTo() const
{
    return dateTo;
}

void EcaParser::setDateTo(const QString &value)
{
    dateTo = value;
}
