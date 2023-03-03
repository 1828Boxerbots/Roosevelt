// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc2/command/CommandPtr.h>
#include "Constants.h"

#include <frc/motorcontrol/Spark.h>
#include <frc/motorcontrol/VictorSP.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>

#include <frc/Encoder.h>
#include <frc/ADIS16448_IMU.h>
#include <frc/ADIS16470_IMU.h>

#include "Util.h"

class DriveSub : public frc2::SubsystemBase {

 public:
  DriveSub(double* pIMUAngle);

  void Periodic() override;

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
  double GetLeftVelocity();
  double GetRightVelocity();

  // IMU FUNCTIONS
  double GetXAngle();
  double GetYAngle();
  double GetZAngle();

  const DriveStyles kDriveStyle = DriveStyles::RC_STYLE; 

 private:
  void ResetEncoders();
  void ResetIMU();

  ctre::phoenix::motorcontrol::can::WPI_VictorSPX m_leftOne {kLeftDrive1};
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX m_leftTwo {kLeftDrive2};
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX m_rightOne {kRightDrive1};
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX m_rightTwo {kRightDrive2};

  frc::Encoder m_leftEncoder{kLeftEncoderA, kLeftEncoderB};
  frc::Encoder m_rightEncoder{kRightEncoderA, kRightEncoderB};

  frc::ADIS16448_IMU m_imu;
  double* m_pIMUAngle;
};
