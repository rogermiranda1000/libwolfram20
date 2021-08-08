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

using namespace rapidxml;

class WAImage
{
public:
    WAImage(const WAImage &old);
    WAImage(xml_node<>* imgNode);

    std::string getSrc();
    std::string getAlt();
    std::string getTitle();
    size_t getWidth();
    size_t getHeight();

private:
    // Attributes of 'image' node
    std::string _src;
    std::string _alt;
    std::string _title;
    size_t _width;
    size_t _height;

    void parse(xml_node<>* imgNode);
};

#endif // WAIMAGE_H
