/*
 *      WAPod.cpp
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *
 */

#include "WAPod.h"

WAPod::~WAPod()
{
    if (SubPods != NULL)
    {
        for (size_t i = 0; i < countSubPods; i++)
            SubPods[i].~WASubpod();
    }
    if (States != NULL)
    {
        for (size_t i = 0; i < countStates; i++)
            States[i].~WAPodState();
    }
}

/**
 * Returns a 'title' attribute of Pod
 *
 * @return  title
 */
char *WAPod::getTitle()
{
    return title;
}

/**
 * Returns a 'scanner' attribute of Pod
 *
 * @return  scanner
 */
string
WAPod::getScanner()
{
    return string(scanner);
}

/**
 * Returns a 'position' attribute of Pod
 *
 * @return  position
 */
int
WAPod::getPosition()
{
    return position;
}

/**
 * Returns a 'id' attribute of Pod
 *
 * @return  ID
 */
string
WAPod::getID()
{
    return string(id);
}

/**
 * Returns a count of 'subpod' blocks
 *
 * @return  count
 */
size_t
WAPod::getCountSubpods()
{
    return countSubPods;
}

WASubpod*
WAPod::getSubpods()
{
    if (countSubPods == 0) return NULL;
    return SubPods;
}

/**
 * Returns a count of 'state' blocks
 *
 * @return count
 */
size_t
WAPod::getCountStates()
{
    return countStates;
}

WAPodState*
WAPod::getStates()
{
    if (countStates == 0) return NULL;
    return States;
}

/**
 * Parsing a input 'pod' xml node
 *
 * @param   pod XML Node of pod
 * @return  false, if error
 */
bool WAPod::Parse(xml_node<>* pod) {
    if (string(pod->first_attribute("error")->value()) == "true") return false;
	
    // Read arguments Pods node
    title   = pod->first_attribute("title")->value();
    id      = pod->first_attribute("id")->value();
    scanner = pod->first_attribute("scanner")->value();
    position = atoi(pod->first_attribute("title")->value());

    countSubPods = atoi(pod->first_attribute("numsubpods")->value());
    if (countSubPods > 0)
    {
        // Reading a Subpods node
        SubPods = new WASubpod[countSubPods];

        xml_node<>* nodeSubpod = pod->first_node("subpod");
        for(size_t i = 0; i < countSubPods; i++)
        {
            SubPods[i].Parse(nodeSubpod);
            nodeSubpod = nodeSubpod->next_sibling("subpod");
        }
    }

    // Reading a States node
    xml_node<>* nodeStates = pod->first_node("states");
    if (nodeStates != 0)
    {
        countStates = atoi(nodeStates->first_attribute("count")->value());

        if (countStates > 0)
        {
            States = new WAPodState[countStates];
            nodeStates = nodeStates->first_node("state");
            for(size_t i = 0; i < countStates; i++)
            {
                States[i].Parse(nodeStates);
                nodeStates = nodeStates->next_sibling("state");
            }
        }
    }
    else
    {
        // States not found
        countStates = 0;
    }
    return true;
}
