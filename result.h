#ifndef RESULT_H
#define RESULT_H

#include <QString>

template<class T>
class Result
{
public:
    Result() {
    }

    T getData() const {
        return data;
    }

    void setData(const T &value) {
        data = value;
    }

    bool getSuccess() const {
        return success;
    }

    void setSuccess(bool value) {
        success = value;
    }

    QString getErrMsg() const {
        return errMsg;
    }

    void setErrMsg(const QString &value) {
        errMsg = value;
    }

protected:
    T data;
    bool success;
    QString errMsg;
};

#endif // RESULT_H
