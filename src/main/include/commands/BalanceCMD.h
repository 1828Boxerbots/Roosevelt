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

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class BalanceCMD
    : public frc2::CommandHelper<frc2::CommandBase, BalanceCMD> {
 public:
  BalanceCMD(DriveSub* pDrive, bool useIsFinished = false, double pidTolerance = 1.5, double waitTime = 0.5);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
  
 private:
  DriveSub *m_pDrive;

  frc::PIDController m_pid{0.05, 0, 0};

  double m_pidTolerance;
  double m_waitTime;
  bool m_useIsFinished;

  frc::Timer m_timer;
};
