// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/button/Trigger.h>

#include "commands/Autos.h"

RobotContainer::RobotContainer()
{
  // Initialize all of your commands and subsystems here
  m_pDriveCMD = new DriveCMD(&m_DriveSub, &m_XboxOne, kDriveScale);
  m_pDriveCMD = new DriveCMD(&m_DriveSub, &m_XboxOne, kSlowDriveScale);

  m_pIntake = new IntakeCMD(&m_IntakeSub);
  
  m_pPivotManUp = new PivotManCMD(&m_PivotSub, &m_XboxTwo, &frc::XboxController::GetLeftTriggerAxis, &m_turretAngle, 1.0);
  m_pPivotManDown = new PivotManCMD(&m_PivotSub, &m_XboxTwo, &frc::XboxController::GetRightTriggerAxis, &m_turretAngle, -1.0);
  
  m_pElevatorMan = new ElevatorManCMD(&m_ElevatorSub, &m_XboxTwo, &frc::XboxController::GetLeftY, 1.0);
  m_pTurretMan = new TurretManCMD(&m_TurretSub, &m_XboxTwo, &frc::XboxController::GetRightX, &m_pivotAngle, 1.0);

  m_pBalance = new BalanceCMD(&m_DriveSub, &m_TurretSub);
  
  // PID COMMANDS
  m_pPivotPIDUp = new PivotPIDCMD{&m_PivotSub, 90.0, &m_turretAngle};
  m_pPivotPIDTop = new PivotPIDCMD{&m_PivotSub, 90.0, &m_turretAngle};
  m_pPivotPIDMid = new PivotPIDCMD{&m_PivotSub, 90.0, &m_turretAngle};
  m_pPivotPIDHybrid = new PivotPIDCMD{&m_PivotSub, 90.0, &m_turretAngle};
  m_pPivotPIDGround = new PivotPIDCMD{&m_PivotSub, 90.0, &m_turretAngle};
  m_pPivotPIDSubstation = new PivotPIDCMD{&m_PivotSub, 90.0, &m_turretAngle};

  m_pElevatorPIDUp = new ElevatorPIDCMD{&m_ElevatorSub, 0.0};
  m_pElevatorPIDTop = new ElevatorPIDCMD{&m_ElevatorSub, 0.0};
  m_pElevatorPIDMid = new ElevatorPIDCMD{&m_ElevatorSub, 0.0};
  m_pElevatorPIDHybrid = new ElevatorPIDCMD{&m_ElevatorSub, 0.0};
  m_pElevatorPIDGround = new ElevatorPIDCMD{&m_ElevatorSub, 0.0};
  m_pElevatorPIDSubstation = new ElevatorPIDCMD{&m_ElevatorSub, 0.0};

  m_pTurretPIDFront = new TurretPIDCMD{&m_TurretSub, 0.0, true, &m_pivotAngle};
  m_pTurretPIDLeft = new TurretPIDCMD{&m_TurretSub, -90.0, true, &m_pivotAngle};
  m_pTurretPIDRight = new TurretPIDCMD{&m_TurretSub, 90.0, true, &m_pivotAngle};
  m_pTurretPIDBack = new TurretPIDCMD{&m_TurretSub, 180.0, true, &m_pivotAngle};

  m_pForward = new ForwardFeetAbsolute(&m_DriveSub, &m_TurretSub, 10.0, 0.1);
  m_pBack = new ForwardFeetAbsolute(&m_DriveSub, &m_TurretSub, 0.0, 0.1);
  // Configure the button bindings
  ConfigureBindings();
  Init();
}

void RobotContainer::ConfigureBindings()
{
  // Driver Controller
  m_driverController.A().OnTrue(m_pBalance);
  m_driverController.LeftTrigger().OnTrue(m_pSlowDriveCMD);

  // Operator Controller
  m_operatorController.LeftBumper().WhileTrue(m_pIntake);
  m_operatorController.RightBumper().WhileTrue(m_pIntake);

  m_operatorController.LeftTrigger().WhileTrue(m_pPivotManUp);
  m_operatorController.RightTrigger().WhileTrue(m_pPivotManDown);

  m_operatorController.LeftStick().OnTrue(m_pElevatorMan);
  m_operatorController.RightStick().OnTrue(m_pTurretMan);

  m_operatorController.A().OnTrue(frc2::cmd::Parallel(*m_pPivotPIDGround, *m_pElevatorPIDGround));
  m_operatorController.A().OnFalse(frc2::cmd::Parallel(*m_pPivotManUp, *m_pElevatorPIDUp));

  m_operatorController.B().OnTrue(frc2::cmd::Parallel(*m_pPivotPIDSubstation, *m_pElevatorPIDSubstation));
  m_operatorController.B().OnFalse(frc2::cmd::Parallel(*m_pPivotManUp, *m_pElevatorPIDUp));

  m_operatorController.X().OnTrue(frc2::cmd::Parallel(*m_pPivotPIDMid, *m_pElevatorPIDMid));
  m_operatorController.X().OnFalse(frc2::cmd::Parallel(*m_pPivotManUp, *m_pElevatorPIDUp));

  m_operatorController.Y().OnTrue(frc2::cmd::Parallel(*m_pPivotPIDTop, *m_pElevatorPIDTop));
  m_operatorController.Y().OnFalse(frc2::cmd::Parallel(*m_pPivotManUp, *m_pElevatorPIDUp));

  m_operatorController.Start().OnTrue(frc2::cmd::Parallel(*m_pPivotPIDHybrid, *m_pElevatorPIDHybrid));
  m_operatorController.Start().OnFalse(frc2::cmd::Parallel(*m_pPivotManUp, *m_pElevatorPIDUp));

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
  m_DriveSub.SetDefaultCommand(*m_pDriveCMD);
  //m_IntakeSub.SetDefaultCommand(*m_pIntakeOpen);
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
  return autos::ForwardLoadAuto(&m_IntakeSub, &m_DriveSub);
}
