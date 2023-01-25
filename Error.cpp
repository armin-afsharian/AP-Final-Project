#include "Error.h"

void NotFound::what()
{
    std::cerr << "Not Found\n";
}

void BadRequest::what()
{
    std::cerr << "Bad Request\n";
}

void PermissionDenied::what()
{
    std::cerr << "Permission Denied\n";
}