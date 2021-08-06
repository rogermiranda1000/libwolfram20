/*
 *      WAPod.cpp
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *		Copyright 2021 Roger Miranda <contacto@rogermiranda1000.com>
 *
 */

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
char *WAPod::getTitle()
{
    return title;
}

/**
 * Returns a 'scanner' attribute of Pod
 *
 * @return  scanner
 */
string
WAPod::getScanner()
{
    return string(scanner);
}

/**
 * Returns a 'position' attribute of Pod
 *
 * @return  position
 */
int
WAPod::getPosition()
{
    return position;
}

/**
 * Returns a 'id' attribute of Pod
 *
 * @return  ID
 */
string
WAPod::getID()
{
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
 * @param   pod XML Node of pod
 * @return  false, if error
 */
bool WAPod::Parse(xml_node<>* pod) {
    if (string(pod->first_attribute("error")->value()) == "true") return false;
	
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
