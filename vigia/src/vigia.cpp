//============================================================================
// Name        : vigia.cpp
// Author      : Batela Software
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <httpserver.hpp>

using namespace std;
using namespace httpserver;
int main() {
	bool error = false ;
	while (true){
		/**
		 * Aqui invocar al servidor local del datos...
		 */
		if (error == true){
			system("sudo shutdown -r 0");
		}
		sleep (20);
	}

}
