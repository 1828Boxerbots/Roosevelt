// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/CommandXboxController.h>

#include "Constants.h"
#include "subsystems/ExampleSubsystem.h"

#include <frc/XboxController.h>
#include <frc/DigitalInput.h>

#include "commands/DriveCMD.h"
#include "commands/IntakeCMD.h"
#include "commands/ROCKYshoot.h"
#include "commands/BalanceCMD.h"
#include "commands/ForwardFeetAbsolute.h"

#include "subsystems/DriveSub.h"
#include "subsystems/IntakeSub.h"

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
  // Replace with CommandPS4Controller or CommandJoystick if needed
  frc2::CommandXboxController m_driverController{
      OperatorConstants::kDriverControllerPort};

  // The robot's subsystems are defined here...
  ExampleSubsystem m_subsystem;

  void ConfigureBindings();
  void Init();

  int GetDPDT();

  frc::XboxController m_XboxOne{OperatorConstants::kDriverControllerPort};
  frc::XboxController m_XboxTwo{1};

  frc::DigitalInput m_topDPDT{2};
  frc::DigitalInput m_bottomDPDT{3};

  DriveSub m_Drive;
  IntakeSub m_Intake;

  DriveCMD* m_pDriveCMD = nullptr;
  IntakeCMD* m_pIntakeOpen = nullptr;
  IntakeCMD* m_pIntakeClose = nullptr;
  BalanceCMD* m_pBalance = nullptr;
  ForwardFeetAbsolute* m_pForward = nullptr;
  ForwardFeetAbsolute* m_pBack = nullptr;

  ROCKYshoot* m_pshoot = nullptr;
};
