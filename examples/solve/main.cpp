#include "WAEngine.h"
#include "secrets.h" // place here #define APP_ID
#include <sstream>

int main(int argc, char const *argv[]) {
	WAEngine searcher(APP_ID);
	
	std::string contents;
	std::string url = searcher.getURL( std::string("3x+2=7") );
	std::cout << "Searching '" << url << "'..." << std::endl;
	if (!WAEngine::DownloadURL(url, &contents)) {
		std::cerr << "Downloading error!" << std::endl;
		return EXIT_FAILURE;
	}
	
	WAResult search = searcher.getResult(contents);
	WAPod response;
	if (search.getPod("Solution", &response)) {
		std::cout << "Solution: " << response.getSubpods()[0].getPlainText() << std::endl;
	}
	
	return 0;
}