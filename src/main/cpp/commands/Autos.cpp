// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Autos.h"

#include <frc2/command/Commands.h>

frc2::CommandPtr autos::ForwardAuto(DriveSub* pDrive)
{
  return frc2::cmd::Sequence(ForwardFeetAbsolute(pDrive, kForwardDistFt, kForwardTolerance));
}

frc2::CommandPtr autos::ScoreForwardAuto(DriveSub* pDrive, TurretSub* pTurret, PivotSub* pPivot, ElevatorSub* pElevator, IntakeSub* pIntake, VisionSub* pVision,
                                          double* pPivotAngle, double* pTurretAngle, double* pIMUAngle)
{
  return frc2::cmd::Sequence(TurretPIDCMD(pTurret, kTurretBack, pIMUAngle, true, pPivotAngle, true), // Move Turret Toward Grid
                            /*Vision,*/ // Allign to Reflective Tape
                            ArmPIDCMD(pPivot, pElevator, pTurretAngle, kPivotDegHigh, kElevatorInHigh, true, kArmHoldTime, kArmTolerance), // Move Arm to High Pos
                            IntakeCMD(pIntake, true), // Open Intake
                            ArmPIDCMD(pPivot, pElevator, pTurretAngle, kPivotDegUp, kElevatorInUp, true, kArmHoldTime, kArmTolerance), // Move Arm to Up Pos
                            frc2::cmd::Parallel( // Turn Turret to front and move out
                              TurretPIDCMD(pTurret, kTurretFront, pIMUAngle, false, pPivotAngle, true), // Turn Turret to front
                              ForwardFeetAbsolute(pDrive, kForwardDistFt, kArmTolerance))); // Move robot out
}

frc2::CommandPtr autos::BalanceAuto(DriveSub* pDrive)
{
  return frc2::cmd::Sequence(ForwardFeetAbsolute(pDrive, kBalanceDistFt, kForwardTolerance),
                            BalanceCMD(pDrive, true));
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
  return frc2::cmd::Sequence(ScoreForwardAuto(pDrive, pTurret, pPivot, pElevator, pIntake, pVision, pPivotAngle, pTurretAngle, pIMUAngle), //Score first piece and go 15 ft out
                            /* Set Vision Pipeline to CONE and allign,*/ //Allign Turret to Cone
                            PivotPIDCMD(pPivot, kPivotDegGround, pTurretAngle, true, kPivotHoldTime, kPivotTolerance), //Move the arm down 
                            ElevatorPIDCMD(pElevator, kElevatorDistToConeInch, true, kElevatorHoldTime, kElevatorTolerance), //Extend the elevator to the cone
                            IntakeCMD(pIntake, true), // Grab Cone
                            frc2::cmd::Parallel( //Move arm up and move turret to face Grid in Parallel
                              ArmPIDCMD(pPivot, pElevator, pTurretAngle, kPivotDegUp, kElevatorInUp, true, kArmHoldTime, kArmTolerance), //Arm up
                              TurretPIDCMD(pTurret, kTurretBack, pIMUAngle, true, pPivotAngle, true), //Turret facing grid
                            ForwardFeetAbsolute(pDrive, kGridDistFt, kForwardTolerance)), // Move to grid
                            /*Allign to Tape*/ // Align Turret to Reflective tape
                            ArmPIDCMD(pPivot, pElevator, pTurretAngle, kPivotDegHigh, kElevatorInHigh, true, kArmHoldTime, kArmTolerance), // Move arm to high pos
                            IntakeCMD(pIntake, true), // Drop cone
                            ArmPIDCMD(pPivot, pElevator, pTurretAngle, kPivotDegUp, kElevatorInUp, true, kArmHoldTime, kArmTolerance), // Bring Arm Up
                            frc2::cmd::Parallel( // Move turret to front and move forward in parallel
                              TurretPIDCMD(pTurret, kTurretFront, pIMUAngle, false, pPivotAngle, true), // Move turret to front
                              ForwardFeetAbsolute(pDrive, kForwardDistFt, kForwardTolerance))); // Move forward
}

