/*********************************************************************
 *		@file WAPod.h
 *      Wolfram API element
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
 * Wolfram API element. It contains information about the given query.
 * More information [on Wolfram documentation](https://products.wolframalpha.com/api/documentation/#result-pod)
 */
class WAPod {
public:
    WAPod(rapidxml::xml_node<>* pod);
    ~WAPod();

    std::string getTitle();
    std::string getScanner();
    int getPosition();
    std::string getID();

    std::vector<WASubpod*> getSubpods();
    std::vector<WAPodState*> getStates();

private:
    std::string _title;					//!< The pod title, used to identify the pod and its contents
	bool error;							//!< true or false depending on whether a serious processing error occurred with this specific pod
    std::string _scanner;				//!< The name of the scanner that produced this pod. A general guide to the type of data it holds
    std::string _id;					//!< A unique identifier for a pod, used for selecting specific pods to include or exclude
    int position;						//!< A number indicating the intended position of the pod in a visual display

    std::vector<WASubpod*> SubPods;		//!< All the valid Pods returned by the query
    std::vector<WAPodState*> States;	//!< All the valid States returned by the query
	// TODO if error there will be an error subelement

    void parse(rapidxml::xml_node<>* pod);
};

#endif // WAPOD_H
