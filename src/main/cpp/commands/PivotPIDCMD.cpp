// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/PivotPIDCMD.h"

PivotPIDCMD::PivotPIDCMD(PivotSub* pPivot, double setAngle, double* pTurretAngle, bool useLimits, bool useIsFinished, double holdtime, double threshold)
{
  m_pPivot = pPivot;
  m_pTurretAngle = pTurretAngle;
  m_setAngle = setAngle;
  m_useLimits = useLimits;
  m_useIsFinished = useIsFinished;
  m_holdTime = holdtime;
  m_threshold = threshold;

  m_pid.SetSetpoint(m_setAngle);
  m_pid.SetTolerance(m_threshold);

  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pPivot);
}

// Called when the command is initially scheduled.
void PivotPIDCMD::Initialize()
{
  m_timer.Stop();
  m_timer.Reset();
  m_pid.Reset();
}

// Called repeatedly when this Command is scheduled to run
void PivotPIDCMD::Execute()
{
  if(m_useLimits)
  {
    if(((*m_pTurretAngle >= kBatteryTurretAngleLimit) or (*m_pTurretAngle <= -kBatteryTurretAngleLimit)) and
        (m_pPivot->GetPivotAngle() > kBatteryPivotAngleLimit) and ((m_setAngle >= kBatteryPivotAngleLimit)))
    {
      m_pid.SetSetpoint(m_pPivot->GetPivotAngle());
      // Flash red and yell at drivers
    }
  }
  
  m_pPivot->SetPivotMotor(m_pid.Calculate(m_pPivot->GetPivotAngle()));

  if(m_useIsFinished)
  {
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
}

// Called once the command ends or is interrupted.
void PivotPIDCMD::End(bool interrupted)
{
  m_pPivot->SetPivotMotor(0.0);
}

// Returns true when the command should end.
bool PivotPIDCMD::IsFinished()
{
  bool value = false;
  if(((double)m_timer.Get() >= m_holdTime))
  {
    value = true;
  }

  return value;
}
