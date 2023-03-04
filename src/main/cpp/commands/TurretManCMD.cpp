// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TurretManCMD.h"

TurretManCMD::TurretManCMD(TurretSub* pTurret, frc::XboxController* pXbox, double (frc::XboxController::*pInput)() const, double* pPivotAngle, bool useLimits, double scale)
{
  m_pTurret = pTurret;
  m_pXbox = pXbox;
  m_pInput = pInput;
  m_pPivotAngle = pPivotAngle;
  m_useLimits = useLimits;
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
  // double turretAngle = m_pTurret->GetTurretAngle();

  // if(speed > 0.0 and turretAngle >= kTurretAngleLimit and m_useLimits)
  // {
  //   // Turn Turret to -135
  //   speed = 0.0;
  // }
  // else if(speed < 0 and turretAngle <= -kTurretAngleLimit and m_useLimits)
  // {
  //   // Turn Turret to 135
  //   speed = 0.0;
  // }

  // if(m_useLimits)
  // {
  //   if((speed > 0 and *m_pPivotAngle > kBatteryPivotAngleLimit and turretAngle > kBatteryTurretAngleLimit)
  //       or (speed < 0 and *m_pPivotAngle > kBatteryPivotAngleLimit and turretAngle < -kBatteryTurretAngleLimit))
  //   {
  //     speed = 0.0;
  //     // Flash Red and yell at drivers
  //   }
  //   else
  //   {
  //     if(turretAngle > kTurretAngleLimit and speed > 0.0)
  //     {
  //       speed = 0.0;
  //     }
  //     else if(turretAngle < -kTurretAngleLimit and speed < 0.0)
  //     {
  //       speed = 0.0;
  //     }
  //   }
  // }

  m_pTurret->SetTurretMotor(speed);
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
