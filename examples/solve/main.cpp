#include "WAEngine.h"
#include "secrets.h" // place here #define APP_ID

int main(int argc, char const *argv[]) {
	WAEngine search(APP_ID);
	search.query.addFormat("html");
	search.query.addFormat("plaintext");

	search.query.setInput(std::string("3x+2=7"));
	
	std::string contents;
	std::cout << "Searching '" << search.getURL() << "'..." << std::endl;
	if (!WAEngine::DownloadURL(search.getURL(), &contents)) {
		std::cerr << "Downloading error!" << std::endl;
		return EXIT_FAILURE;
	}
	
	search.Parse(contents);
	int numPod = search.getCountPods();
	
	// TODO buscar el pod 'title="Implicit plot" scanner="Inequality2D"' para ecuaciones 2d
	// TODO buscar el pod 'title="Surface plot" scanner="Plot"' para ecuaciones 3d
	
	WAPod *response = search.getPod("Solution");
	if (response != nullptr) {
		cout << "Solution: "   << response->getSubpods()[0].getPlainText() << endl;
	}
	
	return 0;
}