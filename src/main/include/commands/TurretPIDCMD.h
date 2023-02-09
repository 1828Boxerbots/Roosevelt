// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <frc/controller/PIDController.h>
#include <frc/Timer.h>
#include "Util.h"
#include "Constants.h"

#include "subsystems/TurretSub.h"
#include "subsystems/DriveSub.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class TurretPIDCMD
    : public frc2::CommandHelper<frc2::CommandBase, TurretPIDCMD> {
 public:
  TurretPIDCMD(TurretSub* pTurret, double angle, bool isFieldOriented, double* pPivotAngle, bool useIsFinished = false, 
                double tolerance = 0.5, double waitTime = 0.5);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
 private:
  TurretSub* m_pTurret;
  bool m_isFieldOriented;
  double* m_pPivotAngle;
  bool m_useIsFinished;
  double m_waitTime;

  frc::Timer m_timer;
  frc::PIDController m_pid {kTurretP, kTurretI, kTurretD};
};
