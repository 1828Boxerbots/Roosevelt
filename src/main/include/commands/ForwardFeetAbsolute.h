// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/DriveSub.h"
#include "subsystems/TurretSub.h"
#include <frc/controller/PIDController.h>

#include <frc/Timer.h>
#include "Util.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ForwardFeetAbsolute
    : public frc2::CommandHelper<frc2::CommandBase, ForwardFeetAbsolute> {
 public:
  ForwardFeetAbsolute(DriveSub *pDrive, double distance, double tolerance);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  DriveSub* m_pDrive;
  double m_distance;

  frc::PIDController m_forwardPID{0.4, 0, 0};
  frc::PIDController m_allignPID{0.15, 0, 0.1};

  frc::Timer m_timer;
  double m_yesTime = 0.0;
  bool m_isFinished = false;
};