frc2::CommandPtr autos::DoubleScoreChargingStationAuto(DriveSub* pDrive, TurretSub* pTurret, PivotSub* pPivot, ElevatorSub* pElevator, IntakeSub* pIntake, VisionSub* pVision,
                                                    double* pPivotAngle, double* pTurretAngle, double* pIMUAngle)
{
  return frc2::cmd::Sequence(ScoreForwardAuto(pDrive, pTurret, pPivot, pElevator, pIntake, pVision, pPivotAngle, pTurretAngle, pIMUAngle), //Score first piece and go 15 ft out
                            TurretPIDCMD(pTurret, kTurretTowardsObj, pIMUAngle, true, pPivotAngle, true), //Face Turret towards Cone to get close to CONE for allignment
                            /* Set Vision Pipeline to CONE and allign,*/ //Allign Turret to Cone
                            PivotPIDCMD(pPivot, kPivotDegGround, pTurretAngle, true, kPivotHoldTime, kPivotTolerance), //Move the arm down 
                            ElevatorPIDCMD(pElevator, kElevatorLengthToMidObj, true, kElevatorHoldTime, kElevatorTolerance), //Extend the elevator to the cone
                            IntakeCMD(pIntake, true), // Grab Cone
                            frc2::cmd::Parallel( //Move arm up and move turret to face Grid in Parallel
                              ArmPIDCMD(pPivot, pElevator, pTurretAngle, kPivotDegUp, kElevatorInUp, true, kArmHoldTime, kArmTolerance), //Arm up
                              TurretPIDCMD(pTurret, kTurretFront, pIMUAngle, true, pPivotAngle, true), //Turret facing grid
                            ForwardFeetAbsolute(pDrive, kGridDistFt, kForwardTolerance)), // Move to grid
                            /*Allign to Tape*/ // Align Turret to Reflective tape
                            ArmPIDCMD(pPivot, pElevator, pTurretAngle, kPivotDegHigh, kElevatorInHigh, true, kArmHoldTime, kArmTolerance), // Move arm to high pos
                            IntakeCMD(pIntake, true), // Drop cone
                            ArmPIDCMD(pPivot, pElevator, pTurretAngle, kPivotDegUp, kElevatorInUp, true, kArmHoldTime, kArmTolerance), // Bring Arm Up
                            frc2::cmd::Parallel( // Move turret to front and move forward in parallel
                              TurretPIDCMD(pTurret, kTurretFront, pIMUAngle, false, pPivotAngle, true), // Move turret to front
                              ForwardFeetAbsolute(pDrive, kForwardDistFt, kForwardTolerance))); // Move forward
}

frc2::CommandPtr autos::DoubleScoreBalanceAuto(DriveSub* pDrive, TurretSub* pTurret, PivotSub* pPivot, ElevatorSub* pElevator, IntakeSub* pIntake, VisionSub* pVision, 
                                                double* pPivotAngle, double* pTurretAngle, double* pIMUAngle)
{
  return frc2::cmd::Sequence(ScoreForwardAuto(pDrive, pTurret, pPivot, pElevator, pIntake, pVision, pPivotAngle, pTurretAngle, pIMUAngle), //Score first piece and go 15 ft out
                            TurretPIDCMD(pTurret, kTurretTowardsObj, pIMUAngle, true, pPivotAngle, true), //Face Turret towards Cone to get close to CONE for allignment
                            /* Set Vision Pipeline to CONE and allign,*/ //Allign Turret to Cone
                            PivotPIDCMD(pPivot, kPivotDegGround, pTurretAngle, true, kPivotHoldTime, kPivotTolerance), //Move the arm down 
                            ElevatorPIDCMD(pElevator, kElevatorLengthToMidObj, true, kElevatorHoldTime, kElevatorTolerance), //Extend the elevator to the cone
                            IntakeCMD(pIntake, true), // Grab Cone
                            frc2::cmd::Parallel( //Move arm up and move turret to face Grid in Parallel
                              ArmPIDCMD(pPivot, pElevator, pTurretAngle, kPivotDegUp, kElevatorInUp, true, kArmHoldTime, kArmTolerance), //Arm up
                              TurretPIDCMD(pTurret, kTurretBack, pIMUAngle, true, pPivotAngle, true), //Turret facing grid
                            ForwardFeetAbsolute(pDrive, kGridDistFt, kForwardTolerance)), // Move to grid
                            /*Allign to Tape*/ // Align Turret to Reflective tape
                            ArmPIDCMD(pPivot, pElevator, pTurretAngle, kPivotDegHigh, kElevatorInHigh, true, kArmHoldTime, kArmTolerance), // Move arm to high pos
                            IntakeCMD(pIntake, true), // Drop cone
                            ArmPIDCMD(pPivot, pElevator, pTurretAngle, kPivotDegUp, kElevatorInUp, true, kArmHoldTime, kArmTolerance), // Bring Arm Up
                            frc2::cmd::Parallel( // Move turret to front and balance
                              TurretPIDCMD(pTurret, 0.0, pIMUAngle, false, pPivotAngle, true), // Move turret to front
                              BalanceAuto(pDrive))); // Move to Correct location and balance
}