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
    this->parse(states);
}

/**
 * Returning the name of the state
 *
 * @return Name of image
 */
std::string WAPodState::getName() {
    return this->_name;
}

/**
 * Returning a 'input' attribute of state
 *
 * @return Input of image
 */
std::string WAPodState::getInput() {
    return this->_input;
}

/**
 * Parsing a input 'state' xml node
 *
 * @param[in]	states	XML Node of state
 */
void WAPodState::parse(rapidxml::xml_node<>* states) {
    // Reading attribute
    this->_name = std::string( states->first_attribute("name")->value() );
    this->_input = std::string( states->first_attribute("input")->value() );
}
