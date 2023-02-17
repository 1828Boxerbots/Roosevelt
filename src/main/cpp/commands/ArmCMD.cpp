// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ArmCMD.h"

ArmCMD::ArmCMD(PivotSub* pPivot, ElevatorSub* pElevator, double height, double distance, double* pTurretAngle,
              bool useIsFinished, double holdtime, double thresholdPivot, double thresholdElevator)
{
  m_pPivot = pPivot;
  m_pElevator = pElevator;
  m_height = height;
  m_distance = distance;
  m_pTurretAngle = pTurretAngle;
  m_useIsFinished = useIsFinished;
  m_holdTime = holdtime;
  m_thresholdPivot = thresholdPivot;
  m_thresholdElevator = thresholdElevator;

  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pPivot);
  AddRequirements(m_pElevator);
}

// Called when the command is initially scheduled.
void ArmCMD::Initialize()
{
  m_timer.Stop();
  m_timer.Reset();

  m_pivotPID.Reset();
  m_elevatorPID.Reset();

  m_pivotAngle = atan(m_distance/m_height) * (M_PI / 180.0);
  m_elevatorLength = sqrt(pow(m_distance, 2) + pow(m_height, 2));

  m_pivotPID.SetSetpoint(m_pivotAngle);
  m_elevatorPID.SetSetpoint(m_elevatorLength);
}

// Called repeatedly when this Command is scheduled to run
void ArmCMD::Execute()
{
  if(((*m_pTurretAngle >= 150) or (*m_pTurretAngle <= -150)) and (m_pPivot->GetPivotAngle() > 60.0) and ((m_pivotAngle >= 80.0)))
  {
    m_pivotPID.SetSetpoint(m_pPivot->GetPivotAngle());
    // Flash red and yell at drivers
  }

  

  m_pPivot->SetPivotMotor(m_pivotPID.Calculate(m_pPivot->GetPivotAngle()));
  m_pElevator->SetElevatorMotor(m_pivotPID.Calculate(m_pElevator->GetElevatorLength()));
}

// Called once the command ends or is interrupted.
void ArmCMD::End(bool interrupted)
{
  m_pPivot->SetPivotMotor(0.0);
  m_pElevator->SetElevatorMotor(0.0);
}

// Returns true when the command should end.
bool ArmCMD::IsFinished()
{
  bool value = false;
  if(((double)m_timer.Get() >= m_holdTime) and m_useIsFinished)
  {
    value = true;
  }

  return value;
}
