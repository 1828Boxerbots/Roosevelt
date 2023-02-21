// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <frc/controller/PIDController.h>

#include "subsystems/PivotSub.h"
#include "subsystems/ElevatorSub.h"

#include "Constants.h"
#include "Util.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ArmPIDCMD
    : public frc2::CommandHelper<frc2::CommandBase, ArmPIDCMD> {
 public:
  ArmPIDCMD(PivotSub* pPivot, ElevatorSub* pElevate, double* pTurretAngle, double pivotAngle, double elevateLength);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  PivotSub* m_pPivot;
  ElevatorSub* m_pElevate;
  double* m_pTurretAngle;
  double m_pivotAngle;
  double m_elevateLength;

  frc::PIDController m_pivotPID{kPivotP, kPivotI, kPivotD};
  frc::PIDController m_elevatePID{kElevatorP, kElevatorI, kElevatorD};
};
