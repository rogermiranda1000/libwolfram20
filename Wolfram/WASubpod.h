/*
 *      WASubpod.h
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *		Copyright 2021 Roger Miranda <contacto@rogermiranda1000.com>
 *
 */

#ifndef WASUBPOD_H
#define WASUBPOD_H

#include <string>

#include <rapidxml/rapidxml_utils.hpp>

#include "WAImage.h"

using namespace rapidxml;

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
