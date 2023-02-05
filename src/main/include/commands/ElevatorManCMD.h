// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/ElevatorSub.h"
#include <frc/XboxController.h>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ElevatorManCMD
    : public frc2::CommandHelper<frc2::CommandBase, ElevatorManCMD> {
 public:
  ElevatorManCMD(ElevatorSub* pElevator, frc::XboxController* pXbox, double (frc::XboxController::*pInput)() const, double scale = 1.0);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  ElevatorSub* m_pElevator;
  frc::XboxController* m_pXbox;
  double (frc::XboxController::*m_pInput)() const;
  double m_scale;
};
