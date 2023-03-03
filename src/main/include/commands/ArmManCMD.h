// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <frc/XboxController.h>

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
class ArmManCMD
    : public frc2::CommandHelper<frc2::CommandBase, ArmManCMD> {
 public:
  ArmManCMD(PivotSub* pPivot, ElevatorSub* pElevate, double* pTurretAngle, frc::XboxController* pXbox,
            double (frc::XboxController::*pPivotFunctionUp)()const,
            double (frc::XboxController::*pPivotFunctionDown)()const,
            double (frc::XboxController::*pElevatorFunction)()const,
            bool useLimits = false,
            double pivotScale = 1.0, double elevateScale = 1.0);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  PivotSub* m_pPivot;
  ElevatorSub* m_pElevate;
  double* m_pTurretAngle;
  frc::XboxController* m_pXbox;
  double (frc::XboxController::*m_pPivotFunctionUp)()const;
  double (frc::XboxController::*m_pPivotFunctionDown)()const;
  double (frc::XboxController::*m_pElevatorFunction)()const;
  bool m_useLimits;
  double m_pivotScale;
  double m_elevateScale;
};
