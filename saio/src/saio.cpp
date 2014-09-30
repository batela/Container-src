//============================================================================
// Name        : saio.cpp
// Author      : Batela
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/NDC.hh"
#include "log4cpp/PropertyConfigurator.hh"
using namespace std;

int main() {
	log4cpp::Category &log_root = log4cpp::Category::getRoot();


    try{
    	log4cpp::PropertyConfigurator::configure( "../cnf/log4cpp.properties" );
    	log_root.error("root error");
    	log_root.warn("root warn");


    }
    catch( log4cpp::ConfigureFailure &e ){
    	cout << "adfsfafs" << e.what() << endl; // prints !!!Hello World!!!
    }
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
