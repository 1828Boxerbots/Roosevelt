// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/DoubleSolenoid.h>

#include <frc2/command/CommandPtr.h>

#include "rev/ColorSensorV3.h"

class IntakeSub : public frc2::SubsystemBase {
 public:
  IntakeSub();

  enum ColorTargets
  {
    CONE, CUBE, NOTHING=0
  };

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  // MOTOR FUNCTIONS
  void SetIntake(bool setOpen);
  frc2::CommandPtr IntakeOpen();
  frc2::CommandPtr IntakeClose();

  // COLOR SENSOR FUNCTIONS
  ColorTargets GetColorTarget();

 private:
  frc::DoubleSolenoid m_intake{frc::PneumaticsModuleType::CTREPCM, 0, 1};

  rev::ColorSensorV3 m_colorSensor{frc::I2C::kOnboard};

  // Color Values
  frc::Color m_ConeTarget = frc::Color(0.34, 0.52, 0.1);
  frc::Color m_CubeTarget = frc::Color(0.21, 0.32, 0.47);

  double m_CubeDead = 0.05;
  double m_ConeDead = 0.035;

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
