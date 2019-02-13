// Force Sensor C++ file
#include <stm32f405xx.h>
#include <stm32f4xx_hal.h>
#include <stdint.h>

#include <force_sense.h>
#include <adc.h>
#include <gpio.h>
#include <main.h>

#include "odrive_main.h"

// Private Variables
float ref_ForceV; // Global Reference Variable
float oldEMA;     // Previous exponential moving average
float alpha;      // weighted co-eff


// Sets the Zero-Force value of the sensor
float Zero_Force_Sensor(void)
{
	float force_voltage = 0;
	count = 0;

	for (i = 0; i < 100; i++){ // Replace with timer?
		force_voltage += get_adc_voltage(&GPIOA, GPIO_PIN_x); // x = [4:1]
		count++;
		for (int j = 0; j < 60000; j++){} // Basic delay. ADC samples every 35 kHz.
	}

	ref_ForceV = (force_voltage/count); // Set global reference variable
  oldEMA = ref_ForceV;                // Initially set EMA
	return ref_ForceV;                  // return zero reference voltage
}

// Helper method: Returns the Zero-Force voltage
float get_ref_forceV(void)
{
  return (ref_ForceV > 0) ? ref_ForceV : -1.0;
}


// Exponential Moving Average Filter
float EMA_filter(void)
{
    // Obtain new ADC reading
    float newADC = get_adc_voltage(&GPIOA, GPIO_PIN_x); // x = [4:1]

    // Calculate new EMA
    float newEMA = oldEMA + alpha * (newADC - oldEMA);
    oldEMA = newEMA;
    return newEMA;
}


// Helper method: Sets the alpha weight co-eff
void set_alpha(float num)
{
  alpha = num;
}
