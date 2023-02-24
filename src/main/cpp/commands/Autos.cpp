// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Autos.h"

#include <frc2/command/Commands.h>

frc2::CommandPtr autos::ForwardAuto(DriveSub* pDrive)
{
  return frc2::cmd::Sequence(ForwardFeetAbsolute(pDrive, 15.0, 0.5));
}

frc2::CommandPtr autos::ScoreForwardAuto(DriveSub* pDrive, TurretSub* pTurret, PivotSub* pPivot, ElevatorSub* pElevator, IntakeSub* pIntake, VisionSub* pVision,
                                          double* pPivotAngle, double* pTurretAngle, double* pIMUAngle)
{
  return frc2::cmd::Sequence(TurretPIDCMD(pTurret, 180, pIMUAngle, true, pPivotAngle, true), /*Vision,*/ 
                            ArmPIDCMD(pPivot, pElevator, pTurretAngle, kPivotDegHigh, kElevatorInHigh, true, 0.5, 1),
                            IntakeCMD(pIntake, true), ArmPIDCMD(pPivot, pElevator, pTurretAngle, 0.0, 0.0, true, 0.5, 1),
                            frc2::cmd::Parallel(TurretPIDCMD(pTurret, 0.0, pIMUAngle, true, pPivotAngle, true), ForwardFeetAbsolute(pDrive, 15.0, 1.0)));
}

frc2::CommandPtr autos::BalanceAuto(DriveSub* pDrive)
{
  return frc2::cmd::Sequence(ForwardFeetAbsolute(pDrive, 8.0, 0.5), BalanceCMD(pDrive, true));
}

frc2::CommandPtr autos::BalanceMobilityAuto(DriveSub* pDrive)
{
  return frc2::cmd::Sequence(ForwardAuto(pDrive), BalanceAuto(pDrive));
}

frc2::CommandPtr autos::ScoreBalanceAuto(DriveSub* pDrive, TurretSub* pTurret, PivotSub* pPivot, ElevatorSub* pElevator, IntakeSub* pIntake, VisionSub* pVision,
                                          double* pPivotAngle, double* pTurretAngle, double* pIMUAngle)
{
  return frc2::cmd::Sequence(ScoreForwardAuto(pDrive, pTurret, pPivot, pElevator, pIntake, pVision, pPivotAngle, pTurretAngle, pIMUAngle),
                            BalanceAuto(pDrive));
}

// Double scores

frc2::CommandPtr autos::DoubleScoreAuto(DriveSub* pDrive, TurretSub* pTurret, PivotSub* pPivot, ElevatorSub* pElevator, IntakeSub* pIntake, VisionSub* pVision,
                                        double* pPivotAngle, double* pTurretAngle, double* pIMUAngle)
{
  return frc2::cmd::Sequence();
}

frc2::CommandPtr autos::DoubleScoreBalanceAuto(DriveSub* pDrive, TurretSub* pTurret, PivotSub* pPivot, ElevatorSub* pElevator, IntakeSub* pIntake, VisionSub* pVision, 
                                                double* pPivotAngle, double* pTurretAngle, double* pIMUAngle)
{
  return frc2::cmd::Sequence();
}