/*
 *      WAPodState.cpp
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *		Copyright 2021 Roger Miranda <contacto@rogermiranda1000.com>
 *
 */

#include "WAPodState.h"

WAPodState::WAPodState(xml_node<>* states) {
    this->Parse(states);
}

/**
 * Returning a 'name' attribute of state
 *
 * @return Name of image
 */
string
WAPodState::getName() {
    return string(name);
}

/**
 * Returning a 'input' attribute of state
 *
 * @return Input of image
 */
string
WAPodState::getInput() {
    return string(input);
}

/**
 * Parsing a input 'state' xml node
 *
 * @param   states XML Node of state
 */
void WAPodState::Parse(xml_node<>* states)
{
    // Reading attribute
    name    = states->first_attribute("name")->value();
    input   = states->first_attribute("input")->value();
}
