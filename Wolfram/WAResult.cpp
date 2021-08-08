#include "WAResult.h"

/**
 * It extracts the data from \b query and save it into the object's arguments
 */
WAResult::WAResult(rapidxml::xml_node<>* query) {
	this->parse(query);
}

/**
 * Destructor; it frees the Pods
 */
WAResult::~WAResult() {
	for (auto it : this->_pods) delete it;
}

void WAResult::parse(rapidxml::xml_node<>* query) {
	if (std::string(query->first_attribute("success")->value()) == "false") {
		this->_error = true;
		return;
	}
	
    if (std::string(query->first_attribute("error")->value()) == "true") {
		// TODO get error
		this->_error = true;
		return;
	}
	
	this->_version = std::string( query->first_attribute("version")->value() );
	this->_dataTypes = std::string( query->first_attribute("datatypes")->value() );
	this->_timings = (Timings){ .parse = (float)atof(query->first_attribute("timing")->value()),
							.generate = (float)atof(query->first_attribute("parsetiming")->value()) };
	this->_timedout = WAResult::countTimedout(query->first_attribute("timedout")->value());
	if (this->_timedout > 0) this->_try_again = std::string( query->first_attribute("recalculate")->value() );

    rapidxml::xml_node<>* node = query->first_node("pod");
    for(size_t i = 0; i < atoi(query->first_attribute("numpods")->value()); i++) {
		this->_pods.push_back(new WAPod(node));
        node = node->next_sibling("pod");
    }
	
    return;
}

/**
 * It counts the pods that are timedout
 * @param[in]	timedout	Pod names separated by ',' that are timedout. Empty string (not null) if any.
 * @return					Number of timedout elements
 */
unsigned int WAResult::countTimedout(char *timedout) {
	if (*timedout = '\0') return 0;
	unsigned int counter = 1; // if there's zero comas (but it's not empty; as checked on the previous line) there's 1 element
	while (*timedout != '\0') {
		if (*timedout == ',') counter++;
		timedout++;
	}
	return counter;
}

bool WAResult::isError() {
	return this->_error;
}

unsigned int WAResult::getTimedout() {
	return this->_timedout;
}

/**
 * Returns the getted array of Pods of the previous query
 *
 * @pre Call \ref parse
 * @return Getted Pods
 */
std::vector<WAPod*> WAResult::getPods() {
    return this->_pods;
}

/**
 * Returns a Pod matching the \p title
 *
 * @param[in]	title	Title to search on the getted Pods
 * @return 				Pointer to the Pod with the specified title
 * @retval		nullptr	No Pod found
 */
WAPod *WAResult::getPod(const char *title) {
	vector<WAPod*>::iterator it;
	for (it = begin(this->_pods); it != end(this->_pods); it++) {
		if (strcmp((*it)->getTitle().c_str(), title) == 0) return *it; // same title
	}
    return nullptr;
}