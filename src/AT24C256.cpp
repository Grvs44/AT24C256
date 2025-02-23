//AT24C256 driver CPP file
#include "Arduino.h"
#include "Wire.h"
#include "AT24C256.h"

AT24C256::AT24C256(byte address){
	Wire.begin();
	_address = address;
}

void AT24C256::write(unsigned short writeAddress, byte* data, byte len){
	byte thisLen;
	while(len > 0){
		if(len > 16){
			thisLen = 16;
			len -= thisLen;
		}
		else{
			thisLen = len;
			len = 0;
		}
		Wire.beginTransmission(_address);
		Wire.write(writeAddress >> 8);
		Wire.write(writeAddress & 0xFF);
		for(byte i = 0; i < thisLen; i++) Wire.write(data[i]);
		Wire.endTransmission();
		writeAddress += thisLen;
		delay(6);
	}
}

void AT24C256::read(unsigned short readAddress, byte* data, byte len){
	Wire.beginTransmission(_address);
	Wire.write(readAddress >> 8);
	Wire.write(readAddress & 0xFF);
	Wire.endTransmission();
	Wire.requestFrom(_address, len);
	for(byte i = 0; i < len; i++)
		if(Wire.available())
			data[i] = Wire.read();
		else
			break;
}