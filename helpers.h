#ifndef HELPERS_H
#define HELPERS_H

#include <QDebug>
#include <QString>
#include <QVector>
#include <QFile>
#include <QDate>
#include <QTextStream>

#include <math.h>

int compare(const QChar *a, int alen, const QChar *b, int blen);

QString formatText(QString s, int newLinew = 0);

QString getStr(QVector<QString *> *list, bool nl = true);

void writeToFile(QString sPath, QString sFilename, QString sEnding, QString s, bool time = 0, QString sTemp = "");

QString convertToCsv(QList<QStringList> &list);
QString calculateAndConvertToCsv(QList<QStringList> &list, QStringList &elements);

#endif // HELPERS_H
