/*
 *      WAQuery.cpp
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *		Copyright 2021 Roger Miranda <contacto@rogermiranda1000.com>
 *
 */

#include "WAQuery.h"

WAQuery::~WAQuery()
{
    // Clear vectors
    this->formats.clear();
    this->PodTitle.clear();
    this->PodIndexes.clear();
    this->PodScanners.clear();
    this->IncludePodIDs.clear();
    this->ExcludePodIDs.clear();
}

/**
 * Returning a query param string
 *
 * @return Query
 */
string WAQuery::toString() {
    string q = string("&input=") + WAQuery::parseInput(this->input);

    // Adding a vectors data to string
    q += VectorToStr("&format=",       false, this->formats);
    q += VectorToStr("&includepodid=", true,  this->IncludePodIDs);
    q += VectorToStr("&excludepodid=", true,  this->ExcludePodIDs);
    q += VectorToStr("&podtitle=",     true,  this->PodTitle);
    q += VectorToStr("&scanner=",      true,  this->PodScanners);
    q += VectorToStr("&podindex=",     false, this->PodIndexes);

    return q;
}

/**
 *	Characters on https://es.wikipedia.org/wiki/C%C3%B3digo_porciento
 */
static std::set<char> special_char = {'!', '#', '$', '&', '\'', '(', ')', '*', '+', ',', '/', ':', ';', '=', '?', '@', '[', ']'};

/**
 *	Given an string it creates a copy but with % code
 */
string WAQuery::parseInput(string str) {
	std::stringstream result;
	
	string::iterator it;
	for (it = str.begin(); it < str.end(); it++) {
		if (special_char.find(*it) != special_char.end()) {
			result << '%';
			result << std::hex << (int)(*it);
		}
		else if (*it == ' ') result << '+'; // space is special; it should be '+'
		else result << (*it);
	}
	
	return result.str();
}

/**
 * Returning a search query text
 *
 * @return Search query string
 */
string
WAQuery::getInput()
{
    return this->input;
}

/**
 * Set text for search
 *
 * @param   input   Text for search
 */
void WAQuery::setInput(string input) {
    this->input = input;
}

/**
 * Adding a string format
 *
 * @param   format String of format
 */
void WAQuery::addFormat(string format) {
    this->formats.push_back(format);
}

/**
 * Adding a string format
 *
 * @param   format String of format
 */
void WAQuery::addFormat(const char *format) {
	this->addFormat(string(format));
}

/**
 * Clear format config
 */
void
WAQuery::clearFormats()
{
    this->formats.clear();
}

void
WAQuery::addPodTitle(string podtitle)
{
    this->PodTitle.push_back(podtitle);
}

void
WAQuery::clearPodTitles()
{
    this->PodTitle.clear();
}

void
WAQuery::addPodIndex(int podindex)
{
    this->PodIndexes.push_back(podindex);
}

void
WAQuery::clearPodIndexes()
{
    this->PodIndexes.clear();
}

void
WAQuery::addPodScanner(string podscanner)
{
    this->PodScanners.push_back(podscanner);
}

void
WAQuery::clearPodScanners()
{
    this->PodScanners.clear();
}

void
WAQuery::addIncludePodID(string podid)
{
    this->IncludePodIDs.push_back(podid);
}

void
WAQuery::clearIncludePodIDs()
{
    this->IncludePodIDs.clear();
}

void
WAQuery::addExcludePodID(string podid)
{
    this->ExcludePodIDs.push_back(podid);
}

void
WAQuery::clearExcludePodIDs()
{
    this->ExcludePodIDs.clear();
}
/**
 * Concatenating a vector data to string
 *
 * @param   prefix      String prefix for data; example '&name='
 * @param   individual  Type of concatenating string
 * @param   t           Vector of data
 * @return 	String with concatenated string
 */
template <typename T>
string WAQuery::VectorToStr(const char *prefix, bool individual, vector<T>& t) {
	return this->VectorToStr(string(prefix), individual, t);
}

/**
 * Concatenating a vector data to string
 *
 * @param   prefix      String prefix for data; example '&name='
 * @param   individual  Type of concatenating string
 * @param   t           Vector of data
 * @return 	String with concatenated string
 */
template <typename T>
string WAQuery::VectorToStr(string prefix, bool individual, vector<T>& t) {
    string q("");
    typename vector<T>::iterator tmpIter;

    if (t.size() == 0) return q;

    if (individual) {
        // [prefix][data][prefix][data]
        for (tmpIter = t.begin(); tmpIter < t.end(); tmpIter++) {
            q += prefix + to_string(*tmpIter);
        }
    }
    else {
        // [prefix][data,data,data,...]
        q += prefix;

        for (tmpIter = t.begin(); tmpIter < t.end(); tmpIter++) {
            q += to_string(*tmpIter);
            q += string(",");
        }
        q.pop_back(); // Erase last ','
    }
	
    return q;
}
