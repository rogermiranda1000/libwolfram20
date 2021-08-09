/*********************************************************************
 *		@file WAPod.cpp
 *      Wolfram API element
 *
 *      @author 	Nikolenko Konstantin <knikolenko@yandex.ru>
 *		@author 	Roger Miranda <contacto@rogermiranda1000.com>
 *		@date		2011-2021
 ********************************************************************/

#include "WAPod.h"

/**
 * Default constructor.
 * It sets the error object, just in case
 */
WAPod::WAPod() {
	this->_error = new WAError(0, "Uninitialized WAPod object");
}

/**
 * It generates the object with the \p pod
 *
 * @param[in]	pod			XML Node of pod
 */
WAPod::WAPod(rapidxml::xml_node<>* pod) {
	this->parse(pod);
}

/**
 * Copy constructor
 *
 * @param[in]	old			Object to copy
 */
WAPod::WAPod(const WAPod &old) {
	if (old._error != nullptr) this->_error = new WAError(*old._error);
	this->_title = old._title;
	this->_scanner = old._scanner;
	this->_id = old._id;
	this->_position = old._position;
	this->SubPods = old.SubPods;
	this->States = old.States;
}

/**
 * Returns a 'title' attribute of Pod
 *
 * @return  title
 */
std::string WAPod::getTitle() {
    return this->_title;
}

/**
 * Returns a 'scanner' attribute of Pod
 *
 * @return  scanner
 */
std::string WAPod::getScanner() {
    return this->_scanner;
}

/**
 * Returns a 'position' attribute of Pod
 *
 * @return  position
 */
int WAPod::getPosition() {
    return this->_position;
}

/**
 * Returns a 'id' attribute of Pod
 *
 * @return  ID
 */
std::string WAPod::getID() {
    return this->_id;
}

/**
 * Returns all the getted subpods
 *
 * @return  Subpods
 */
std::vector<WASubpod> WAPod::getSubpods() {
    return SubPods;
}

/**
 * Returns all the getted states
 *
 * @return  States
 */
std::vector<WAPodState> WAPod::getStates() {
    return this->States;
}

/**
 * It checks if the results contains valid data.
 * @retval		true	The result is an error
 * @retval		false	All OK
 */
bool WAPod::isError() {
	return (this->_error != nullptr);
}

/**
 * It provides information about what happened
 * @return		Information about the error
 * @retval		nullptr		Error not returned by the API
 */
WAError *WAPod::getError() {
	return this->_error;
}

/**
 * Parsing a input 'pod' xml node
 *
 * @pre	You must call this function only once (called my the constructor)
 * @param[in]	pod			XML Node of pod
 */
void WAPod::parse(rapidxml::xml_node<>* pod) {
    if (std::string(pod->first_attribute("error")->value()) == "true") {
		this->_error = new WAError(pod->first_node("error"));
		return;
	}
	
    // Read arguments Pods node
    this->_title = std::string( pod->first_attribute("title")->value() );
    this->_id = std::string( pod->first_attribute("id")->value() );
    this->_scanner = std::string( pod->first_attribute("scanner")->value() );
    this->_position = atoi(pod->first_attribute("title")->value());
	
	// Reading a Subpods node
	xml_node<>* nodeSubpod = pod->first_node("subpod");
	for(unsigned int i = 0; i < atoi(pod->first_attribute("numsubpods")->value()); i++) {
		this->SubPods.push_back(WASubpod(nodeSubpod));
		nodeSubpod = nodeSubpod->next_sibling("subpod");
	}

    // Reading a States node
    xml_node<>* nodeStates = pod->first_node("states");
    if (nodeStates != nullptr) {
		unsigned int len = atoi(nodeStates->first_attribute("count")->value());
		nodeStates = nodeStates->first_node("state");
		for(unsigned int i = 0; i < len; i++) {
			this->States.push_back(WAPodState(nodeStates));
			nodeStates = nodeStates->next_sibling("state");
		}
    }
}
