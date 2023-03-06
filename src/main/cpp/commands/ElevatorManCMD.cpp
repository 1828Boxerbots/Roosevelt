// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ElevatorManCMD.h"

ElevatorManCMD::ElevatorManCMD(ElevatorSub* pElevator, frc::XboxController* pXbox, double (frc::XboxController::*pInput)() const, double* pPivotAngle, double scale)
{
  m_pElevator = pElevator;
  m_pXbox = pXbox;
  m_pInput = pInput;
  m_pPivotAngle = pPivotAngle;
  m_scale = scale;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pElevator);
}

// Called when the command is initially scheduled.
void ElevatorManCMD::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ElevatorManCMD::Execute()
{
  // Get speed from input
  double extendSpeed = (m_pXbox->*m_pInput)() * m_scale;

  // Calculate the current height and distance of the arm using PivotAngle and Extention length
  double height = cos(*m_pPivotAngle * (M_PI/180.0)) * m_pElevator->GetElevatorLength();
  double distance = sin(*m_pPivotAngle * (M_PI/180.0)) * m_pElevator->GetElevatorLength();

  // If we are above any limits retract the extension
  if(height > kHeightLimit)
  {
    extendSpeed = m_scale;
  }
  if(distance > kDistanceLimit)
  {
    extendSpeed = m_scale;
  }

  m_pElevator->SetElevatorMotor(extendSpeed);
}

// Called once the command ends or is interrupted.
void ElevatorManCMD::End(bool interrupted)
{
  m_pElevator->SetElevatorMotor(0.0);
}

// Returns true when the command should end.
bool ElevatorManCMD::IsFinished() {
  return false;
}
