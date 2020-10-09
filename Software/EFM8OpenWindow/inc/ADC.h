/*
 * ADC.h
 *
 *  Created on: 29 Sep 2020
 *      Author: alan
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include <stdint.h>

// Empirically determined current limit
#define ADC_MAX_RAISE_VAL 8000
#define ADC_MIN_RAISE_VAL 4000

#define ADC_MAX_LOWER_VAL 10500
#define ADC_MIN_LOWER_VAL 8500


void ADC_start(uint16_t min_val, uint16_t max_val);

void ADC_stop(void);

void ADC_callback(void);

#endif /* INC_ADC_H_ */
