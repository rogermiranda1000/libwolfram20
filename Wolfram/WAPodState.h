/*
 *      WAPodState.h
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *		Copyright 2021 Roger Miranda <contacto@rogermiranda1000.com>
 *
 */

#ifndef WAPODSTATE_H
#define WAPODSTATE_H

#include <string>

#include <rapidxml/rapidxml_utils.hpp>

using std::string;
using namespace rapidxml;

class WAPodState
{
public:
    WAPodState() = default;
    WAPodState(xml_node<>* states);

    string  getName();      // Return 'name' attribute
    string  getInput();     // Return 'input' attribute

    void Parse(xml_node<>* states);
protected:
private:
    // Attributes of 'state'
    char*   name;
    char*   input;
};

#endif // WAPODSTATE_H
