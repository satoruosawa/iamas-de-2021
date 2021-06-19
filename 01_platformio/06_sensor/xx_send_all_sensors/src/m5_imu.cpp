#include "./m5_imu.h"

M5Imu::M5Imu() {
  gyro_offset_x_ = 0;
  gyro_offset_y_ = 0;
  gyro_offset_y_ = 0;
  acc_x_ = 0;
  acc_y_ = 0;
  acc_z_ = 0;
  gyro_x_ = 0;
  gyro_y_ = 0;
  gyro_z_ = 0;
  mag_x_ = 0;
  mag_y_ = 0;
  mag_z_ = 0;
  was_measured_ = false;
}

void M5Imu::initialize(float target_freq) {
  M5.Power.begin();
  M5.IMU.Init();
  interval_ = 1000000 / target_freq;
  filter_.begin(target_freq);
  Wire.begin(21, 22, 400000);
  if (m5_bmm150_.initialize() != BMM150_OK) {
    Serial.println("BMM150 initialization failed.");
    while (1)
      ;
  }
  m5_bmm150_.loadOffset();
  loadOffset();
}

void M5Imu::loadOffset() {
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

void M5Imu::saveOffset() {
  prefs_.begin("mpu6886", false);
  prefs_.putFloat("x", gyro_offset_x_);
  prefs_.putFloat("y", gyro_offset_y_);
  prefs_.putFloat("z", gyro_offset_z_);
  prefs_.end();
}

void M5Imu::update() {
  was_measured_ = false;
  unsigned long now = micros();
  if (now < prev_update_ + interval_) return;
  actual_freq_ = 1000000 / (float)(now - prev_update_);
  prev_update_ = now;
  was_measured_ = true;
  M5.IMU.getAccelData(&acc_x_, &acc_y_, &acc_z_);
  M5.IMU.getGyroData(&gyro_x_, &gyro_y_, &gyro_z_);
  gyro_x_ += gyro_offset_x_;
  gyro_y_ += gyro_offset_y_;
  gyro_z_ += gyro_offset_z_;
  m5_bmm150_.update();
  m5_bmm150_.getCalibratedData(&mag_x_, &mag_y_, &mag_z_);
  filter_.update(gyro_x_, gyro_y_, gyro_z_, acc_x_, acc_y_, acc_z_, mag_x_,
                 -mag_y_, mag_z_);
}

void M5Imu::getAccelData(float *acc_x, float *acc_y, float *acc_z) {
  *acc_x = acc_x_;
  *acc_y = acc_y_;
  *acc_z = acc_z_;
}

void M5Imu::getGyroData(float *gyro_x, float *gyro_y, float *gyro_z) {
  *gyro_x = gyro_x_;
  *gyro_y = gyro_y_;
  *gyro_z = gyro_z_;
}

void M5Imu::getMagData(float *mag_x, float *mag_y, float *mag_z) {
  *mag_x = mag_x_;
  *mag_y = mag_y_;
  *mag_z = mag_z_;
}

void M5Imu::getRollPitchYaw(float *roll, float *pitch, float *yaw) {
  *roll = filter_.getRoll();
  *pitch = filter_.getPitch();
  *yaw = filter_.getYaw();
}

float M5Imu::getHeadDirection() { return m5_bmm150_.getHeadDirection(); }

float M5Imu::getActualFreq() { return actual_freq_; }

bool M5Imu::wasMeasured() { return was_measured_; }
