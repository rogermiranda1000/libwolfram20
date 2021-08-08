#include <iostream>
#include "WAEngine.h"
#include "secrets.h" // place here #define APP_ID

int main(int argc, char const *argv[]) {
	WAEngine searcher(APP_ID);
	
	std::string contents;
	std::string url = searcher.getURL( std::string("x^3 - 6x^2 + 4x + 12 = 32y") );
	std::cout << "Searching '" << url << "'..." << std::endl;
	if (!WAEngine::DownloadURL(url, &contents)) {
		std::cerr << "Downloading error!" << std::endl;
		return EXIT_FAILURE;
	}
	
	WAResult *search = searcher.getResult(contents);
	WAPod *response = search->getPod("Implicit plot");
	if (response != nullptr) {
		WASubpod *subpod = response->getSubpods()[0];
		if (subpod->hasImage()) std::cout << "Graph: " << subpod->getImage()->getSrc() << std::endl;
	}
	delete search;
	
	return 0;
}