/****************************************************************************
 *		@mainpage	libwolfram20
 *      Library for using Wolfram|Alpha API v2.0
 *
 *      @version 	2.1
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
#include <curl/curl.h>	// download website contents

#include <rapidxml/rapidxml_utils.hpp>

#include "WAResult.h"
#include "WAQuery.h"

/**
 * Wolfram API access point
 */
class WAEngine {
public:
    WAEngine(std::string appID, std::string server = "api.wolframalpha.com", std::string path = "/v2/query");

    std::string getURL(std::string input);
    WAResult getResult(std::string inputData);
	
	void setTimeout(unsigned int timeout);
	
	static bool DownloadURL(std::string url, std::string *readBuffer);

private:
    std::string server;     	//!< Config of WolframAlpha address
    std::string path;       	//!< Config of WolframAlpha address
    std::string appID;      	//!< Config of WolframAlpha address
	WAQuery _query;				//!< Query to make the request
};

#endif // WAENGINE_H
