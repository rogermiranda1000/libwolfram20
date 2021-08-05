/*
 *      WAImage.cpp
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *		Copyright 2021 Roger Miranda <contacto@rogermiranda1000.com>
 *
 */

#include "WAImage.h"

WAImage::WAImage() {
	this->src = nullptr;
	this->alt = nullptr;
	this->title = nullptr;
}

/**
 * Returning a 'src' attribute of image
 *
 * @return Address of image
 */
string WAImage::getSrc() {
	if (this->src == nullptr) return string("");
    return string(this->src);
}

/**
 * Returning a 'alt' attribute of image
 *
 * @return Alternate text of image
 */
string WAImage::getAlt() {
	if (this->alt == nullptr) return string("");
    return string(this->alt);
}

/**
 * Returning a 'title' attribute of image
 *
 * @return Title of image
 */
string WAImage::getTitle() {
	if (this->title == nullptr) return string("");
    return string(this->title);
}

/**
 * Returning a 'width' attribute of image
 *
 * @return Width of image
 */
size_t WAImage::getWidth() {
    return this->width;
}

/**
 * Returning a 'height' attribute of image
 *
 * @return Height of image
 */
size_t WAImage::getHeight() {
    return this->height;
}

/**
 * Parsing a input 'img' xml node
 *
 * @param   imgNode XML Node of image
 */
void WAImage::Parse(xml_node<>* imgNode) {
    // Get attributes
	xml_attribute<>* tmp = imgNode->first_attribute("src");
    if (tmp != nullptr) this->src = tmp->value();
	tmp = imgNode->first_attribute("alt");
    if (tmp != nullptr) this->alt = tmp->value();
	tmp = imgNode->first_attribute("title");
    if (tmp != nullptr) this->title = tmp->value();
	tmp = imgNode->first_attribute("width");
    if (tmp != nullptr) this->width = atoi(tmp->value());
	tmp = imgNode->first_attribute("height");
    if (tmp != nullptr) this->height = atoi(tmp->value());
}
