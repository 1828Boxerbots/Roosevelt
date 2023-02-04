// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "commands/IntakeCMD.h"
#include "commands/ForwardFeetAbsolute.h"
#include "commands/BalanceCMD.h"

#include "subsystems/IntakeSub.h"
#include "subsystems/DriveSub.h"

namespace autos {
/**
 * Example static factory for an autonomous command.
 */
    frc2::CommandPtr ForwardLoadAuto(IntakeSub* pIntake, DriveSub* pDrive);

    frc2::CommandPtr BalanceAuto(IntakeSub* pIntake, DriveSub* pDrive);

}  // namespace autos