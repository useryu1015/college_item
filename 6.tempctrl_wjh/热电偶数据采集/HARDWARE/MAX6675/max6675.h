#ifndef __MAX66_H_
#define __MAX66_H_

extern int sensor_state;

void SPI_MAX6675_Init(void);
float read_max6675 (void);

#endif