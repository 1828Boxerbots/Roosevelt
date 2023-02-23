// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Autos.h"

#include <frc2/command/Commands.h>

frc2::CommandPtr autos::ForwardAuto(DriveSub* pDrive)
{
  return frc2::cmd::Sequence();
}

frc2::CommandPtr autos::ScoreForwardAuto(DriveSub* pDrive, PivotSub* pPivot, ElevatorSub* pElevator, IntakeSub* pIntake, VisionSub* pVision)
{
  return frc2::cmd::Sequence();
}

frc2::CommandPtr autos::BalanceAuto(DriveSub* pDrive)
{
  return frc2::cmd::Sequence();
}

frc2::CommandPtr autos::ScoreBalanceAuto(DriveSub* pDrive, PivotSub* pPivot, ElevatorSub* pElevator, IntakeSub* pIntake, VisionSub* pVision)
{
  return frc2::cmd::Sequence();
}


frc2::CommandPtr autos::DoubleScoreAuto(DriveSub* pDrive, PivotSub* pPivot, ElevatorSub* pElevator, IntakeSub* pIntake, VisionSub* pVision)
{
  return frc2::cmd::Sequence();
}

frc2::CommandPtr autos::DoubleScoreBalanceAuto(DriveSub* pDrive, PivotSub* pPivot, ElevatorSub* pElevator, IntakeSub* pIntake, VisionSub* pVision)
{
  return frc2::cmd::Sequence();
}