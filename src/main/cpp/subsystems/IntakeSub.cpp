// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/IntakeSub.h"

IntakeSub::IntakeSub() = default;

void IntakeSub::Init()
{
    m_compressor.EnableDigital();
    m_isIntakeOpen = true;
    //SetIntake(false);
}

void IntakeSub::SetIntake(bool setOpen)
{
    Util::Log("SetIntake", setOpen);
    if(setOpen == true)
    {
        m_intake.Set(frc::DoubleSolenoid::kForward);
    }
    else if(setOpen == false)
    {
        m_intake.Set(frc::DoubleSolenoid::kReverse);
    }
    m_intake.Set(frc::DoubleSolenoid::kOff);
    m_isIntakeOpen = setOpen;
}

bool IntakeSub::IsIntakeOpen()
{
    return m_isIntakeOpen;
}

IntakeSub::ColorTargets IntakeSub::GetHeldObject()
{
    IntakeSub::ColorTargets object = IntakeSub::NOTHING;

    frc::Color currentColor = m_colorSensor.GetColor();

    if(((m_ConeTarget.red - m_ConeDead) < currentColor.red) and ((m_ConeTarget.red + m_ConeDead) > currentColor.red) and
      ((m_ConeTarget.blue -m_ConeDead)<currentColor.blue) and ((m_ConeTarget.blue +m_ConeDead)>currentColor.blue) and
      ((m_ConeTarget.green-m_ConeDead)<currentColor.green) and ((m_ConeTarget.green+m_ConeDead)>currentColor.green))
  {
    object = IntakeSub::CONE;
  }
  else if(((m_CubeTarget.red - m_CubeDead) < currentColor.red) and ((m_CubeTarget.red + m_CubeDead) > currentColor.red) and
      ((m_CubeTarget.blue -m_CubeDead)<currentColor.blue) and ((m_CubeTarget.blue +m_CubeDead)>currentColor.blue) and
      ((m_CubeTarget.green-m_CubeDead)<currentColor.green) and ((m_CubeTarget.green+m_CubeDead)>currentColor.green))
  {
    object = IntakeSub::CUBE;
  }
  
  return object;
}