#ifndef WARESULT_H
#define WARESULT_H

#include <string>
#include <vector>

#include <rapidxml/rapidxml_utils.hpp>

#include "WAQuery.h"
#include "WAPod.h"


/**
 * Query timings
 */
typedef struct {
	float parse;		//!< Time in seconds required to parse the input
	float generate;		//!< Time in seconds required to generate the output
} Timings;

/**
 * Wolfram API result. It contains all the Pods
 * More information [on Wolfram documentation](https://products.wolframalpha.com/api/documentation/#result-queryresult)
 */
class WAResult {
public:
    WAResult(rapidxml::xml_node<>* query);
    ~WAResult();

    std::vector<WAPod*> getPods();
	WAPod *getPod(const char *title);
    bool isError();
	unsigned int getTimedout();

private:
	bool _error;				//!< The input could be successfully understood or a serious processing error occurred
    std::string _dataTypes;  	//!< Categories and types of data represented in the results
    std::string _version;    	//!< The version specification of the API on the server that produced this result
	Timings _timings;			//!< Time in seconds required to parse the input and generate the output
	
	unsigned int _timedout;		//!< Number of pods that are missing because they timed out
	std::string _try_again;		//!< If _timedout > 0 this will contain an URL to perform the next search

    std::vector<WAPod*> _pods;	//!< All the results of the query

    void parse(rapidxml::xml_node<>* query);
	static unsigned int countTimedout(char *timedout);
};

#endif // WARESULT_H
