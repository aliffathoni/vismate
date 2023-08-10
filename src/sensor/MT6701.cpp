#include "MT6701.h"

void MT6701_t::Init() {
	pinMode(csn, OUTPUT);
}

void MT6701_t::Sample() {
	digitalWrite(csn, LOW);
	data = spi->transfer32(0);
	digitalWrite(csn, HIGH);
}

float MT6701_t::GetAngle() {
	float angle;
	
	angle = ((data >> 10) & 0x3FFF) * 0.02197;
	
	return angle;
}

uint8_t MT6701_t::GetStatus() {
	return (data >> 9) & 0b1;
}

uint8_t MT6701_t::GetField() {
	return (data >> 6) & 0b11;
}

uint8_t MT6701_t::GetButton() {
	return (data >> 8) & 0b1;
}