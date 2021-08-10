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
 * More information [on Wolfram documentation](https://products.wolframalpha.com/api/documentation/#result-error).
 */
class WAError {
public:
	/**
	 * Copy constructor
	 * @param[in]	old		Object to copy
	 */
	WAError(const WAError &old) = default;
	WAError(int code, const char *msg);
    WAError(rapidxml::xml_node<>* error);

    std::string getErrorMessage();
    int getErrorCode();

private:
	/**
	 * The error code
	 * HTTP Status 501: This status is returned if a given input value cannot be interpreted by this API.
	 * HTTP Status 400: This status indicates that the API did not find an input parameter while parsing.
	 * Invalid appid (Error 1): This error is returned when a request contains an invalid option for the appid parameter.
	 * Appid missing (Error 2): This error is returned when a request does not contain any option for the appid parameter.
	 */
    int _code;
    std::string _msg;						//!< A short message describing the error

    void parse(rapidxml::xml_node<>* error);
};

#endif // WAERROR_H
