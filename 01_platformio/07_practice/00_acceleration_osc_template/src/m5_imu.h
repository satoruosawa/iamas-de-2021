#ifndef M5_IMU_H_
#define M5_IMU_H_

#ifndef M5STACK_MPU6886
#define M5STACK_MPU6886
#endif  // M5STACK_MPU6886

#include <M5Stack.h>
#include <MadgwickAHRS.h>
#include <Preferences.h>

#include "./bmm150.h"
#include "./bmm150_defs.h"
#include "./m5_bmm150.h"

class M5Imu {
 public:
  M5Imu();
  //   void calibrate(uint32_t calibrate_time);
  void initialize(float target_sample_frequency = 20);
  void update();
  void calibrateBmm150(uint32_t calibrate_time);
  void calibrateMpu6886();
  void getMagOffsetData(float *mag_offset_x, float *mag_offset_y,
                        float *mag_offset_z);
  void getGyroOffsetData(float *gyro_offset_x, float *gyro_offset_y,
                         float *gyro_offset_z);
  bool wasMeasured();
  float actualSampleFrequency();  // Hz
  float accX();
  float accY();
  float accZ();
  float gyroX();
  float gyroY();
  float gyroZ();
  float magX();
  float magY();
  float magZ();
  float headDirection();
  float roll();
  float pitch();
  float yaw();

 private:
  void loadOffsetMpu6886();
  void saveOffsetMpu6886();
  M5Bmm150 m5_bmm150_;
  Madgwick filter_;
  Preferences prefs_;
  float gyro_offset_x_;
  float gyro_offset_y_;
  float gyro_offset_z_;
  unsigned long interval_;
  unsigned long prev_update_;
  float actual_sample_frequency_;  // Hz
  float acc_x_;
  float acc_y_;
  float acc_z_;
  float gyro_x_;
  float gyro_y_;
  float gyro_z_;
  float mag_x_;
  float mag_y_;
  float mag_z_;
  float head_direction_;
  bool was_measured_;
};

#endif  // M5_IMU_H_