/*********************************************************************
 *		@file WASubpod.h
 *      Wolfram API subpod
 *
 *      @author 	Nikolenko Konstantin <knikolenko@yandex.ru>
 *		@author 	Roger Miranda <contacto@rogermiranda1000.com>
 *		@date		2011-2021
 ********************************************************************/

#ifndef WASUBPOD_H
#define WASUBPOD_H

#include <string>

#include <rapidxml/rapidxml_utils.hpp>

#include "WAImage.h"

using namespace rapidxml;

/**
 * Wolfram API element. It contains information about the pod.
 * More information [on Wolfram documentation](https://products.wolframalpha.com/api/documentation/#result-subpod).
 */
class WASubpod
{
public:
    WASubpod(const WASubpod &old);
	WASubpod(xml_node<>* subpod);
    ~WASubpod();

    std::string  getTitle();
    std::string  getPlainText();

    WAImage *getImage();
	bool 	hasImage();

private:
    std::string _title;			//!< TODO
    std::string _plain;			//!< TODO
    WAImage* _img;				//!< Included img block

    void parse(xml_node<>* subpod);
};

#endif // WASUBPOD_H
