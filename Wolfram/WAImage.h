#ifndef WAIMAGE_H
#define WAIMAGE_H

#include <cstring>

/*
 *      WAImage.h
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *
 */

#include <rapidxml/rapidxml_utils.hpp>

using std::string;
using namespace rapidxml;

class WAImage
{
public:
    WAImage();
    virtual ~WAImage();

    string  getSrc();
    string  getAlt();
    string  getTitle();
    size_t  getWidth();
    size_t  getHeight();

    bool    Parse(xml_node<>* imgNode);

private:
    // Attributes of 'image' node
    char*   src;
    char*   alt;
    char*   title;
    size_t  width;
    size_t  height;
};

#endif // WAIMAGE_H
