/*
 * DX80.h
 *
 *  Created on: May 1, 2015
 *      Author: root
 */

#ifndef DX80_H_
#define DX80_H_

namespace container {

class DX80 {
public:
	DX80();
	virtual ~DX80();
	int getInput1 (){ return valores[0];}
	int getInput2 (){ return valores[1];}
	int getInput3 (){ return valores[2];}
	int getInput4 (){ return valores[3];}
	int getPeso (){ return peso;}

	bool getIsOKInput1 (){ return isOKInput1;}
	bool getIsOKInput2 (){ return isOKInput2;}
	bool getIsOKInput3 (){ return isOKInput3;}
	bool getIsOKInput4 (){ return isOKInput4;}

	void setInput1(int a) {valores[0] = a;}
	void setInput2(int a) {valores[1] = a;}
	void setInput3(int a) {valores[2] = a;}
	void setInput4(int a) {valores[3] = a;}
	void setPeso(int a) {peso = a;}

	void setIsOKInput1(bool a) {isOKInput1 = a;}
	void setIsOKInput2(bool a) {isOKInput2 = a;}
	void setIsOKInput3(bool a) {isOKInput3 = a;}
	void setIsOKInput4(bool a) {isOKInput4 = a;}
	int  getValorIdx (int i) {return valores[i];}
	char getSigno () {return signo;}
	void setSigno (char a) {signo = a;}
private:
	int valores[4];
	int peso;
	char signo;
	bool isOKInput1;
	bool isOKInput2;
	bool isOKInput3;
	bool isOKInput4;
};

} /* namespace container */

#endif /* DX80_H_ */
