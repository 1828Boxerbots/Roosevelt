// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SequentialCommandGroup.h>


#include "subsystems/IntakeSub.h"
#include "subsystems/DriveSub.h"
#include "subsystems/ElevatorSub.h"
#include "subsystems/TurretSub.h"
#include "subsystems/PivotSub.h"
#include "subsystems/VisionSub.h"

#include "commands/IntakeCMD.h"
#include "commands/ForwardFeetAbsolute.h"
#include "commands/ForwardTimerCMD.h"
#include "commands/BalanceCMD.h"
#include "commands/TurretPIDCMD.h"
#include "commands/ArmPIDCMD.h"
#include "commands/PivotPIDCMD.h"
#include "commands/ElevatorPIDCMD.h"
#include "commands/VisionAlignCMD.h"
#include "commands/VisionPipelineCMD.h"

#include "Constants.h"

namespace autos {
/**
 * Example static factory for an autonomous command.
 */
    frc2::CommandPtr ForwardAuto(DriveSub* pDrive);

   frc2::CommandPtr BalanceMobilityTimerAuto(DriveSub* pDrive);

    frc2::CommandPtr ScoreForwardAuto(DriveSub* pDrive, TurretSub* pTurret, PivotSub* pPivot, ElevatorSub* pElevator, IntakeSub* pIntake, VisionSub* pVision, 
                                        double* pPivotAngle, double* pTurretAngle, double* pIMUAngle, VisionSub::Pipelines* pPipeline);

    frc2::CommandPtr BalanceAuto(DriveSub* pDrive);

    frc2::CommandPtr BalanceMobilityAuto(DriveSub* pDrive);

    frc2::CommandPtr ScoreBalanceAuto(DriveSub* pDrive, TurretSub* pTurret, PivotSub* pPivot, ElevatorSub* pElevator, IntakeSub* pIntake, VisionSub* pVision,
                                        double* pPivotAngle, double* pTurretAngle,double* pIMUAngle, VisionSub::Pipelines* pPipeline);
    
    //Ideal Autos
    frc2::CommandPtr DoubleScoreAuto(DriveSub* pDrive, TurretSub* pTurret, PivotSub* pPivot, ElevatorSub* pElevator, IntakeSub* pIntake, VisionSub* pVision,
                                        double* pPivotAngle, double* pTurretAngle, double* pIMUAngle, VisionSub::Pipelines* pPipeline);
    frc2::CommandPtr DoubleScoreChargingStationAuto(DriveSub* pDrive, TurretSub* pTurret, PivotSub* pPivot, ElevatorSub* pElevator, IntakeSub* pIntake, VisionSub* pVision,
                                                    double* pPivotAngle, double* pTurretAngle, double* pIMUAngle, VisionSub::Pipelines* pPipeline);
    frc2::CommandPtr DoubleScoreBalanceAuto(DriveSub* pDrive, TurretSub* pTurret, PivotSub* pPivot, ElevatorSub* pElevator, IntakeSub* pIntake, VisionSub* pVision,
                                                double* pPivotAngle, double* pTurretAngle, double* pIMUAngle, VisionSub::Pipelines* pPipeline);

}  // namespace autos