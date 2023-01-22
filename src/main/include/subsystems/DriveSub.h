// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include <frc/motorcontrol/Spark.h>
#include <frc/motorcontrol/VictorSP.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>

#include <frc/Encoder.h>
#include <frc/ADIS16448_IMU.h>
#include <frc/ADIS16470_IMU.h>

#include "Util.h"

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
  double GetLeftDist();
  double GetRightDist();
  void ResetEncoders();
  double GetLeftVelocity();
  double GetRightVelocity();

  // IMU FUNCTIONS
  double GetXAngle();
  double GetYAngle();
  double GetZAngle();

  void Periodic() override;

 private:
  frc::Spark m_leftDrive{1};
  frc::Spark m_rightDrive{0};

  ctre::phoenix::motorcontrol::can::WPI_VictorSPX m_victor {0};

  frc::Encoder m_leftEncoder{8, 9, true};
  frc::Encoder m_rightEncoder{0, 1, true};

  frc::ADIS16448_IMU m_imu;
  frc::ADIS16470_IMU m_newIMU;
};
