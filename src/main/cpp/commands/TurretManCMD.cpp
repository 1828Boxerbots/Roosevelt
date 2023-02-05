// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TurretManCMD.h"

TurretManCMD::TurretManCMD(TurretSub* pTurret, frc::XboxController* pXbox, double (frc::XboxController::*pInput)() const, double scale)
{
  m_pTurret = pTurret;
  m_pXbox = pXbox;
  m_pInput = pInput;
  m_scale = scale;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pTurret);
}

// Called when the command is initially scheduled.
void TurretManCMD::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TurretManCMD::Execute()
{
  m_pTurret->SetTurretMotor((m_pXbox->*m_pInput)() * m_scale);
}

// Called once the command ends or is interrupted.
void TurretManCMD::End(bool interrupted)
{
  m_pTurret->SetTurretMotor(0.0);
}

// Returns true when the command should end.
bool TurretManCMD::IsFinished() {
  return false;
}
