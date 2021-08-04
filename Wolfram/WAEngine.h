/*
 *      Library for using Wolfram|Alpha API v2.0
 *
 *      Version of library: 1.0
 *
 *      WAEngine.h
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#ifndef WAENGINE_H
#define WAENGINE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

#include <rapidxml/rapidxml_utils.hpp>

#include "WAQuery.h"
#include "WAPod.h"

using namespace std;
using namespace rapidxml;

class WAEngine
{
public:
    WAEngine(string appid, string server = "api.wolframalpha.com", string path = "/v2/query");
    virtual ~WAEngine();

    string  getAppID();
    void    setAppID(string appid);
    string  getURL();
    string  getURL(WAQuery query);

    bool    Parse();
    bool    Parse(string filename);
    bool    Parse(char * inputData);

    int     getCountPods();
    WAPod*  getPods();

    bool    isError();

    WAQuery query;

private:
    int     error;

    string  server;     // Config of WolframAlpha address
    string  path;       // Config of WolframAlpha address
    string  appID;      // Config of WolframAlpha address

    string  dataTypes;  // Attribute of 'queryresult'
    string  version;    // Attribute of 'queryresult'

    size_t  countPods;  // Count of blocks Pod
    WAPod * Pods;

    char *  data;       // Text for parsing
    size_t  length;     // Length of text, unused
};

#endif // WAENGINE_H
