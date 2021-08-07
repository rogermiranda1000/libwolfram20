/*********************************************************************
 *		@file WAPod.h
 *      Wolfram API content
 *
 *      @author 	Nikolenko Konstantin <knikolenko@yandex.ru>
 *		@author 	Roger Miranda <contacto@rogermiranda1000.com>
 *		@date		2011-2021
 ********************************************************************/

#ifndef WAPOD_H
#define WAPOD_H

#include <string>
#include <vector>

#include <rapidxml/rapidxml_utils.hpp>

#include "WASubpod.h"
#include "WAPodState.h"

/**
 * Wolfram API content
 */
class WAPod {
public:
    WAPod() = default;
    ~WAPod();

    char *getTitle();

    std::string getScanner();
    int getPosition();
    std::string getID();

    std::vector<WASubpod*> getSubpods();
    std::vector<WAPodState*> getStates();

    bool Parse(rapidxml::xml_node<>* pod);

private:
    // Attributes of 'pod' node
    char* title;
    char* scanner;
    char* id;
    int position;

    std::vector<WASubpod*> SubPods;
    std::vector<WAPodState*> States;
};

#endif // WAPOD_H
