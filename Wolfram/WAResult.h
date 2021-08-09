#ifndef WARESULT_H
#define WARESULT_H

#include <sstream>
#include <string>
#include <vector>

#include <rapidxml/rapidxml_utils.hpp>

#include "WAQuery.h"
#include "WAPod.h"
#include "WAError.h"


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
    WAResult(const WAResult &old);
    WAResult(rapidxml::xml_node<>* query);
    ~WAResult();

    std::vector<WAPod> getPods();
	bool getPod(const char *title, WAPod *pod);
	
	unsigned int getTimedoutNumber();
	std::vector<std::string> getTimedout();
	
    bool isError();
	WAError *getError();

private:
	bool _is_error;						//!< The input could be successfully understood or a serious processing error occurred
	WAError *_error;					//!< Information about the given error
	
    std::string _dataTypes;  			//!< Categories and types of data represented in the results
    std::string _version;    			//!< The version specification of the API on the server that produced this result
	Timings _timings;					//!< Time in seconds required to parse the input and generate the output
	
	std::vector<std::string> _timedout;	//!< Number of pods that are missing because they timed out
	std::string _try_again;				//!< If _timedout > 0 this will contain an URL to perform the next search

    std::vector<WAPod> _pods;			//!< All the results of the query

    void parse(rapidxml::xml_node<>* query);
	static std::vector<std::string> splitTimedout(const std::string& s);
};

#endif // WARESULT_H
