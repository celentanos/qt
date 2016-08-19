#include "helpers.h"

int compare(const QChar *a, int alen, const QChar *b, int blen)
{
    for (int i = 0; i < alen; ++i) {
        if(blen == i) return 1;
        if(*b > *a) return -1;
        if(*a > *b) return 1;
        a++;
        b++;
    }
    if(blen > alen)
        return -1;

    return 0;
}

QString formatText(QString s, int newLinew)
{
    switch (newLinew) {
    case 1:
        s.insert(0, '\n');
        return s.leftJustified(41, '-');
        break;
    case 2:
        s = s.leftJustified(40, '-');
        return s.append('\n');
        break;
    default:
        return s.leftJustified(40, '-');
        break;
    }
}

QString getStr(QVector<QString *> *list, bool nl)
{
    QString s = "";
    for (int i = 0; i < list->count(); ++i) {
        if(nl) {
            s += list->at(i);
            s += '\n';
        } else
            s += list->at(i);
    }
    return s;
}

void writeToFile(QString sPath, QString sFilename, QString sEnding, QString s, bool time, QString sTemp)
{
    QString sFile;
    if(time) {
        QDateTime date = QDateTime::currentDateTime();
        sFile = sPath + sFilename + "_" + date.toString("yyyyMMdd_HHmmss") + sTemp + sEnding;
    } else
        sFile = sPath + sFilename + "_" + sTemp + sEnding;

    QFile file(sFile);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "ERROR: open file!";
        return;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << s;
}

QString convertToCsv(QList<QStringList> &list)
{
    QString s;
    for (int i = 0; i < list.at(0).count(); ++i) {      // Anzahl der Zeilen
        for (int j = 0; j < list.count(); ++j) {        // Anzahl der Spalten
            s += list.at(j).at(i);
            s += ";";
        }
        s += '\n';
    }
    return s;
}

QString calculateAndConvertToCsv(QList<QStringList> &list, QStringList &elements)
{
    if(list.count() < 1) return "";
    if(list.at(0).count() < 1) return "";
    QString s;
    double spalten = list.count();
    double zeilen = list.at(0).count();

    // Tabelle -----------------------------------------------------------------
    for (int i = 0; i < list.at(0).count(); ++i) {      // Anzahl der Zeilen
        for (int j = 0; j < list.count(); ++j) {        // Anzahl der Spalten
            s += list.at(j).at(i);
            s += ";";
        }
        s += '\n';
    }

    // Mittelwert --------------------------------------------------------------
    for (int i = 0; i < spalten; ++i) {                 // Anzahl der Spalten
        double mittelwert = 0;
        for (int j = 0; j < zeilen; ++j) {              // Anzahl der Zeilen
            mittelwert += list.at(i).at(j).toDouble();
        }
        mittelwert /= zeilen;
        s += QString::number(mittelwert);
        s += ";";
    }
    s += "Mittelwert/Erwartungswert;";
    s += '\n';

    // Varianz -----------------------------------------------------------------
    for (int i = 0; i < spalten; ++i) {                 // Anzahl der Spalten
        // Mittelwert ----------------------------------
        double mittelwert = 0;
        for (int j = 0; j < zeilen; ++j) {              // Anzahl der Zeilen
            mittelwert += list.at(i).at(j).toDouble();
        }
        mittelwert /= zeilen;
        // Varianz -------------------------------------
        double varianz = 0;
        for (int j = 0; j < zeilen; ++j)                // Anzahl der Zeilen
            varianz += pow((list.at(i).at(j).toDouble() - mittelwert), 2.0);
        varianz /= zeilen;

        s += QString::number(varianz);
        s += ";";
    }
    s += "Varianz;";
    s += '\n';

    // Standardabweichung ------------------------------------------------------
    for (int i = 0; i < spalten; ++i) {                 // Anzahl der Spalten
        // Mittelwert ----------------------------------
        double mittelwert = 0;
        for (int j = 0; j < zeilen; ++j) {              // Anzahl der Zeilen
            mittelwert += list.at(i).at(j).toDouble();
        }
        mittelwert /= zeilen;
        // Varianz -------------------------------------
        double varianz = 0;
        for (int j = 0; j < zeilen; ++j)                // Anzahl der Zeilen
            varianz += pow((list.at(i).at(j).toDouble() - mittelwert), 2.0);
        varianz /= zeilen;
        // Standartabweichung --------------------------
        double standartabweichung = 0;
        standartabweichung = sqrt(varianz);

        s += QString::number(standartabweichung);
        s += ";";
    }
    s += "Standartabweichung;";
    s += '\n';

    // Anzahl der Elemente -----------------------------------------------------
    for (int i = 0; i < spalten; ++i) {                 // Anzahl der Spalten
        s += elements.at(i) + ";";
    }
    s += "Elemente;";
    return s.replace('.', ',');
}
