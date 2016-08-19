#ifndef SUCCESSRESULT_H
#define SUCCESSRESULT_H

#include "result.h"

template<class T> class SuccessResult : public Result<T>
{
public:
    SuccessResult(T data) {
        this->setSuccess(true);
        this->setData(data);
    }
};

#endif // SUCCESSRESULT_H
