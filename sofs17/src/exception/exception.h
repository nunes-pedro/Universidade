/**
 * \file exception.h
 * \brief the sofs17 exception support
 * \author Artur Pereira - 2016-2017
 */
#ifndef __SOFS17_EXCEPTION__
#define __SOFS17_EXCEPTION__

#include <exception>
#include <string>
#include <sstream>

#include <string.h>

/**
 * \brief sofs17 exception data type
 */
struct SOException:public std::exception
{
    int en;             ///< (system) error number
    const char *msg;    ///< name of function that has thrown the exception
    /**
     * \brief the constructor
     * \param _en (system) error number 
     * \param _msg name of function throwing the exception
     */
    SOException(int _en, const char *_msg):en(_en), msg(_msg)
    {
    }

    /**
     * \brief default exception message
     * \return pointer to exception message
     */
    const char *what() const throw()
    {
        std::ostringstream ss;
        ss << "\e[01;31m" << std::
            string(msg) << ": error " << en << " (" << strerror(en) << ")\e[0m";
        return ss.str().c_str();
    }
};

#endif                          /* __SOFS17_EXCEPTION__ */
