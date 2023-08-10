#ifndef MT6701_H_
#define MT6701_H_

#include <Arduino.h>
#include <SPI.h>

struct MT6701_t {
public:
	MT6701_t(SPIClass *spi, uint8_t csn) {
		this->spi = spi;
		this->csn = csn;
	}
	void Init();
	void Sample();
	float GetAngle();
	uint8_t GetStatus();
	uint8_t GetField();
	uint8_t GetButton();
	
private:
	SPIClass *spi;
	uint32_t data;
	uint8_t  csn;
};

#endif // MT6701_H_