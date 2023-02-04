// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/button/Trigger.h>

#include "commands/Autos.h"

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
  m_pDriveCMD = new DriveCMD(&m_Drive, &m_XboxOne, kDriveScale);
  m_pIntakeOpen = new IntakeCMD(&m_Intake, true);
  m_pPivotMan = new PivotManCMD(&m_Pivot, &m_XboxOne, &frc::XboxController::GetLeftTriggerAxis, 1.0);
  //m_pIntakeClose = new IntakeCMD(&m_Intake, false);
  m_pBalance = new BalanceCMD(&m_Drive);
  m_pForward = new ForwardFeetAbsolute(&m_Drive, 10.0, 0.1);
  m_pBack = new ForwardFeetAbsolute(&m_Drive, 0.0, 0.1);
  // Configure the button bindings
  ConfigureBindings();
  Init();
}

void RobotContainer::ConfigureBindings() {
  // Configure your trigger bindings here

  // Schedule `ExampleCommand` when `exampleCondition` changes to `true`
  // frc2::Trigger([this] {
  //   return m_subsystem.ExampleCondition();
  // }).OnTrue(ExampleCommand(&m_subsystem).ToPtr());

  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.
  //m_driverController.B().WhileTrue(m_subsystem.ExampleMethodCommand());

  // m_driverController.A().WhileTrue(m_Intake.IntakeOpen());
  // m_driverController.B().WhileTrue(m_Intake.IntakeClose());


  m_driverController.A().WhileTrue(m_pIntakeOpen);

  m_driverController.X().WhileTrue(m_pBalance);

  m_driverController.Y().WhileTrue(m_pForward);
}

void RobotContainer::Init()
{
  m_Drive.Init();
  m_Intake.Init();
  m_Drive.SetDefaultCommand(*m_pDriveCMD);
  //m_Intake.SetDefaultCommand(*m_pIntakeOpen);
}

int RobotContainer::GetDPDT()
{
  bool isTop = false;//!m_topDPDT.Get();
  bool isBottom = false;//!m_bottomDPDT.Get();

  int value;

  if(isTop)
  {
    value = 3;
  }
  else if(isBottom)
  {
    value = 1;
  }
  else
  {
    value = 2; // Middle Position
  }

  return value;
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  // int pos = GetDPDT();
  // if(pos == 1 or pos == 3)
  // {
  //   Util::Log("AUTO", "ForwardLoadAuto");
  //   Util::Log("DPDT Pos", pos);
  //   return autos::ForwardLoadAuto(&m_Intake, &m_Drive);
  // }
  // else if(pos == 2)
  // {
  //   Util::Log("AUTO", "BalanceAuto");
  //   return autos::BalanceAuto(&m_Intake, &m_Drive);
  // }
  return autos::ForwardLoadAuto(&m_Intake, &m_Drive);
}
