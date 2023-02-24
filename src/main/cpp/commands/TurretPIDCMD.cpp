// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TurretPIDCMD.h"

TurretPIDCMD::TurretPIDCMD(TurretSub* pTurret, double angle, double* pIMUAngle, bool isFieldOriented, double* pPivotAngle, bool useIsFinished, 
                double tolerance, double waitTime)
{
  m_pTurret = pTurret;
  m_angle = angle;
  m_pIMUAngle = pIMUAngle;
  m_isFieldOriented = isFieldOriented;
  m_pPivotAngle = pPivotAngle;
  m_useIsFinished = useIsFinished;
  m_waitTime = waitTime;

  m_pid.SetTolerance(tolerance);

  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pTurret);
}

// Called when the command is initially scheduled.
void TurretPIDCMD::Initialize()
{
  m_timer.Stop();
  m_timer.Reset();
  m_pid.Reset();

  if(m_isFieldOriented)
  {
    m_pid.SetSetpoint(m_angle-*m_pIMUAngle);
  }
  else
  {
    m_pid.SetSetpoint(m_angle);
  }
}

// Called repeatedly when this Command is scheduled to run
void TurretPIDCMD::Execute()
{
  if((*m_pPivotAngle >= kBatteryPivotAngleLimit) and (m_pTurret->GetTurretAngle() > kBatteryTurretAngleLimit) and ((m_angle >= 170) and (m_angle <= 190)))
  {
    m_pTurret->SetTurretMotor(0.0);
    // Flash red and yell at drivers
  }
  else
  {
    m_pTurret->SetTurretMotor(m_pid.Calculate(m_pTurret->GetTurretAngle()));
  }

  if(m_pid.AtSetpoint())
  {
    m_timer.Start();
  }
  else
  {
    m_timer.Stop();
    m_timer.Reset();
  }
}

// Called once the command ends or is interrupted.
void TurretPIDCMD::End(bool interrupted)
{
  m_pTurret->SetTurretMotor(0.0);
}

// Returns true when the command should end.
bool TurretPIDCMD::IsFinished()
{
  bool value = false;
  if(((double)m_timer.Get() >= m_waitTime) and m_useIsFinished)
  {
    value = true;
  }

  return value;
}
