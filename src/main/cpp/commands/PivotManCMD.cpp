// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/PivotManCMD.h"

PivotManCMD::PivotManCMD(PivotSub* pPivot, frc::XboxController* pXbox, double (frc::XboxController::*input)() const, double* pTurretAngle, bool usePID, double scale)
{
  m_pPivot = pPivot;
  m_scale = scale;
  m_pXbox = pXbox;
  m_Input = input;
  m_usePID = usePID;
  m_pTurretAngle = pTurretAngle;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pPivot);
}

// Called when the command is initially scheduled.
void PivotManCMD::Initialize()
{
  m_pid.Reset();
}

// Called repeatedly when this Command is scheduled to run
void PivotManCMD::Execute()
{
  double speed = (m_pXbox->*m_Input)();
  if((speed > 0 and m_pPivot->GetPivotAngle() > kBatteryPivotAngleLimit and *m_pTurretAngle > kBatteryTurretAngleLimit)
      or (speed < 0 and m_pPivot->GetPivotAngle() > kBatteryPivotAngleLimit and *m_pTurretAngle < -kBatteryTurretAngleLimit))
  {
    speed = 0.0;
    // Flash Red and yell at drivers
  }
  
  if(m_usePID)
  {
    if(speed < 0.1 and speed > -0.1)
    {
      m_pid.SetSetpoint(m_pPivot->GetPivotAngle());
      speed = m_pid.Calculate(m_pPivot->GetPivotAngle());
    }
  }

  m_pPivot->SetPivotMotor(speed);
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
