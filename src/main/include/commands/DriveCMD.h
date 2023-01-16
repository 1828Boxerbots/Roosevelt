// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <frc/smartdashboard/SmartDashboard.h>

#include "../subsystems/DriveSub.h"
#include <frc/XboxController.h>
#include "Constants.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class DriveCMD
    : public frc2::CommandHelper<frc2::CommandBase, DriveCMD> {
 public:
  DriveCMD(DriveSub* pDrive, frc::XboxController *pXbox, double scale = 1.0);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  DriveSub* m_pDrive = nullptr;
  frc::XboxController* m_pXbox = nullptr;
  double m_scale;

  DriveSub::DriveStyles m_style;

  double m_RightX;
  double m_LeftX;
  double m_LeftY;
  double m_RightY;
};
