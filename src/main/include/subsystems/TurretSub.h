// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include <frc/ADIS16448_IMU.h>
#include <frc/ADIS16470_IMU.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <frc/Encoder.h>

#include "Constants.h"
#include "Util.h"

class TurretSub : public frc2::SubsystemBase {
 public:
  TurretSub(double* pTurretAngle);

  void Init();

  void Periodic() override;

  // MOTOR FUNCTIONS
  void SetTurretMotor(double speed);

  // ENCODER FUNCTIONS
  double GetTurretAngle();

 private:
  void ResetTurretEncoder();

  ctre::phoenix::motorcontrol::can::WPI_VictorSPX m_turret{kTurretMotor};
  frc::Encoder m_encoder {kTurretEncoderA, kTurretEncoderB};

  double* m_pTurretAngle = nullptr;
};
