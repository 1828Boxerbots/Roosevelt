// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/button/Trigger.h>

#include "commands/Autos.h"

RobotContainer::RobotContainer()
{
  // Initialize all of your commands and subsystems here
  // Drive CMDS -Normal -Slow
  m_pDriveCMD = new DriveCMD(&m_DriveSub, &m_XboxOne, kDriveScale);
  m_pSlowDriveCMD = new DriveCMD(&m_DriveSub, &m_XboxOne, kSlowDriveScale);

  // Intake CMD
  m_pIntake = new IntakeCMD(&m_IntakeSub);
  
  // Arm and Turret Man (Pivot-Up, Pivot-Down, Elevator, Turret)
  m_pPivotManUp = new PivotManCMD(&m_PivotSub, &m_XboxTwo, &frc::XboxController::GetLeftTriggerAxis, &m_turretAngle, 1.0);
  m_pPivotManDown = new PivotManCMD(&m_PivotSub, &m_XboxTwo, &frc::XboxController::GetRightTriggerAxis, &m_turretAngle, -1.0);
  m_pElevatorMan = new ElevatorManCMD(&m_ElevatorSub, &m_XboxTwo, &frc::XboxController::GetLeftY, 1.0);
  m_pTurretMan = new TurretManCMD(&m_TurretSub, &m_XboxTwo, &frc::XboxController::GetRightX, &m_pivotAngle, 1.0);

  // Balance CMD
  m_pBalance = new BalanceCMD(&m_DriveSub, &m_TurretSub);

  // ARM CMDS
  m_pArmManCMD = new ArmManCMD{&m_PivotSub, &m_ElevatorSub, &m_turretAngle, &m_XboxTwo,
                &frc::XboxController::GetLeftTriggerAxis, &frc::XboxController::GetRightTriggerAxis, &frc::XboxController::GetLeftY};
  m_pArmPIDUp = new ArmPIDCMD{&m_PivotSub, &m_ElevatorSub, &m_turretAngle, 0.0, 0.0}; // Straight Up - In all the way
  m_pArmPIDHigh = new ArmPIDCMD{&m_PivotSub, &m_ElevatorSub, &m_turretAngle, kPivotDegHigh, kElevatorInHigh}; // Goes for the high goal on the grid
  m_pArmPIDMid = new ArmPIDCMD{&m_PivotSub, &m_ElevatorSub, &m_turretAngle, kPivotDegMid, kElevatorInMid}; // Goes for the mid goal on the grid
  m_pArmPIDSubstation = new ArmPIDCMD{&m_PivotSub, &m_ElevatorSub, &m_turretAngle, kPivotDegSubstation, kElevatorInSubstation}; // Arm for the Double Substation -Closest you can get is 1/2 inch

  // Turret PID CMD
  m_pTurretPIDFront = new TurretPIDCMD{&m_TurretSub, 0.0, true, &m_pivotAngle};
  m_pTurretPIDLeft = new TurretPIDCMD{&m_TurretSub, -90.0, true, &m_pivotAngle};
  m_pTurretPIDRight = new TurretPIDCMD{&m_TurretSub, 90.0, true, &m_pivotAngle};
  m_pTurretPIDBack = new TurretPIDCMD{&m_TurretSub, 180.0, true, &m_pivotAngle};

  // Configure the button bindings
  ConfigureBindings();
  Init();
}

void RobotContainer::ConfigureBindings()
{
  // DRIVER CONTROLLER--------
  //--Balance (Hold A)
  m_driverController.A().OnTrue(m_pBalance);

  //--Slow Drive Speed (Hold Left Trigger)
  m_driverController.LeftTrigger().OnTrue(m_pSlowDriveCMD);

  //--Switch LEDs (Right Bumper) 

  // OPERATOR CONTROLLER--------
  //--Toggle Grabber (Left Bumper)
  m_operatorController.LeftBumper().WhileTrue(m_pIntake);

  //--Pivot Manuel Down (Left Trigger) Up (Right Trigger)
  m_operatorController.LeftTrigger().WhileTrue(m_pPivotManUp);
  m_operatorController.RightTrigger().WhileTrue(m_pPivotManDown);

  //--Elevator Manuel (Left Stick Y)
  m_operatorController.LeftStick().OnTrue(m_pElevatorMan);

  //--Turret Manuel (Right Stick X)
  m_operatorController.RightStick().OnTrue(m_pTurretMan);

  //--Ground Arm Position (Hold A)
  m_operatorController.A().OnTrue(new ArmPIDCMD{&m_PivotSub, &m_ElevatorSub, &m_turretAngle, 90.0, m_ElevatorSub.GetElevatorLength()});
  m_operatorController.A().OnFalse(m_pArmPIDUp);

  //--Substation Arm Position (Hold B)
  m_operatorController.B().OnTrue(m_pArmPIDSubstation);
  m_operatorController.B().OnFalse(m_pArmPIDUp);

  //--Mid Arm Position (Hold X)
  m_operatorController.X().OnTrue(m_pArmPIDMid);
  m_operatorController.X().OnFalse(m_pArmPIDUp);

  //--High Arm Position (Hold Y)
  m_operatorController.Y().OnTrue(m_pArmPIDHigh);
  m_operatorController.Y().OnFalse(m_pArmPIDUp);

  //--Vision (Hold Back)
  //--Switch LEDs (Right Bumper) 

  //--Field Oriented Turret PID Positions (D-Pad)
  m_operatorController.POVUp(frc2::CommandScheduler::GetInstance().GetDefaultButtonLoop()).CastTo<frc2::Trigger>().OnTrue(m_pTurretPIDFront);
  m_operatorController.POVDown(frc2::CommandScheduler::GetInstance().GetDefaultButtonLoop()).CastTo<frc2::Trigger>().OnTrue(m_pTurretPIDBack);
  m_operatorController.POVLeft(frc2::CommandScheduler::GetInstance().GetDefaultButtonLoop()).CastTo<frc2::Trigger>().OnTrue(m_pTurretPIDLeft);
  m_operatorController.POVRight(frc2::CommandScheduler::GetInstance().GetDefaultButtonLoop()).CastTo<frc2::Trigger>().OnTrue(m_pTurretPIDRight);
}

void RobotContainer::Init()
{
  m_DriveSub.Init();
  m_IntakeSub.Init();
  m_ElevatorSub.Init();
  m_PivotSub.Init();
  m_TurretSub.Init();

  // Drive Default CMD
  m_DriveSub.SetDefaultCommand(*m_pDriveCMD);
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
  //   return autos::ForwardLoadAuto(&m_IntakeSub, &m_DriveSub);
  // }
  // else if(pos == 2)
  // {
  //   Util::Log("AUTO", "BalanceAuto");
  //   return autos::BalanceAuto(&m_IntakeSub, &m_DriveSub);
  // }
  return autos::ForwardAuto(&m_DriveSub);
}
