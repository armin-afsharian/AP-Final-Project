#ifndef ERORR_H
#define ERORR_H

#include <iostream>

class Exception
{
    public:
        virtual void what() = 0;
};

class NotFound : public Exception
{
    public:
        virtual void what();
};

class BadRequest : public Exception
{
    public:
        virtual void what();
};

class PermissionDenied : public Exception
{
    public:
        virtual void what();
};

#endif