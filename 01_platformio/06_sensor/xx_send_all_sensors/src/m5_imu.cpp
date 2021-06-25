#include "./m5_imu.h"

M5Imu::M5Imu()
    : gyro_offset_x_(0),
      gyro_offset_y_(0),
      gyro_offset_z_(0),
      interval_(0),
      prev_update_(0),
      actual_sample_frequency_(0),
      acc_x_(0),
      acc_y_(0),
      acc_z_(0),
      gyro_x_(0),
      gyro_y_(0),
      gyro_z_(0),
      mag_x_(0),
      mag_y_(0),
      mag_z_(0),
      head_direction_(0),
      was_measured_(false) {}

void M5Imu::initialize(float target_sample_frequency) {
  M5.Power.begin();
  M5.IMU.Init();
  interval_ = 1000000 / target_sample_frequency;
  filter_.begin(target_sample_frequency);
  Wire.begin(21, 22, 400000);
  if (m5_bmm150_.initialize() != BMM150_OK) {
    Serial.println("BMM150 initialization failed.");
    while (1)
      ;
  }
  m5_bmm150_.loadOffset();
  loadOffsetMpu6886();
}

void M5Imu::update() {
  was_measured_ = false;
  unsigned long now = micros();
  if (now < prev_update_ + interval_) return;
  actual_sample_frequency_ = 1000000 / (float)(now - prev_update_);
  prev_update_ = now;
  was_measured_ = true;
  M5.IMU.getAccelData(&acc_x_, &acc_y_, &acc_z_);
  M5.IMU.getGyroData(&gyro_x_, &gyro_y_, &gyro_z_);
  gyro_x_ += gyro_offset_x_;
  gyro_y_ += gyro_offset_y_;
  gyro_z_ += gyro_offset_z_;
  m5_bmm150_.update();
  m5_bmm150_.getCalibratedData(&mag_x_, &mag_y_, &mag_z_);
  head_direction_ = m5_bmm150_.getHeadDirection();
  filter_.update(gyro_x_, gyro_y_, gyro_z_, acc_x_, acc_y_, acc_z_, mag_x_,
                 -mag_y_, mag_z_);
}

void M5Imu::calibrateBmm150(uint32_t calibrate_time) {
  m5_bmm150_.calibrate(calibrate_time);
}

void M5Imu::calibrateMpu6886() {
  float gyro_x, gyro_y, gyro_z;
  M5.IMU.getGyroData(&gyro_x, &gyro_y, &gyro_z);
  gyro_offset_x_ = -gyro_x;
  gyro_offset_y_ = -gyro_y;
  gyro_offset_z_ = -gyro_z;
  saveOffsetMpu6886();
}

void M5Imu::getMagOffsetData(float *mag_offset_x, float *mag_offset_y,
                             float *mag_offset_z) {
  m5_bmm150_.getOffsetData(mag_offset_x, mag_offset_y, mag_offset_z);
}

void M5Imu::getGyroOffsetData(float *gyro_offset_x, float *gyro_offset_y,
                              float *gyro_offset_z) {
  *gyro_offset_x = gyro_offset_x_;
  *gyro_offset_y = gyro_offset_y_;
  *gyro_offset_z = gyro_offset_z_;
}

void M5Imu::loadOffsetMpu6886() {
  if (prefs_.begin("mpu6886", true)) {
    gyro_offset_x_ = prefs_.getFloat("x", 0);
    gyro_offset_y_ = prefs_.getFloat("y", 0);
    gyro_offset_z_ = prefs_.getFloat("z", 0);
    prefs_.end();
    Serial.printf("mpu6886 load offset finish.... \r\n");
  } else {
    Serial.printf("mpu6886 load offset failed.... \r\n");
  }
}

void M5Imu::saveOffsetMpu6886() {
  prefs_.begin("mpu6886", false);
  prefs_.putFloat("x", gyro_offset_x_);
  prefs_.putFloat("y", gyro_offset_y_);
  prefs_.putFloat("z", gyro_offset_z_);
  prefs_.end();
}

bool M5Imu::wasMeasured() { return was_measured_; }
float M5Imu::actualSampleFrequency() { return actual_sample_frequency_; }
float M5Imu::accX() { return acc_x_; }
float M5Imu::accY() { return acc_y_; }
float M5Imu::accZ() { return acc_z_; }
float M5Imu::gyroX() { return gyro_x_; }
float M5Imu::gyroY() { return gyro_y_; }
float M5Imu::gyroZ() { return gyro_z_; }
float M5Imu::magX() { return mag_x_; }
float M5Imu::magY() { return mag_y_; }
float M5Imu::magZ() { return mag_z_; }
float M5Imu::headDirection() { return head_direction_; }
float M5Imu::roll() { return filter_.getRoll(); }
float M5Imu::pitch() { return filter_.getPitch(); }
float M5Imu::yaw() { return filter_.getYaw(); }
