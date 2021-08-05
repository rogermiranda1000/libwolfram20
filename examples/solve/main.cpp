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
		int numSubPod = response->getCountSubpods();
		int numStates = response->getCountStates();
		
		WASubpod * subpods = response->getSubpods();
		WAPodState * states = response->getStates();
		
		// Enumerate a subpods
		for (int j = 0; j < numSubPod; j++)
		{
			cout << "\tSubPod "  << j << endl;
			// Get a subpod attributes
			cout << "\t\tTitle:"   << subpods[j].getTitle() << endl;
			// Get a built-in img attributes
			cout << "\tImg" << endl;
			cout << "\t\tTitle:" << subpods[j].getImage()->getTitle() << endl;
			cout << "\t\tSrc:"   << subpods[j].getImage()->getSrc() << endl;

		}
		
		// Enumerate a states
		for (int j = 0; j < numStates; j++)
		{
			cout << "\tStates " << j << endl;
			cout << "\t\tName:" << states[j].getName() << endl;
		}
	}
	
	return 0;
}