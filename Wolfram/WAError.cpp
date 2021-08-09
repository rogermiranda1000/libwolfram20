/*********************************************************************
 *		@file WAError.cpp
 *      Wolfram API error element
 *
 *		@author 	Roger Miranda <contacto@rogermiranda1000.com>
 *		@date		2021
 ********************************************************************/

#include "WAError.h"

/**
 * C++ error
 *
 * @param[in]	code		Error code
 * @param[in]	msg			Error message
 */
WAError::WAError(int code, const char *msg) {
	this->_msg = std::string(msg);
	this->_code = code;
}

/**
 * It generates the object with the \b error
 *
 * @param[in]	error		XML Node of error
 */
WAError::WAError(rapidxml::xml_node<>* error) {
	this->parse(error);
}

/**
 * It returns information about the error
 *
 * @return	Error message
 */
std::string WAError::getErrorMessage() {
	return this->_msg;
}

/**
 * It returns the error code
 *
 * @return	Error code
 */
int WAError::getErrorCode() {
	return this->_code;
}

/**
 * Parsing the input \p error
 *
 * @pre	You must call this function only once (called my the constructor)
 * @param[in]	error		XML Node of error
 */
void WAError::parse(rapidxml::xml_node<>* error) {
    // Read the error node arguments
    this->_code = atoi( error->first_attribute("code")->value() );
    this->_msg = std::string( error->first_attribute("msg")->value() );
}
