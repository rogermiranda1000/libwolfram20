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
 * Contains a particular pod state for a single pod or subpod.
 * More information [on Wolfram documentation](https://products.wolframalpha.com/api/documentation/#result-state)
 */
class WAPodState {
public:
    WAPodState(rapidxml::xml_node<>* states);

    std::string getName();
    std::string getInput();
	
private:
    // Attributes of 'state'
    std::string _name;			//!< Describes the pod state
    std::string _input;			//!< It can be used to modify subsequent queries

    void parse(rapidxml::xml_node<>* states);
};

#endif // WAPODSTATE_H
