/*
 * brj.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: root
 */
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "../include/HMC5883L.h"

using namespace std;
#define address 0x1E
#define PI 3.14159265
int main() {
	HMC5883L brj;
	cout << "Iniciamos la brujula" <<endl;
	brj.initialize();
	cout << "Inicializada la brujula" <<endl;
	printf ("Modo GPS %d\n", brj.getMode());
	if (brj.testConnection())
		cout << "Brujula conex OK" <<endl;
	else
		cout << "Brujula conex KO" <<endl;

	while (1){
		int valorX = brj.getHeadingX() * 0.92;
		int valorY = brj.getHeadingY() * 0.92;
		float bearing = atan2(valorY, valorX);
		if (bearing < 0) bearing += 2 * PI;

		printf ("Hemos leido valor X-Y %d %d %f\n", valorX, valorY, ((bearing*180)/(PI)));
		sleep (1);
	}
	return 0;
}



