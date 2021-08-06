/*
 *      WASubpod.cpp
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *		Copyright 2021 Roger Miranda <contacto@rogermiranda1000.com>
 *
 */

#include "WASubpod.h"

WASubpod::WASubpod() {
    this->img = nullptr;
}

WASubpod::WASubpod(xml_node<>* subpod) {
    this->img = nullptr;
	this->Parse(subpod);
}

WASubpod::~WASubpod() {
    delete this->img;
}

/**
 * Returns a 'title' attribute of subpod
 *
 * @return Title
 */
string
WASubpod::getTitle()
{
    return string(title);
}

/**
 * Returns a plain-text data, included on subpod
 *
 * @return Plain-text
 */
string
WASubpod::getPlainText()
{
    return string(plain);
}

WAImage* WASubpod::getImage() {
    return this->img;
}

bool WASubpod::hasImage() {
    return this->img != nullptr;
}

/**
 * Parsing a input 'subpod' xml node
 *
 * @param   subpod XML Node of subpod
 */
void WASubpod::Parse(xml_node<>* subpod) {
    xml_node<>* plainNode;
    xml_node<>* imgNode;

    // Get 'title' attribute
    title = subpod->first_attribute("title")->value();

    // Get included plaintext
    plainNode = subpod->first_node("plaintext");
    plain     = plainNode->value();

    // Reading 'img' block
    imgNode = subpod->first_node("img");
    if (imgNode != NULL)
    {
		delete this->img; // if someone call Parse() 2 times
        this->img = new WAImage(imgNode);
    }
}
