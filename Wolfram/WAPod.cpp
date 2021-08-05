/*
 *      WAPod.cpp
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *		Copyright 2021 Roger Miranda <contacto@rogermiranda1000.com>
 *
 */

#include "WAPod.h"

WAPod::WAPod() {
	this->img = nullptr;
}

WAPod::~WAPod() {
	if (this->img != nullptr) delete this->img;
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

WAImage* WAPod::getImage() {
    return img;
}

bool WAPod::hasImage() {
    return img != nullptr;
}

std::vector<WASubpod> WAPod::getSubpods() {
    return SubPods;
}

std::vector<WAPodState> WAPod::getStates() {
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

	xml_node<>* nodeMarkup = pod->first_node("markup")->first_node(); // CDATA is a separate element -> first_node()
    for (char *val = nodeMarkup->value(); *val != '\0'; val++) {
		if (*val == '\n' || *val == '\t') *val = ' ';
	}
    xml_document<> markup;
    markup.parse<0>(nodeMarkup->value());
	xml_node<>* imgNode = markup.first_node("img");
	if (imgNode != NULL) {
		if (this->img != nullptr) delete this->img;
		
		this->img = new WAImage();
		this->img->Parse(imgNode);
	}
	
	// Reading a Subpods node
	this->SubPods.clear();
	xml_node<>* nodeSubpod = pod->first_node("subpod");
	for(size_t i = 0; i < atoi(pod->first_attribute("numsubpods")->value()); i++) {
		WASubpod tmp;
		tmp.Parse(nodeSubpod);
		this->SubPods.push_back(tmp);
		nodeSubpod = nodeSubpod->next_sibling("subpod");
	}

    // Reading a States node
	this->States.clear();
    xml_node<>* nodeStates = pod->first_node("states");
    if (nodeStates != nullptr) {
		size_t len = atoi(nodeStates->first_attribute("count")->value());
		nodeStates = nodeStates->first_node("state");
		for(size_t i = 0; i < len; i++) {
			WAPodState tmp;
			tmp.Parse(nodeStates);
			this->States.push_back(tmp);
			nodeStates = nodeStates->next_sibling("state");
		}
    }
	
    return true;
}
