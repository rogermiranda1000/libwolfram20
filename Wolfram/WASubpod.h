/*
 *      WASubpod.h
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *
 */

#ifndef WASUBPOD_H
#define WASUBPOD_H

#include <string>

#include <rapidxml/rapidxml_utils.hpp>

#include "WAImage.h"

using std::string;
using namespace rapidxml;

class WASubpod
{
public:
    WASubpod();
    virtual ~WASubpod();

    string  getTitle();         // Return attr 'title' of subpods
    string  getPlainText();     // Return included plaintext of subpods

    WAImage* getImage();

    bool    Parse(xml_node<>* subpod);

private:
    // Attributes of 'subpod'
    char*   title;
    char*   plain;

    // Included img block
    WAImage* img;
};

#endif // WASUBPOD_H
