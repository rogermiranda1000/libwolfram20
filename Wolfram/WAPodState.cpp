/*********************************************************************
 *		@file WAPodState.cpp
 *      Wolfram Pod States
 *
 *      @author 	Nikolenko Konstantin <knikolenko@yandex.ru>
 *		@author 	Roger Miranda <contacto@rogermiranda1000.com>
 *		@date		2011-2021
 ********************************************************************/

#include "WAPodState.h"

WAPodState::WAPodState(rapidxml::xml_node<>* states) {
    this->Parse(states);
}

/**
 * Returning a 'name' attribute of state
 *
 * @return Name of image
 */
std::string WAPodState::getName() {
    return std::string(name);
}

/**
 * Returning a 'input' attribute of state
 *
 * @return Input of image
 */
std::string WAPodState::getInput() {
    return std::string(input);
}

/**
 * Parsing a input 'state' xml node
 *
 * @param[in]	states	XML Node of state
 */
void WAPodState::Parse(rapidxml::xml_node<>* states) {
    // Reading attribute
    name = states->first_attribute("name")->value();
    input = states->first_attribute("input")->value();
}
