/*
 *      WASubpod.cpp
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *		Copyright 2021 Roger Miranda <contacto@rogermiranda1000.com>
 *
 */

#include "WASubpod.h"

WASubpod::WASubpod(const WASubpod &old) {
	this->_title = old._title;
	this->_plain = old._plain;
	this->_img = new WAImage(*old._img);
}

WASubpod::WASubpod(xml_node<>* subpod) {
	this->parse(subpod);
}

WASubpod::~WASubpod() {
    delete this->_img;
}

/**
 * Returns a 'title' attribute of subpod
 *
 * @return Title
 */
std::string WASubpod::getTitle() {
    return this->_title;
}

/**
 * Returns a plain-text data, included on subpod
 *
 * @return Plain-text
 */
std::string WASubpod::getPlainText() {
    return this->_plain;
}

WAImage* WASubpod::getImage() {
    return this->_img;
}

bool WASubpod::hasImage() {
    return (this->_img != nullptr);
}

/**
 * Parsing a input 'subpod' xml node
 *
 * @param   subpod XML Node of subpod
 */
void WASubpod::parse(xml_node<>* subpod) {
    // Get 'title' attribute
    this->_title = std::string( subpod->first_attribute("title")->value() );

    // Get included plaintext
    xml_node<>* plainNode = subpod->first_node("plaintext");
    this->_plain = std::string( plainNode->value() );

    // Reading 'img' block
    xml_node<>* imgNode = subpod->first_node("img");
    if (imgNode != nullptr) this->_img = new WAImage(imgNode);
}
