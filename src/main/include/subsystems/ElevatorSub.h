// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include "Util.h"
#include "Constants.h"

#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <frc/Encoder.h>

class ElevatorSub : public frc2::SubsystemBase {
 public:
  ElevatorSub();

  void Init();
  void SetElevatorMotor(double speed);
  double GetElevatorLength();

 private:
  void ResetElevatorEncoder();

  ctre::phoenix::motorcontrol::can::WPI_VictorSPX m_elevator {kElevatorMotor};
  frc::Encoder m_encoder {kElevatorEncoderA, kElevatorEncoderB};
};
