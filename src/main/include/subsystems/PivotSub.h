// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include "Util.h"
#include "Constants.h"

#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <frc/Encoder.h>

class PivotSub : public frc2::SubsystemBase {
 public:
  PivotSub();

  void Init();
  void SetPivotMotor(double speed);
  double GetPivotAngle();

 private:
  void ResetPivotEncoder();

  ctre::phoenix::motorcontrol::can::WPI_VictorSPX m_pivot{kPivotMotor};

  frc::Encoder m_encoder{kPivotEncoderA, kPivotEncoderB};
};
