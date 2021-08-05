#ifndef WAIMAGE_H
#define WAIMAGE_H

#include <cstring>

/*
 *      WAImage.h
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *		Copyright 2021 Roger Miranda <contacto@rogermiranda1000.com>
 *
 */

#include <rapidxml/rapidxml_utils.hpp>

using std::string;
using namespace rapidxml;

class WAImage
{
public:
    WAImage();

    string  getSrc();
    string  getAlt();
    string  getTitle();
    size_t  getWidth();
    size_t  getHeight();

    void    Parse(xml_node<>* imgNode);

private:
    // Attributes of 'image' node
    char*   src;
    char*   alt;
    char*   title;
    size_t  width;
    size_t  height;
};

#endif // WAIMAGE_H
