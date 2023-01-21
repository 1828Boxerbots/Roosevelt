// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/IntakeSub.h"

#include <frc/Timer.h>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ROCKYshoot
    : public frc2::CommandHelper<frc2::CommandBase, ROCKYshoot> {
 public:
  ROCKYshoot(IntakeSub *pIntake, double speed);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  IntakeSub* m_pIntake;
  double m_speed;

  frc::Timer m_time;
};
