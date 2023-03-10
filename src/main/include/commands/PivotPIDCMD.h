// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <frc/Timer.h>
#include <frc/controller/PIDController.h>
#include "subsystems/PivotSub.h"

#include "Constants.h"
#include "Util.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class PivotPIDCMD
    : public frc2::CommandHelper<frc2::CommandBase, PivotPIDCMD> {
 public:
  PivotPIDCMD(PivotSub* pPivot, double setAngle, double* pTuretAngle, bool useLimits = false, bool useIsFinished = false, double holdtime = 0.5, double threshold = 0.1);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
 private:
  PivotSub* m_pPivot;
  double m_setAngle;
  double* m_pTurretAngle;
  bool m_useLimits;
  bool m_useIsFinished;
  double m_holdTime;
  double m_threshold;

  frc::PIDController m_pid{kPivotP, kPivotI, kPivotD};

  frc::Timer m_timer;
};
