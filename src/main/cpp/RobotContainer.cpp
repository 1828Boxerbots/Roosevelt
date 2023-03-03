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
  //m_pIntake = new IntakeCMD(&m_IntakeSub);
  m_pInIntake = new IntakeCMD(&m_IntakeSub, false, 0.5, true, true);
  m_pInIntake = new IntakeCMD(&m_IntakeSub, false, 0.5, true, false);
  
  // Arm and Turret Man (Pivot-Up, Pivot-Down, Elevator, Turret)
  // m_pPivotManUp = new PivotManCMD(&m_PivotSub, &m_XboxTwo, &frc::XboxController::GetLeftTriggerAxis, &m_turretAngle, 1.0);
  // m_pPivotManDown = new PivotManCMD(&m_PivotSub, &m_XboxTwo, &frc::XboxController::GetRightTriggerAxis, &m_turretAngle, -1.0);
  // m_pElevatorMan = new ElevatorManCMD(&m_ElevatorSub, &m_XboxTwo, &frc::XboxController::GetLeftY, 1.0);

  // m_pTurretMan = new TurretManCMD(&m_TurretSub, &m_XboxTwo, &frc::XboxController::GetRightX, &m_pivotAngle, true, kTurretScale);

  // Balance CMD
  //m_pBalance = new BalanceCMD(&m_DriveSub);

  // ARM CMDS
  m_pArmManCMD = new ArmManCMD{&m_PivotSub, &m_ElevatorSub, &m_turretAngle, &m_XboxTwo,
                &frc::XboxController::GetLeftTriggerAxis, &frc::XboxController::GetRightTriggerAxis, &frc::XboxController::GetLeftY, true, kPivotScale, kElevatorScale};
  // m_pArmPIDUp = new ArmPIDCMD{&m_PivotSub, &m_ElevatorSub, &m_turretAngle, kPivotDegUp, kElevatorInUp}; // Straight Up - In all the way
  // m_pArmPIDHigh = new ArmPIDCMD{&m_PivotSub, &m_ElevatorSub, &m_turretAngle, kPivotDegHigh, kElevatorInHigh}; // Goes for the high goal on the grid
  // m_pArmPIDMid = new ArmPIDCMD{&m_PivotSub, &m_ElevatorSub, &m_turretAngle, kPivotDegMid, kElevatorInMid}; // Goes for the mid goal on the grid
  // m_pArmPIDSubstation = new ArmPIDCMD{&m_PivotSub, &m_ElevatorSub, &m_turretAngle, kPivotDegSubstation, kElevatorInSubstation}; // Arm for the Double Substation -Closest you can get is 1/2 inch

  // Turret PID CMD
  // m_pTurretPIDFront = new TurretPIDCMD{&m_TurretSub, 0.0, &m_imuAngle, true, &m_pivotAngle};
  // m_pTurretPIDLeft = new TurretPIDCMD{&m_TurretSub, -90.0, &m_imuAngle, true, &m_pivotAngle};
  // m_pTurretPIDRight = new TurretPIDCMD{&m_TurretSub, 90.0, &m_imuAngle, true, &m_pivotAngle};
  // m_pTurretPIDBack = new TurretPIDCMD{&m_TurretSub, 180.0, &m_imuAngle, true, &m_pivotAngle};

  // Vision Align CMD
  //m_pVisionAlignCMD = new VisionAlignCMD{&m_VisionSub, &m_TurretSub, kVisionAlignSpeed};
  //m_pVisionPipelineCMD = new VisionPipelineCMD(&m_pipeline);

  // Configure the button bindings
  ConfigureBindings();
}

void RobotContainer::ConfigureBindings()
{
  // WhileTrue means the command will run until the button is let go
  // OnTrue means the command will continue to run even if the button is let go
  // Using OnTrue/OnFalse gives the same effect as WhileTrue/WhileFalse
    // While holding the button CMD in OnTrue/WhileTrue will run and when let go OnFalse/While will run 

  // DRIVER CONTROLLER--------
  //--Balance (Hold A)
  //m_driverController.A().WhileTrue(m_pBalance);

  //--Slow Drive Speed (Hold Left Trigger)
  m_driverController.LeftTrigger().WhileTrue(m_pSlowDriveCMD);

  //--Switch LEDs (Right Bumper) 
  //m_driverController.RightBumper().WhileTrue(m_pVisionPipelineCMD);

  // OPERATOR CONTROLLER--------
  //--Toggle Grabber (Left Bumper)
  m_operatorController.LeftBumper().WhileTrue(m_pInIntake);
  m_operatorController.RightBumper().WhileTrue(m_pOutIntake);

  //--Pivot Manuel Down (Left Trigger) Up (Right Trigger)
  m_operatorController.LeftTrigger().OnTrue(m_pArmManCMD);
  m_operatorController.RightTrigger().OnTrue(m_pArmManCMD);

  //--Elevator Manuel (Left Stick Y)
  m_operatorController.LeftStick().OnTrue(m_pArmManCMD);

  //--Turret Manuel (Right Stick X)
  //m_operatorController.RightStick().WhileTrue(m_pTurretMan);

  //--Ground Arm Position (Hold A)
  //m_operatorController.A().OnTrue(new ArmPIDCMD{&m_PivotSub, &m_ElevatorSub, &m_turretAngle, kPivotDegGround, m_ElevatorSub.GetElevatorLength()});
  //m_operatorController.A().OnFalse(m_pArmPIDUp);

  //--Substation Arm Position (Hold B)
  //m_operatorController.B().OnTrue(m_pArmPIDSubstation);
  //m_operatorController.B().OnFalse(m_pArmPIDUp);

  //--Mid Arm Position (Hold X)
  //m_operatorController.X().OnTrue(m_pArmPIDMid);
  //m_operatorController.X().OnFalse(m_pArmPIDUp);

  //--High Arm Position (Hold Y)
  //m_operatorController.Y().OnTrue(m_pArmPIDHigh);
  //m_operatorController.Y().OnFalse(m_pArmPIDUp);

  //--Vision (Hold Back)
  //m_operatorController.Back().WhileTrue(m_pVisionAlignCMD);

  //--Switch LEDs (Right Bumper) 
  //m_operatorController.RightBumper().WhileTrue(m_pVisionPipelineCMD);

  //--Field Oriented Turret PID Positions (D-Pad)
  //m_operatorController.POVUp(frc2::CommandScheduler::GetInstance().GetDefaultButtonLoop()).CastTo<frc2::Trigger>().OnTrue(m_pTurretPIDFront);
  //m_operatorController.POVDown(frc2::CommandScheduler::GetInstance().GetDefaultButtonLoop()).CastTo<frc2::Trigger>().OnTrue(m_pTurretPIDBack);
  //m_operatorController.POVLeft(frc2::CommandScheduler::GetInstance().GetDefaultButtonLoop()).CastTo<frc2::Trigger>().OnTrue(m_pTurretPIDLeft);
  //m_operatorController.POVRight(frc2::CommandScheduler::GetInstance().GetDefaultButtonLoop()).CastTo<frc2::Trigger>().OnTrue(m_pTurretPIDRight);
}

void RobotContainer::Init()
{
  m_DriveSub.Init();
  m_IntakeSub.Init();
  //m_ElevatorSub.Init();
  //m_PivotSub.Init();
  //m_TurretSub.Init();
  //m_VisionSub.Init();

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
