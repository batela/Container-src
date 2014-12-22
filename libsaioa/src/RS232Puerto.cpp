/*
 * RS232Puerto.cpp
 *
 *  Created on: Sep 21, 2014
 *      Author: borja
 */

#include "../include/RS232Puerto.h"

namespace container {
extern log4cpp::Category &log;


	RS232Puerto::RS232Puerto(string id,int baudrate) : Puerto(id,RS232){
	}

	RS232Puerto::~RS232Puerto() {
	// TODO Auto-generated destructor stub
	}

	int RS232Puerto::abrir(){
		log.info("%s: %s %s",__FILE__, "Comienza abrir puerto..",this->getName().data());
		serial_port.Open( this->getName()) ;
		if ( ! serial_port.good() ) {
			return -1;
		}
		// Default configuration
		serial_port.SetBaudRate( SerialStreamBuf::BAUD_9600 ) ;
		if ( ! serial_port.good() ){
			return(-1) ;
		}
		//
		// Set the number of data bits.
		//
		serial_port.SetCharSize( SerialStreamBuf::CHAR_SIZE_8 ) ;
		if ( ! serial_port.good() ){
			return(-1) ;
		}
		//
		// Disable parity.
		//
		serial_port.SetParity( SerialStreamBuf::PARITY_NONE ) ;
		if ( ! serial_port.good() ){
			return(-1) ;
		}
		//
		// Set the number of stop bits.
		//
		serial_port.SetNumOfStopBits( 1 ) ;
		if ( ! serial_port.good() ){
			return(-1) ;
		}
		//
		// Turn on hardware flow control.
		//

		serial_port.SetFlowControl( SerialStreamBuf::FLOW_CONTROL_NONE ) ;
		if ( ! serial_port.good() ){
			return(-1) ;
		}
		serial_port.SetVMin(0);
		serial_port.SetVTime(0);
		this->setIsOpen(true);
		log.info("%s: %s",__FILE__, "Puerto abierto!!");
		return 0 ;
	}

	void RS232Puerto::cerrar(){
		serial_port.Close();
		this->setIsOpen(false);
	}

	int RS232Puerto::reabrir(){
		this->cerrar();
		return ( this->abrir() );
	}
	/**
	 * Devuelve -1 si hay error.
	 */
	int RS232Puerto::leer (char buffer[]){
		int count = 0 ;
		int res = 0;

		while( (res = serial_port.rdbuf()->in_avail()) > 0  ){
			char next_byte;
			serial_port.get(next_byte);
			if (count < 255) buffer[count++] = next_byte;
			if (next_byte =='\n') break;
		}
		if (count >= 255 || res < 0 ) count = -1;
		buffer[count]= 0 ;
		return count;
	}

	int RS232Puerto::leerSimple (char data){
			int count = 0 ;
			int res = 0;

			if( (res = serial_port.rdbuf()->in_avail()) > 0  ){
				serial_port.get(data);
			}

			return res;
		}
	int RS232Puerto::escribir (char buffer[], int count){
			serial_port.write( buffer, count ) ;
			return 0;
		}
} /* namespace container */
