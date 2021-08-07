/****************************************************************************
 *		@mainpage	libwolfram20
 *      Library for using Wolfram|Alpha API v2.0
 *
 *      @version 	2.0
 *      @author 	Nikolenko Konstantin <knikolenko@yandex.ru>
 *		@author 	Roger Miranda <contacto@rogermiranda1000.com>
 *		@date		2011-2021
 *		@copyright 	GNU General Public License
 ***************************************************************************/

/****************************************************************************
 *		@file 		WAEngine.h
 *      Wolfram API access point
 *
 *      @author 	Nikolenko Konstantin <knikolenko@yandex.ru>
 *		@author 	Roger Miranda <contacto@rogermiranda1000.com>
 *		@date		2011-2021
 ***************************************************************************/

#ifndef WAENGINE_H
#define WAENGINE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <curl/curl.h>	// download website contents
#include <sstream>		// std::stringstream
#include <regex>

#include <rapidxml/rapidxml_utils.hpp>

#include "WAQuery.h"
#include "WAPod.h"

/**
 * Wolfram API access point
 */
class WAEngine {
public:
    WAEngine(std::string appID, std::string server = "api.wolframalpha.com", std::string path = "/v2/query");
	~WAEngine();

    std::string getAppID();
    void setAppID(std::string appID);
    std::string getURL();
    std::string getURL(WAQuery query);

    bool Parse(string inputData);

    vector<WAPod*> getPods();
	WAPod *getPod(const char *title);

    bool isError();
	
	static bool DownloadURL(std::string url, std::string *readBuffer);

    WAQuery query;

private:
    std::string server;     	//!< Config of WolframAlpha address
    std::string path;       	//!< Config of WolframAlpha address
    std::string appID;      	//!< Config of WolframAlpha address

    std::string dataTypes;  	//!< Attribute of 'queryresult'
    std::string version;    	//!< Attribute of 'queryresult'

    std::vector<WAPod*> Pods;	//!< All the valid results of the query
};

#endif // WAENGINE_H
