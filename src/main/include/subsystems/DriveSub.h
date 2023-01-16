// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include <frc/motorcontrol/Spark.h>
#include <frc/Encoder.h>
#include <frc/ADIS16448_IMU.h>

class DriveSub : public frc2::SubsystemBase {

 public:
  DriveSub();

  enum DriveStyles
  {
    RC_STYLE,
    TANK_STYLE,
    ARCADE_STYLE
  };

  void Init();

  // Motor Functions
  void MoveTank(double left, double right);
  void MoveRC(double horizontal, double vertical);

  // Encoder Functions
  int GetLeftDist();
  int GetRightDist();
  void ResetEncoders();

  // IMU FUNCTIONS
  double GetXAngle();
  double GetYAngle();
  double GetZAngle();

  void Periodic() override;

 private:
  frc::Spark m_leftDrive{1};
  frc::Spark m_rightDrive{0};

  frc::Encoder m_leftEncoder{0, 1};
  frc::Encoder m_rightEncoder{2, 3};

  frc::ADIS16448_IMU m_imu;
};
