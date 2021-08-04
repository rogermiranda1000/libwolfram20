/*
 *      WAPodState.h
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
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
    WAPodState();
    virtual ~WAPodState();

    string  getName();      // Return 'name' attribute
    string  getInput();     // Return 'input' attribute

    bool    Parse(xml_node<>* states);
protected:
private:
    // Attributes of 'state'
    char*   name;
    char*   input;
};

#endif // WAPODSTATE_H
