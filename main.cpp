#define _GLIBCXX_USE_CXX11_ABI 0

#include <iostream>
#include <string>
#include "EcalSimHandler.hh"

using std::cerr;

int main(int argc, char* argv[]) {

	try
	{
		if (argv[1]) {
			cout << "\n";
			cout << "The file is processing: " << argv[1] << endl;
			cout << "\n";
		}
		else {
			throw 0;
			//throw return to the catch
		}

		// Check output
		cout << "======================================\n";
		cout << "============== ECAL SIM ==============\n";
		cout << "======================================\n";

		EcalSimHandler esimh(argv[1]);
		esimh.Loop();

		cout << "\n";
		cout <<	"======================================\n";

	}
	catch (int exc)
	{
		cerr << "\n";
		switch (exc) {
		case 0:
			cerr << "[Error 000] No inputs given.\n";
			break;
		case 1:
			cerr << "[Error 001] File does not exist.\n";
			break;
		default:
			break;
		}
		cerr << "\n";

	}

	
}