// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <photonlib/PhotonCamera.h>
#include <photonlib/PhotonUtils.h>
#include <photonlib/PhotonPipelineResult.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/motorcontrol/Victor.h>
#include <frc/XboxController.h>
#include <frc/controller/PIDController.h>
#include <units/angle.h>
#include <units/length.h>

class VisionSub : public frc2::SubsystemBase 
{
 public:
 //Constructor:
  VisionSub();

  //Initialize:
  void Init();

  //Pipeline:
  enum Pipelines
  {
    AprilTags, ReflectiveTapeTop, ReflectiveTapeBottom, PseudoReflectiveTape, Cone, Cube
  };

  void SetPipeline(Pipelines pipeline);
  
  //Data:
  void ShowData();
  void FindTargetDistance();
  bool GetHasTarget();
  int GetPipelineIndex();
  double GetYaw();
  double GetPitch();

  //Operational Functions:
  void DriveRC(double forward, double rotation);
  void AimAtTarget(int pipeline);

  // Other Functions:
  void Periodic() override;

  private:
  //Camera 
  photonlib::PhotonCamera m_camera{"MicrosoftLifeCamHDTest1"};

  //PhotonVision Variables:
  const int kPipelineAprilTags = 3;
  const int kPipelineIndexCube = 2;
  const int kPipelineIndexCone = 1;
  const int kPipelineReflectiveTapeBottom = 0;
  const int kPipelineReflectiveTapeTop = 4;
  const int kPipelinePseudoRT = 5;
  units::meter_t m_targetHeight = 0.0_in;
  const units::meter_t kCameraHeight = 0.0_in;
  const units::degree_t kCameraPitch = 0.0_deg;
  const units::meter_t kTargetHeightReflectiveTape = 2.0_in;
  const units::meter_t kTargetHeightAprilTag = 8.5_in;
  const units::meter_t kTargetHeightCube = 9.5_in;
  const units::meter_t kTargetHeightCone = 12.8125_in;
  const units::meter_t kTargetHeightPRT = 7.0_in;
};