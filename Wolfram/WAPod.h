/*
 *      WAPod.h
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *
 */

#ifndef WAPOD_H
#define WAPOD_H

#include <string>
#include <vector>

#include <rapidxml/rapidxml_utils.hpp>

#include "WASubpod.h"
#include "WAPodState.h"

using std::string;
using namespace rapidxml;

class WAPod
{
public:
    WAPod() = default;

    char	*getTitle();

    string  getScanner();
    int     getPosition();
    string  getID();

    std::vector<WASubpod> getSubpods();
    std::vector<WAPodState> getStates();

    bool    Parse(xml_node<>* pod);

private:
    // Attributes of 'pod' node
    char*   title;
    char*   scanner;
    char*   id;
    int     position;

    std::vector<WASubpod> SubPods;
    std::vector<WAPodState> States;

};

#endif // WAPOD_H
