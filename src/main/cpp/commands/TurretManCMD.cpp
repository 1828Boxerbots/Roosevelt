// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TurretManCMD.h"

TurretManCMD::TurretManCMD(TurretSub* pTurret, frc::XboxController* pXbox, double (frc::XboxController::*pInput)() const, double* pPivotAngle, double scale)
{
  m_pTurret = pTurret;
  m_pXbox = pXbox;
  m_pInput = pInput;
  m_pPivotAngle = pPivotAngle;
  m_scale = scale;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pTurret);
}

// Called when the command is initially scheduled.
void TurretManCMD::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TurretManCMD::Execute()
{
  double speed = (m_pXbox->*m_pInput)() * m_scale;

  if(speed > 0 and m_pTurret->GetTurretAngle() >= kTurretAngleLimit)
  {
    // Turn Turret to -135
    m_pTurret->SetTurretMotor(0.0);
  }
  else if(speed < 0 and m_pTurret->GetTurretAngle() <= -kTurretAngleLimit)
  {
    // Turn Turret to 135
    m_pTurret->SetTurretMotor(0.0);
  }

  if((speed > 0 and *m_pPivotAngle > kBatteryPivotAngleLimit and m_pTurret->GetTurretAngle() > kBatteryTurretAngleLimit)
      or (speed < 0 and *m_pPivotAngle > kBatteryPivotAngleLimit and m_pTurret->GetTurretAngle() < -kBatteryTurretAngleLimit))
  {
    m_pTurret->SetTurretMotor(0.0);
    // Flash Red and yell at drivers
  }
  else
  {
    m_pTurret->SetTurretMotor(speed);
  }
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
