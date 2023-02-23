// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/CommandXboxController.h>

#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/Commands.h>

#include "Constants.h"

#include <frc/XboxController.h>
#include <frc/DigitalInput.h>
#include <frc/DigitalOutput.h>

#include "commands/DriveCMD.h"
#include "commands/IntakeCMD.h"
#include "commands/BalanceCMD.h"
#include "commands/ForwardFeetAbsolute.h"

#include "commands/PivotManCMD.h"
#include "commands/ElevatorManCMD.h"
#include "commands/TurretManCMD.h"

#include "commands/PivotPIDCMD.h"
#include "commands/ElevatorPIDCMD.h"
#include "commands/TurretPIDCMD.h"

#include "commands/ArmManCMD.h"
#include "commands/ArmPIDCMD.h"

#include "subsystems/DriveSub.h"
#include "subsystems/IntakeSub.h"
#include "subsystems/IntakeSub.h"
#include "subsystems/ElevatorSub.h"
#include "subsystems/TurretSub.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and trigger mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::CommandPtr GetAutonomousCommand();

 private:
  // COMMAND CONTROLLERS
  frc2::CommandXboxController m_driverController{kDriverControllerPort};
  frc2::CommandXboxController m_operatorController{kOperatorControllerPort};

  // CONTROLLERS
  frc::XboxController m_XboxOne{kDriverControllerPort};
  frc::XboxController m_XboxTwo{kOperatorControllerPort};

  void ConfigureBindings();
  void Init();

  int GetDPDT();

  // AUTO SWITCH
  //frc::DigitalInput m_topDPDT{2};
  //frc::DigitalInput m_bottomDPDT{3};

  // Pointer Variables
  double m_pivotAngle = 0.0;
  double m_turretAngle = 0.0;

  // SUBSYSTEMS
  DriveSub m_DriveSub;
  IntakeSub m_IntakeSub;
  PivotSub m_PivotSub{&m_pivotAngle};
  ElevatorSub m_ElevatorSub;
  TurretSub m_TurretSub{&m_turretAngle};

  // DRIVE CMD
  DriveCMD* m_pDriveCMD = nullptr;
  DriveCMD* m_pSlowDriveCMD = nullptr;

  // INTAKE CMD
  IntakeCMD* m_pIntake = nullptr;

  // AUTO CMDs
  BalanceCMD* m_pBalance = nullptr;
  ForwardFeetAbsolute* m_pForward = nullptr;
  ForwardFeetAbsolute* m_pBack = nullptr;

  // MANUAL CMDS
  PivotManCMD* m_pPivotManUp = nullptr;
  PivotManCMD* m_pPivotManDown = nullptr;
  ElevatorManCMD* m_pElevatorMan = nullptr;
  TurretManCMD* m_pTurretMan = nullptr;

  // OLD---ELEVATOR AND PIVOT PID
  PivotPIDCMD* m_pPivotPIDUp = nullptr;
  PivotPIDCMD* m_pPivotPIDTop = nullptr;
  PivotPIDCMD* m_pPivotPIDMid = nullptr;
  PivotPIDCMD* m_pPivotPIDHybrid = nullptr;
  PivotPIDCMD* m_pPivotPIDGround = nullptr;
  PivotPIDCMD* m_pPivotPIDSubstation = nullptr;
  ElevatorPIDCMD* m_pElevatorPIDUp = nullptr;
  ElevatorPIDCMD* m_pElevatorPIDTop = nullptr;
  ElevatorPIDCMD* m_pElevatorPIDMid = nullptr;
  ElevatorPIDCMD* m_pElevatorPIDHybrid = nullptr;
  ElevatorPIDCMD* m_pElevatorPIDGround = nullptr;
  ElevatorPIDCMD* m_pElevatorPIDSubstation = nullptr;

  // ARM CMD
  ArmManCMD* m_pArmManCMD = nullptr;

  ArmPIDCMD* m_pArmPIDUp = nullptr;
  ArmPIDCMD* m_pArmPIDHigh = nullptr;
  ArmPIDCMD* m_pArmPIDMid = nullptr;
  ArmPIDCMD* m_pArmPIDSubstation = nullptr;

  // TURRET PID
  TurretPIDCMD* m_pTurretPIDFront = nullptr;
  TurretPIDCMD* m_pTurretPIDLeft = nullptr;
  TurretPIDCMD* m_pTurretPIDRight = nullptr;
  TurretPIDCMD* m_pTurretPIDBack = nullptr;

};
