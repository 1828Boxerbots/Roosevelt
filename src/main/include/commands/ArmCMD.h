// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <frc/Timer.h>
#include <frc/controller/PIDController.h>

#include "Util.h"
#include "Constants.h"
#include "subsystems/ElevatorSub.h"
#include "subsystems/PivotSub.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ArmCMD
    : public frc2::CommandHelper<frc2::CommandBase, ArmCMD> {
 public:
  ArmCMD(PivotSub* pPivot, ElevatorSub* pElevator, double height, double distance, double* pTurretAngle,
          bool useIsFinished = false, double holdtime = 0.5, double thresholdPivot = 0.1, double thresholdElevator = 0.1);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  PivotSub* m_pPivot;
  ElevatorSub* m_pElevator;
  double m_height;
  double m_distance;
  double* m_pTurretAngle;
  bool m_useIsFinished;
  double m_holdTime;
  double m_thresholdPivot;
  double m_thresholdElevator;

  double m_pivotAngle;
  double m_elevatorLength;

  frc::PIDController m_pivotPID{kPivotP, kPivotI, kPivotD};
  frc::PIDController m_elevatorPID{kElevatorP, kElevatorI, kElevatorD};

  frc::Timer m_timer;
};
