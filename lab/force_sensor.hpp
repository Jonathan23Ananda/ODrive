// Force Sensor Header file
#ifndef __FORCE_SENSOR_HPP
#define __FORCE_SENSOR_HPP

#ifndef __ODRIVE_MAIN_H
#error "This file should not be included directly. Include odrive_main.h instead."
#endif

// Variables
extern float ref_ForceV; // Global Reference Variable
extern float oldEMA;     // Previous exponential moving average
extern float alpha;      // weighted co-eff

// Function Prototypes
float Zero_Force_Sensor(void);
float get_ref_forceV(void);
float EMA_filter(void);
void set_alpha(float num);

#endif // __FORCE_SENSOR_HPP
