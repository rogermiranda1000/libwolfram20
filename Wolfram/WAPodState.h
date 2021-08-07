/*********************************************************************
 *		@file WAPodState.h
 *      Wolfram Pod States
 *
 *      @author 	Nikolenko Konstantin <knikolenko@yandex.ru>
 *		@author 	Roger Miranda <contacto@rogermiranda1000.com>
 *		@date		2011-2021
 ********************************************************************/

#ifndef WAPODSTATE_H
#define WAPODSTATE_H

#include <string>

#include <rapidxml/rapidxml_utils.hpp>

/**
 * Subelement of WAPod or WASubpod.
 * More information [on Wolfram documentation](https://products.wolframalpha.com/api/documentation/#result-states)
 */
class WAPodState {
public:
    WAPodState() = default;
    WAPodState(rapidxml::xml_node<>* states);

    std::string getName();      // Return 'name' attribute
    std::string getInput();     // Return 'input' attribute

    void Parse(rapidxml::xml_node<>* states);
	
private:
    // Attributes of 'state'
    char* name;
    char* input;
};

#endif // WAPODSTATE_H
