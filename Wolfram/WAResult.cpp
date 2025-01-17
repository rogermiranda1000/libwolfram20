/*********************************************************************
 *		@file WAResult.cpp
 *      Wolfram API result
 *
 *      @author 	Nikolenko Konstantin <knikolenko@yandex.ru>
 *		@author 	Roger Miranda <contacto@rogermiranda1000.com>
 *		@date		2011-2021
 ********************************************************************/

#include "WAResult.h"

/**
 * Copy constructor
 *
 * @param[in]	old			Object to copy
 */
WAResult::WAResult(const WAResult &old) {
	this->_is_error = old._is_error;
	this->_error = nullptr;
	if (old._error != nullptr) this->_error = new WAError(*old._error);
	this->_dataTypes = old._dataTypes;
	this->_version = old._version;
	this->_timings = old._timings;
	this->_timedout = old._timedout;
	this->_try_again = old._try_again;
	this->_pods = old._pods;
}

/**
 * It extracts the data from \b query and save it into the object's arguments
 *
 * @param[in]	query		XML Node of query
 */
WAResult::WAResult(rapidxml::xml_node<>* query) {
	this->parse(query);
}

/**
 * Destructor. It frees the error memory (if any).
 */
WAResult::~WAResult() {
	delete this->_error;
}

/**
 * Parsing the input \p query
 *
 * @pre 				It must be called only once
 * @param[in]   query	XML Node of query
 */
void WAResult::parse(rapidxml::xml_node<>* query) {
	this->_error = nullptr;
	
	if (strcmp(query->first_attribute("success")->value(), "false") == 0) {
		this->_is_error = true;
		return;
	}
	
    if (strcmp(query->first_attribute("error")->value(), "true") == 0) {
		this->_is_error = true;
		rapidxml::xml_node<>* error = query->first_node("error");
		if (error != nullptr) this->_error = new WAError(error);
		return;
	}
	
	this->_version = std::string( query->first_attribute("version")->value() );
	this->_dataTypes = std::string( query->first_attribute("datatypes")->value() );
	this->_timings = (Timings){ .parse = (float)atof(query->first_attribute("timing")->value()),
							.generate = (float)atof(query->first_attribute("parsetiming")->value()) };
	this->_timedout = WAResult::splitTimedout(query->first_attribute("timedout")->value());
	if (this->getTimedoutNumber() > 0) this->_try_again = std::string( query->first_attribute("recalculate")->value() );

    rapidxml::xml_node<>* node = query->first_node("pod");
    for(size_t i = 0; i < atoi(query->first_attribute("numpods")->value()); i++) {
		this->_pods.push_back(WAPod(node));
        node = node->next_sibling("pod");
    }
	
    return;
}

/**
 * It stores the pods that are timedout into a vector.
 * Posted on https://stackoverflow.com/a/52690600/9178470
 * @author					eXpl0it3R
 * @param[in]	s			Pod names separated by ',' that are timedout. Empty string (not null) if any.
 * @return					Timedout pods vector
 */
std::vector<std::string> WAResult::splitTimedout(const std::string& s) {
	std::vector<std::string> splits;
	std::string split;
	std::istringstream ss(s);
	while (std::getline(ss, split, ',')) splits.push_back(split);
	return splits;
}

/**
 * It checks if the results contains valid data.
 * In some cases, you can call @ref getError to get more information
 * @retval		true	The result is an error
 * @retval		false	All OK
 */
bool WAResult::isError() {
	return this->_is_error;
}

/**
 * It provides information about what happened
 * @warning		Even if @ref isError returns true you souldn't expect the return to be a valid pointer (not nullptr)
 * @return		Information about the error
 * @retval		nullptr		Error not returned by the API
 */
WAError *WAResult::getError() {
	return this->_error;
}

/**
 * It returns the number of elements that were timedout
 * @return		Timedout elements
 */
unsigned int WAResult::getTimedoutNumber() {
	return this->_timedout.size();
}

/**
 * It returns the elements that were timedout
 * @return		Timedout elements
 */
std::vector<std::string> WAResult::getTimedout() {
	return this->_timedout;
}

/**
 * Returns the getted array of Pods of the previous query
 *
 * @pre 	Call @ref parse
 * @return 	Getted Pods
 */
std::vector<WAPod> WAResult::getPods() {
    return this->_pods;
}

/**
 * Returns a Pod matching the \p title
 *
 * @warning				If \p _pods contains pods with the same title it will return the first one
 * @param[in]	title	Title to search on the getted Pods
 * @param[out]	pod		Pod with the specified title
 * @retval		TRUE	Pod found
 * @retval		FALSE	Pod not found
 */
bool WAResult::getPod(const char *title, WAPod *pod) {
	std::vector<WAPod>::iterator it;
	for (it = begin(this->_pods); it != end(this->_pods); it++) {
		std::string cur_title = it->getTitle();
		if (strcmp(cur_title.c_str(), title) == 0) {
			// same title
			*pod = *it;
			return true;
		}
	}
	
    return false;
}