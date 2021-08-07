/*********************************************************************
 *		@file WAPod.cpp
 *      Wolfram API content
 *
 *      @author 	Nikolenko Konstantin <knikolenko@yandex.ru>
 *		@author 	Roger Miranda <contacto@rogermiranda1000.com>
 *		@date		2011-2021
 ********************************************************************/

#include "WAPod.h"

WAPod::~WAPod() {
	for (auto it : this->SubPods) delete it;
	for (auto it : this->States) delete it;
}

/**
 * Returns a 'title' attribute of Pod
 *
 * @return  title
 */
char *WAPod::getTitle() {
    return title;
}

/**
 * Returns a 'scanner' attribute of Pod
 *
 * @return  scanner
 */
std::string WAPod::getScanner() {
    return std::string(scanner);
}

/**
 * Returns a 'position' attribute of Pod
 *
 * @return  position
 */
int WAPod::getPosition() {
    return position;
}

/**
 * Returns a 'id' attribute of Pod
 *
 * @return  ID
 */
std::string WAPod::getID() {
    return string(id);
}

std::vector<WASubpod*> WAPod::getSubpods() {
    return SubPods;
}

std::vector<WAPodState*> WAPod::getStates() {
    return this->States;
}

/**
 * Parsing a input 'pod' xml node
 *
 * @param[in]	pod			XML Node of pod
 * @retval		TRUE		All OK
 * @retval		FALSE		Parse failed
 */
bool WAPod::Parse(rapidxml::xml_node<>* pod) {
    if (std::string(pod->first_attribute("error")->value()) == "true") return false;
	
    // Read arguments Pods node
    title   = pod->first_attribute("title")->value();
    id      = pod->first_attribute("id")->value();
    scanner = pod->first_attribute("scanner")->value();
    position = atoi(pod->first_attribute("title")->value());
	
	// Reading a Subpods node
	this->SubPods.clear();
	xml_node<>* nodeSubpod = pod->first_node("subpod");
	for(size_t i = 0; i < atoi(pod->first_attribute("numsubpods")->value()); i++) {
		this->SubPods.push_back(new WASubpod(nodeSubpod));
		nodeSubpod = nodeSubpod->next_sibling("subpod");
	}

    // Reading a States node
	this->States.clear();
    xml_node<>* nodeStates = pod->first_node("states");
    if (nodeStates != nullptr) {
		size_t len = atoi(nodeStates->first_attribute("count")->value());
		nodeStates = nodeStates->first_node("state");
		for(size_t i = 0; i < len; i++) {
			this->States.push_back(new WAPodState(nodeStates));
			nodeStates = nodeStates->next_sibling("state");
		}
    }
	
    return true;
}
