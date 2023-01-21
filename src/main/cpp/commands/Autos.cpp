// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Autos.h"

#include <frc2/command/Commands.h>

#include "commands/ExampleCommand.h"

frc2::CommandPtr autos::ExampleAuto(ExampleSubsystem* subsystem) {
  return frc2::cmd::Sequence(subsystem->ExampleMethodCommand(),
                             ExampleCommand(subsystem).ToPtr());
}

frc2::CommandPtr autos::ForwardLoadAuto(IntakeSub* pIntake, DriveSub* pDrive)
{
  return frc2::cmd::Sequence(
    ROCKYshoot(pIntake, 1.0), IntakeTimerCMD(pIntake, true, 1),
    //frc2::cmd::Parallel( ROCKYshoot(pIntake, 1.0), IntakeCMD(pIntake, true)),
    ForwardFeetAbsolute(pDrive, -13.0, 0.5),
    IntakeTimerCMD(pIntake, true, 5),
    ForwardFeetAbsolute(pDrive, 0, 0.5),
    ROCKYshoot(pIntake, 1.0), IntakeTimerCMD(pIntake, true, 1)
    //frc2::cmd::Parallel( ROCKYshoot(pIntake, 1.0), IntakeCMD(pIntake, true))
  );
}

frc2::CommandPtr autos::BalanceAuto(IntakeSub* pIntake, DriveSub* pDrive)
{
  return frc2::cmd::Sequence(
    ROCKYshoot(pIntake, 1.0), IntakeTimerCMD(pIntake, true, 1),
    ForwardFeetAbsolute(pDrive, -13.0, 0.5),
    IntakeTimerCMD(pIntake, true, 5),
    ForwardFeetAbsolute(pDrive, 0, 0.5),
    ROCKYshoot(pIntake, 1.0), IntakeTimerCMD(pIntake, true, 1),
    ForwardFeetAbsolute(pDrive, -8.1, 0.5),
    ROCKYshoot(pIntake, 1.0), IntakeTimerCMD(pIntake, true, 1),
    BalanceCMD(pDrive, false, 2)
  );
}