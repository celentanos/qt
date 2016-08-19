#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QString>
#include <QDateTime>

class Log : public QObject
{
    Q_OBJECT
public:

    enum LOG {
        INFO,
        FAILURE,
        ERROR,
        FATAL
    };

    static Log *getInstance() {
        if (instance == 0)
            instance = new Log();
        return instance;
    }

    void log(LOG l, QString s);

private:
    Log();                  // verhindert, dass ein Objekt von außerhalb von 'Classe' erzeugt wird
    Log(const Log &);       // verhindert, dass eine weitere Instanz via Kopie-Konstruktor erstellt werden kann
    static Log *instance;

signals:
    void signalAddLog(QString s);
};

#endif // LOG_H
