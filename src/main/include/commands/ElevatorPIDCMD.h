// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <frc/Timer.h>
#include <frc/controller/PIDController.h>
#include "subsystems/ElevatorSub.h"
#include "Constants.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ElevatorPIDCMD
    : public frc2::CommandHelper<frc2::CommandBase, ElevatorPIDCMD> {
 public:
  ElevatorPIDCMD(ElevatorSub* pElevator, double setLength, bool useIsFinished = false, double holdtime = 0.5, double threshold = 0.1);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
 private:
  ElevatorSub* m_pElevator;
  double m_setLength;
  bool m_useIsFinished;
  double m_holdTime;
  double m_threshold;

  frc::PIDController m_pid{kElevatorP, kElevatorI, kElevatorD};

  frc::Timer m_timer;
};
