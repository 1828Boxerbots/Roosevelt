// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <frc/XboxController.h>

#include "subsystems/PivotSub.h"
#include "Util.h"
#include "Constants.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class PivotManCMD
    : public frc2::CommandHelper<frc2::CommandBase, PivotManCMD> {
 public:
  PivotManCMD(PivotSub* pPivot, frc::XboxController* pXbox, double (frc::XboxController::*input)() const, double* pTurretAngle, double scale);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  PivotSub* m_pPivot = nullptr;
  frc::XboxController* m_pXbox;
  double (frc::XboxController::*m_Input)() const;
  double* m_pTurretAngle;
  double m_scale;
};
