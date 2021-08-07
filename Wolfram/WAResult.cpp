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
    if (std::string(query->first_attribute("error")->value()) == "true") {
		this->_error = true;
		return;
	}

    rapidxml::xml_node<>* node = query->first_node("pod");
    for(size_t i = 0; i < atoi(query->first_attribute("numpods")->value()); i++) {
		this->_pods.push_back(new WAPod(node));
        node = node->next_sibling("pod");
    }
	
    return;
}

bool WAResult::isError() {
	return this->_error;
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
		if (strcmp((*it)->getTitle(), title) == 0) return *it; // same title
	}
    return nullptr;
}