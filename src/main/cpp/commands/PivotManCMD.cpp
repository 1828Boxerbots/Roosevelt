// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/PivotManCMD.h"

PivotManCMD::PivotManCMD(PivotSub* pPivot, double* pTurretAngle, frc::XboxController* pXbox, double (frc::XboxController::*pUpInput)() const, double (frc::XboxController::*pDownInput)() const,
               bool useLimits, double scale)
{
  m_pPivot = pPivot;
  m_pTurretAngle = pTurretAngle;
  m_pXbox = pXbox;
  m_pUpInput = pUpInput;
  m_pDownInput = pDownInput;
  m_useLimits = useLimits;
  m_scale = scale;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pPivot);
}

// Called when the command is initially scheduled.
void PivotManCMD::Initialize()
{
  m_pivotPID.Reset();

  m_pivotSetPoint = m_pPivot->GetPivotAngle();
}

// Called repeatedly when this Command is scheduled to run
void PivotManCMD::Execute()
{
  double pivotSpeed = 0.0; //((m_pXbox->*m_pUpInput)() - (m_pXbox->*m_pDownInput)()) * m_scale));

  // Incrementally change PID Setpoint by adding the input to the previous setpoint
  m_pivotSetPoint = m_pivotSetPoint + (((m_pXbox->*m_pUpInput)() - (m_pXbox->*m_pDownInput)()) * m_scale);

  // Set Pivot Setpoint
  m_pivotPID.SetSetpoint(m_pivotSetPoint);

  pivotSpeed = m_pivotPID.Calculate(m_pPivot->GetPivotAngle());

  // Check for turret angle and pivot speed
  if(m_useLimits)
  {
    if(((pivotSpeed > 0) and (m_pPivot->GetPivotAngle() > kBatteryPivotAngleLimit) and (*m_pTurretAngle > kBatteryTurretAngleLimit))
        or ((pivotSpeed < 0) and (m_pPivot->GetPivotAngle() > kBatteryPivotAngleLimit) and (*m_pTurretAngle < -kBatteryTurretAngleLimit)))
    {
      pivotSpeed = 0.0;
      // Flash Red and yell at drivers
    }
  }

  Util::Log("PivotMan", "Pivot Speed");
  m_pPivot->SetPivotMotor(pivotSpeed);
}

// Called once the command ends or is interrupted.
void PivotManCMD::End(bool interrupted)
{
  m_pPivot->SetPivotMotor(0.0);
}

// Returns true when the command should end.
bool PivotManCMD::IsFinished() {
  return false;
}
