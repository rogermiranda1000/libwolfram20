#ifndef WARESULT_H
#define WARESULT_H

#include <string>
#include <vector>

#include <rapidxml/rapidxml_utils.hpp>

#include "WAQuery.h"
#include "WAPod.h"

class WAResult {
public:
    WAResult(rapidxml::xml_node<>* query);
    ~WAResult();

    std::vector<WAPod*> getPods();
	WAPod *getPod(const char *title);
    bool isError();

private:
	bool _error;				//!< Attribute of 'queryresult'
    std::string dataTypes;  	//!< Attribute of 'queryresult'
    std::string version;    	//!< Attribute of 'queryresult'

    std::vector<WAPod*> _pods;	//!< All the results of the query

    void parse(rapidxml::xml_node<>* query);
};

#endif // WARESULT_H
