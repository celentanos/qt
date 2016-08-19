#ifndef ERRORRESULT_H
#define ERRORRESULT_H

#include "result.h"

template<class T> class ErrorResult : public Result<T>
{
public:
    ErrorResult(QString err) {
        this->setSuccess(false);
        this->setErrMsg(err);
    }
};

#endif // ERRORRESULT_H
