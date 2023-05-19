#define _GLIBCXX_USE_CXX11_ABI 0

#include <iostream>
#include <string>
//#include <TFile.h>
//#include <TString.h>
//#include <TTree.h>

int main(int argc, char* argv[]) {
	using std::cout;
	using std::endl;

	try
	{
		if (argv[1]) {
			cout << "The file is processing: " << argv[1] << endl;
		}
		else {
			throw 0;
			//throw return to the catch
		}


	}
	catch (int exc)
	{
		std::cerr << "[Error] There's an error.\n";
		switch (exc) {
		case 0:
			std::cout << "there's no file\n";
			break;
		case 1:
			std::cout << "second error\n";
			break;
		default:
			break;
		}

	}

	
}