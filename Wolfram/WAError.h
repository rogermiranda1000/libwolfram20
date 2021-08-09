/*********************************************************************
 *		@file WAError.h
 *      Wolfram API error element
 *
 *		@author 	Roger Miranda <contacto@rogermiranda1000.com>
 *		@date		2021
 ********************************************************************/

#ifndef WAERROR_H
#define WAERROR_H

#include <string>

#include <rapidxml/rapidxml_utils.hpp>

/**
 * Wolfram API error element. It contains information about the thrown error.
 * More information [on Wolfram documentation](https://products.wolframalpha.com/api/documentation/#result-error)
 */
class WAError {
public:
    WAError(rapidxml::xml_node<>* error);

    std::string getErrorMessage();
    int getErrorCode();

private:
    int _code;								//!< The error code
    std::string _msg;						//!< A short message describing the error

    void parse(rapidxml::xml_node<>* error);
};

#endif // WAERROR_H
