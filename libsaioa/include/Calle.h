/*
 * Calle.h
 *
 *  Created on: Oct 2, 2014
 *      Author: borja
 */

#ifndef CALLE_H_
#define CALLE_H_

class Calle {
public:
	Calle();
	virtual ~Calle();

	float getA1() const 	{	return a1;	}
	void setA1(float a1) 	{	this->a1 = a1;	}
	float getA2() const 	{	return a2;	}
	void setA2(float a2) 	{	this->a2 = a2;	}
	float getA3() const 	{	return a3;	}
	void setA3(float a3) 	{	this->a3 = a3;	}
	float getA4() const 	{	return a4;	}
	void setA4(float a4) 	{	this->a4 = a4;	}
	float getEspacioContainer() const {		return espacioContainer;	}
	void setEspacioContainer(float espacioContainer) {		this->espacioContainer = espacioContainer;	}
	float getXf() const 	{	return Xf;	}
	void setXf(float xf) 	{	Xf = xf;	}
	float getXi() const 	{	return Xi;	}
	void setXi(float xi)	{	Xi = xi;	}
	float getYf() const 	{	return Yf;	}
	void setYf(float yf) 	{	Yf = yf;	}
	float getYi() const 	{	return Yi;	}
	void setYi(float yi) 	{	Yi = yi;	}

private:
	float Xi;
	float Yi;
	float Xf;
	float Yf;
	float espacioContainer;
	float a1;
	float a2;
	float a3;
	float a4;
};

#endif /* CALLE_H_ */
