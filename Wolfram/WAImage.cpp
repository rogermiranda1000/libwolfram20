/*
 *      WAImage.cpp
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *		Copyright 2021 Roger Miranda <contacto@rogermiranda1000.com>
 *
 */

#include "WAImage.h"

WAImage::WAImage(const WAImage &old) {
	this->_src = old._src;
	this->_alt = old._alt;
	this->_title = old._title;
	this->_width = old._width;
	this->_height = old._height;
}

WAImage::WAImage(xml_node<>* imgNode) {
	this->parse(imgNode);
}

/**
 * Returning a 'src' attribute of image
 *
 * @return Address of image
 */
std::string WAImage::getSrc() {
    return this->_src;
}

/**
 * Returning a 'alt' attribute of image
 *
 * @return Alternate text of image
 */
std::string WAImage::getAlt() {
    return this->_alt;
}

/**
 * Returning a 'title' attribute of image
 *
 * @return Title of image
 */
std::string WAImage::getTitle() {
    return this->_title;
}

/**
 * Returning a 'width' attribute of image
 *
 * @return Width of image
 */
size_t WAImage::getWidth() {
    return this->_width;
}

/**
 * Returning a 'height' attribute of image
 *
 * @return Height of image
 */
size_t WAImage::getHeight() {
    return this->_height;
}

/**
 * Parsing a input 'img' xml node
 *
 * @pre		It must be called only one time
 * @param   imgNode XML Node of image
 */
void WAImage::parse(xml_node<>* imgNode) {
    // Get attributes
    this->_src = std::string( imgNode->first_attribute("src")->value() );
    this->_alt = std::string( imgNode->first_attribute("alt")->value() );
    this->_title = std::string( imgNode->first_attribute("title")->value() );
    this->_width = atoi(imgNode->first_attribute("width")->value());
    this->_height = atoi(imgNode->first_attribute("height")->value());
}
