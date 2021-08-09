/*********************************************************************
 *		@file WAError.cpp
 *      Wolfram API error element
 *
 *		@author 	Roger Miranda <contacto@rogermiranda1000.com>
 *		@date		2021
 ********************************************************************/

#include "WAError.h"

/**
 * It generates the object with the \b error
 *
 * @param[in]	error		XML Node of error
 */
WAError::WAError(rapidxml::xml_node<>* error) {
	this->parse(error);
}

std::string WAError::getErrorMessage() {
	return this->_msg;
}

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