/*
 * Enlace.cpp
 *
 *  Created on: Sep 25, 2014
 *      Author: borja
 */

#include "../include/Enlace.h"

namespace container {

Enlace::Enlace() {
	// TODO Auto-generated constructor stub

}

Enlace::~Enlace() {
	// TODO Auto-generated destructor stub
}
std::vector<std::string> & Enlace::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> Enlace::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
} /* namespace container */
