#ifndef GRPException_H
#define GRPException_H

#include <exception>
#include <string>

//!The base exception class
/*!A base exception class for which all other GRPImage/Frame and
 *Colorpalettes are based on
 * \pre NA
 * \post NA
 * \note */

class GRPException : public virtual std::exception
{
    
public:
    
    //!Set the human readable message
    /*!Set a string with a message for the user/developer
     *  to see.
     * \pre NA
     * \post Sets message to string
     * \note NA*/
    void SetErrorMessage(const std::string &errorMessage);
    
    ~GRPException() throw() {}
    virtual std::string GetErrorMessage();
protected:
        //Stored message for error throw
       std::string humanReadableError;
private:
    
};
#endif