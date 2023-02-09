// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "Constants.h"
#include "Util.h"

#include <frc/DoubleSolenoid.h>
#include <frc/Compressor.h>

#include "rev/ColorSensorV3.h"

class IntakeSub : public frc2::SubsystemBase {
 public:
  IntakeSub();

  enum ColorTargets
  {
    CONE, CUBE, NOTHING=0
  };

  void Init();

  // MOTOR FUNCTIONS
  void SetIntake(bool isOpen);
  bool IsIntakeOpen();

  // COLOR SENSOR FUNCTIONS
  ColorTargets GetHeldObject();

  // LED INDICATOR
  void SetLED();

 private:
  frc::DoubleSolenoid m_intake{0, frc::PneumaticsModuleType::CTREPCM, kForwardChannel, kBackwardChannel};
  rev::ColorSensorV3 m_colorSensor{frc::I2C::kOnboard};
  frc::Compressor m_compressor{0, frc::PneumaticsModuleType::CTREPCM};

  // Color Values
  frc::Color m_ConeTarget = frc::Color(0.34, 0.52, 0.1);
  frc::Color m_CubeTarget = frc::Color(0.21, 0.32, 0.47);

  double m_CubeDead = 0.05;
  double m_ConeDead = 0.035;

  bool m_isIntakeOpen;
};
