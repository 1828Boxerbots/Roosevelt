// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ArmManCMD.h"

ArmManCMD::ArmManCMD(PivotSub* pPivot, ElevatorSub* pElevate, double* pTurretAngle, frc::XboxController* pXbox,
            double (frc::XboxController::*pPivotFunctionUp)()const,
            double (frc::XboxController::*pPivotFunctionDown)()const,
            double (frc::XboxController::*pElevatorFunction)()const,
            bool useLimits,
            double pivotScale, double elevateScale)
{
  m_pPivot = pPivot;
  m_pElevate = pElevate;
  m_pTurretAngle = pTurretAngle;
  m_pXbox = pXbox;
  m_pPivotFunctionUp = pPivotFunctionUp;
  m_pPivotFunctionDown = pPivotFunctionDown;
  m_pElevatorFunction = pElevatorFunction;
  m_useLimits = useLimits;
  m_pivotScale = pivotScale;
  m_elevateScale = elevateScale;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pPivot);
  AddRequirements(m_pElevate);
}

// Called when the command is initially scheduled.
void ArmManCMD::Initialize() {Util::Log("ArmMan", "Init");}

// Called repeatedly when this Command is scheduled to run
void ArmManCMD::Execute()
{
  double elevatorSpeed = ((m_pXbox->*m_pElevatorFunction)() * m_elevateScale);
  Util::Log("ArmCMD Elevatorspeed", elevatorSpeed);
  double pivotSpeed = ((m_pXbox->*m_pPivotFunctionUp)() - (m_pXbox->*m_pPivotFunctionDown)()) * m_pivotScale;
  Util::Log("ArmMan", "Speed");

  double height = cos(m_pPivot->GetPivotAngle() * (M_PI/180.0)) * m_pElevate->GetElevatorLength();
  double distance = sin(m_pPivot->GetPivotAngle() * (M_PI/180.0)) * m_pElevate->GetElevatorLength();

  Util::Log("Current Height", height);
  Util::Log("Current Distance", distance);

  Util::Log("kHeightLimit", kHeightLimit);
  Util::Log("kDistanceLimit", kDistanceLimit);

  // if(m_pElevate->GetElevatorLength() >= 15.0 and elevatorSpeed < 0.0)
  // {
  //   elevatorSpeed = 0;
  //   Util::Log("ArmMan", "Stop for extention");
  // }

  // Max height is 78 inches, robot base to turret is ~9in, 43 inch long arm by default (when GetLength = 0)
  // 79 - 9 - 43 = 26 
  if(height > kHeightLimit)
  {
    elevatorSpeed = m_elevateScale;
  }
  // Max distance is 48 inches outside frame perminitar, frame to middle of robot is 14.125 inches, 43 inch long arm by default (when GetLength = 0)
  // (48+14.125)-43 = 19.125
  if(distance > kDistanceLimit)
  {
    elevatorSpeed = m_elevateScale;
  }

  Util::Log("ArmMan", "Before elevate");
  m_pElevate->SetElevatorMotor(elevatorSpeed);
  Util::Log("ArmMan", "After elevate");

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
    Util::Log("ArmMan", "Pivot Speed");
    m_pPivot->SetPivotMotor(pivotSpeed);
}

// Called once the command ends or is interrupted.
void ArmManCMD::End(bool interrupted)
{
  m_pPivot->SetPivotMotor(0.0);
  m_pElevate->SetElevatorMotor(0.0);
}

// Returns true when the command should end.
bool ArmManCMD::IsFinished() {
  return false;
}
