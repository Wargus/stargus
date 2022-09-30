#include "GRPException.hpp"

void GRPException::SetErrorMessage(const std::string &errorMessage)
{
    humanReadableError = "GRPException: ";
    humanReadableError.append(errorMessage);
}

std::string GRPException::GetErrorMessage()
{
    return humanReadableError;
}