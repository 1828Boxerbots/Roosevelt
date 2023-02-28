// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/IntakeSub.h"

#include <frc/Timer.h>
#include "Constants.h"
#include "Util.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class IntakeCMD
    : public frc2::CommandHelper<frc2::CommandBase, IntakeCMD> {
 public:
  IntakeCMD(IntakeSub* pIntake, bool useIsFinished = false, double holdtime = 0.5, bool choseOpen = false, bool isOpen = false);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  IntakeSub* m_pIntake;
  bool m_useIsFinished;
  double m_holdTime;
  bool m_choseOpen;
  bool m_isOpen;

  frc::Timer m_timer;
};
