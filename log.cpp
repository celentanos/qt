#include "log.h"

Log *Log::instance = 0;

Log::Log()
{

}

void Log::log(LOG l, QString s)
{
    emit signalAddLog(QDateTime::currentDateTime().toString("yyyy:MM:dd-HH:mm:ss") + ": " + s);
    (void)l;
}
