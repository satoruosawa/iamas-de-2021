#ifndef UI_H_
#define UI_H_

#include <M5Stack.h>

void drawNav(int mode);
void drawUi(int mode);
void drawGyroUi();
void drawMagUi();
void drawGyroValue(float gyro_x, float gyro_y, float gyro_z,
                   float gyro_offset_x, float gyro_offset_y,
                   float gyro_offset_z);
void drawMagValue(float mag_x, float mag_y, float mag_z, float mag_offset_x,
                  float mag_offset_y, float mag_offset_z);
void drawCompassFrame();
void drawCompassNeedle(float angle);

#endif  // UI_H_