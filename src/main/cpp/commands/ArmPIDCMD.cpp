// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ArmPIDCMD.h"

ArmPIDCMD::ArmPIDCMD(PivotSub* pPivot, ElevatorSub* pElevate, double* pTurretAngle, double pivotAngle, double elevateLength,
                      bool useIsFinished, double holdtime, double threshold)
{
  m_pPivot = pPivot;
  m_pElevate = pElevate;
  m_pTurretAngle = pTurretAngle;
  m_pivotAngle = pivotAngle;
  m_elevateLength = elevateLength;
  m_useIsFinished = useIsFinished;
  m_holdTime = holdtime;
  m_threshold = threshold;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pPivot);
  AddRequirements(m_pElevate);
}

// Called when the command is initially scheduled.
void ArmPIDCMD::Initialize()
{
  m_timer.Stop();
  m_timer.Reset();

  m_elevatePID.Reset();
  m_pivotPID.Reset();

  if(m_elevateLength< 0.0)
  {
    m_elevatePID.SetSetpoint(m_pElevate->GetElevatorLength());
  }
  else
  {
    m_elevatePID.SetSetpoint(m_elevateLength);
  }
  m_pivotPID.SetSetpoint(m_pivotAngle);

  m_pivotPID.SetTolerance(m_threshold);
  m_elevatePID.SetTolerance(m_threshold);
}

// Called repeatedly when this Command is scheduled to run
void ArmPIDCMD::Execute()
{
  double height = cos(m_pPivot->GetPivotAngle() * (M_PI/180.0)) * m_pElevate->GetElevatorLength();
  double distance = sin(m_pPivot->GetPivotAngle() * (M_PI/180.0)) * m_pElevate->GetElevatorLength();

  if(height > 26.0)
  {
    m_elevatePID.SetSetpoint(26.0/cos(m_pPivot->GetPivotAngle()*(M_PI/180.0)));
  }
  
  if(distance > 19.125)
  {
    m_elevatePID.SetSetpoint(19.25/sin(m_pPivot->GetPivotAngle()*(M_PI/180.0)));
  }

  double elevatorSpeed = m_elevatePID.Calculate(m_pElevate->GetElevatorLength());
  double pivotSpeed = m_pivotPID.Calculate(m_pPivot->GetPivotAngle());
 
  // Do Turret stuff
  if(((*m_pTurretAngle >= kBatteryTurretAngleLimit) or (*m_pTurretAngle <= -kBatteryTurretAngleLimit)) and
      (m_pPivot->GetPivotAngle() > kBatteryPivotAngleLimit) and ((m_pivotAngle >= 80.0)))
  {
    m_pivotPID.SetSetpoint(m_pPivot->GetPivotAngle());
    // Flash red and yell at drivers
  }

  m_pElevate->SetElevatorMotor(elevatorSpeed);
  m_pPivot->SetPivotMotor(pivotSpeed);

  if(m_elevatePID.AtSetpoint() and m_pivotPID.AtSetpoint())
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
void ArmPIDCMD::End(bool interrupted)
{
  m_pElevate->SetElevatorMotor(0.0);
  m_pPivot->SetPivotMotor(0.0);
}

// Returns true when the command should end.
bool ArmPIDCMD::IsFinished()
{
  bool returnValue;
  if((double)m_timer.Get() >= m_holdTime and m_useIsFinished)
  {
    returnValue = true;
  }
  else
  {
    returnValue = false;
  }
  return returnValue;
}
