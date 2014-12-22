/*
 * Locks.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: root
 */

#include "../include/Locks.h"

namespace container {

Locks::Locks() {
	// TODO Auto-generated constructor stub

}

int Locks::GetLock (int i){
	int res = 0;
	switch (i){
		case 1: res = GetLock01(); break;
		case 2: res = GetLock02(); break;
		case 3: res = GetLock03(); break;
		case 4: res = GetLock04(); break;
		default: res = 0; break;
	}
	return res;
}
Locks::~Locks() {
	// TODO Auto-generated destructor stub
}

} /* namespace container */
