// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/VisionSub.h"

VisionSub::VisionSub() = default;

// This method will be called once per scheduler run
void VisionSub::Periodic() 
{
   ShowData();
}

void VisionSub::Init()
{
    SetPipeline(AprilTags);
}

void VisionSub::ShowData()
{
    //Data Variables:
    photonlib::PhotonPipelineResult result = m_camera.GetLatestResult();
    int pipelineindex = m_camera.GetPipelineIndex();
    int numtargets = result.GetTargets().size();
    bool hastargets = result.HasTargets();
    double drivemode = m_camera.GetDriverMode();

    if(hastargets == true)
    {
        
        photonlib::PhotonTrackedTarget besttarget = result.GetBestTarget();
        std::vector<std::pair<double, double>> besttargetcorners = besttarget.GetDetectedCorners();
        frc::SmartDashboard::PutNumber("Targetbestcorners Size", besttargetcorners.size());
        if (besttargetcorners.size() > 1)
        {
            // maybe top left? of blob
            double x1 = besttargetcorners[0].first;
            double y1 = besttargetcorners[0].second;
            // maybe bottom right? of blob
            double x2 = besttargetcorners[1].first;
            double y2 = besttargetcorners[1].second;
            // center of blob
            double x3 = x1 + 0.5 * (x2 - x1);
            double y3 = y1 + 0.5 * (y2 - y1);
            frc::SmartDashboard::PutNumber("Targetbestcorners x1", x1);
            frc::SmartDashboard::PutNumber("Targetbestcorners y1", y1);
            frc::SmartDashboard::PutNumber("Targetbestcorners x2", x2);
            frc::SmartDashboard::PutNumber("Targetbestcorners y2", y2);
            frc::SmartDashboard::PutNumber("Targetbestcorners x3", x3);
            frc::SmartDashboard::PutNumber("Targetbestcorners y3", y3);
        }

        units::meter_t range = photonlib::PhotonUtils::CalculateDistanceToTarget(
            kCameraHeight, m_targetHeight, kCameraPitch,
           units::degree_t{besttarget.GetPitch()});

        frc::SmartDashboard::PutNumber("targetbest targetheight: ", (double) m_targetHeight);
        frc::SmartDashboard::PutNumber("targetbest Range", (double)((units::inch_t) range));
        frc::SmartDashboard::PutNumber("targetbest Area", besttarget.GetArea());
        frc::SmartDashboard::PutNumber("targetbest Pitch", besttarget.GetPitch());
        frc::SmartDashboard::PutNumber("targetbest Pose", besttarget.GetPoseAmbiguity());
        frc::SmartDashboard::PutNumber("targetbest Skew", besttarget.GetSkew());

        
        for(int i = 0; i<numtargets; i++)
        {
            photonlib::PhotonTrackedTarget target = result.GetTargets()[i];
            char message[256];

            //rawbytes:
            sprintf(message, "target[%d] Area", i);
            frc::SmartDashboard::PutNumber(message, target.GetArea());

            sprintf(message, "target[%d] Pitch", i);
            frc::SmartDashboard::PutNumber(message, target.GetPitch());

            sprintf(message, "target[%d] Pose", i);
            frc::SmartDashboard::PutNumber(message, target.GetPoseAmbiguity());

            sprintf(message, "target[%d] Skew", i);
            frc::SmartDashboard::PutNumber(message, target.GetSkew());

            sprintf(message, "target[%d] Yaw", i);
            frc::SmartDashboard::PutNumber(message, target.GetYaw());

            range = photonlib::PhotonUtils::CalculateDistanceToTarget(
             kCameraHeight, m_targetHeight, kCameraPitch,
             units::degree_t{target.GetPitch()});

           sprintf(message, "target[%d] Range", i);
           frc::SmartDashboard::PutNumber(message, (double)((units::inch_t) range));

            std::vector<std::pair<double, double>> targetcorners = target.GetDetectedCorners();
            sprintf(message, "target[%d] corners size");
            frc::SmartDashboard::PutNumber(message, targetcorners.size());
            if (targetcorners.size() > 1)
            {
                // maybe top left? of blob
                double x1 = targetcorners[0].first;
                double y1 = targetcorners[0].second;
                // maybe bottom right? of blob
                double x2 = targetcorners[1].first;
                double y2 = targetcorners[1].second;
                // center of blob
                double x3 = x1 + 0.5 * (x2 - x1);
                double y3 = y1 + 0.5 * (y2 - y1);
                sprintf(message, "target[%d] corners x1");
                frc::SmartDashboard::PutNumber(message, x1);
                sprintf(message, "target[%d] corners y1");
                frc::SmartDashboard::PutNumber(message, y1);
                sprintf(message, "target[%d] corners x2");
                frc::SmartDashboard::PutNumber(message, x2);
                sprintf(message, "target[%d] corners y2");
                frc::SmartDashboard::PutNumber(message, y2);
                sprintf(message, "target[%d] corners x3");
                frc::SmartDashboard::PutNumber(message, x3);
                sprintf(message, "target[%d] corners y3");
                frc::SmartDashboard::PutNumber(message, y3);
            }
        }

    }

    //Display Data:
    frc::SmartDashboard::PutBoolean("Driver Mode: ", drivemode);
    frc::SmartDashboard::PutBoolean("Has Targets: ", hastargets);
    frc::SmartDashboard::PutNumber("Number of Targets ", numtargets);
    frc::SmartDashboard::PutNumber("pipelineIndex", pipelineindex);
}

void VisionSub::SetPipeline(Pipelines pipeline)
{
    switch(pipeline)
    {
        case ReflectiveTapeBottom:
            m_camera.SetPipelineIndex(kPipelineReflectiveTapeBottom);

            m_targetHeight = kTargetHeightReflectiveTape;

            break;

        case ReflectiveTapeTop:
            m_camera.SetPipelineIndex(kPipelineReflectiveTapeTop);

            m_targetHeight = kTargetHeightReflectiveTape;

            break;

        case PseudoReflectiveTape:
            m_camera.SetPipelineIndex(kPipelinePseudoRT);

            m_targetHeight = kTargetHeightPRT;

            break;

        case Cone:
            m_camera.SetPipelineIndex(kPipelineIndexCone);

            m_targetHeight = kTargetHeightCone;

            break;

        case Cube:
            m_camera.SetPipelineIndex(kPipelineIndexCube);

            m_targetHeight = kTargetHeightCube;

            break;

        case AprilTags:
        default:
            m_camera.SetPipelineIndex(kPipelineAprilTags);

            m_targetHeight = kTargetHeightAprilTag;

            break;
    }
}

void VisionSub::FindTargetDistance()
{
    if (GetHasTarget()) 
    {
    // Calculate Range:
    units::meter_t m_targetRange = photonlib::PhotonUtils::CalculateDistanceToTarget
    (kCameraHeight, m_targetHeight, kCameraPitch,
    units::degree_t{});

    frc::SmartDashboard::PutNumber("Target Range: ", (double) m_targetRange);
    }
}


int VisionSub::GetPipelineIndex()
{
    return m_camera.GetPipelineIndex();
}

bool VisionSub::GetHasTarget()
{
    photonlib::PhotonPipelineResult result = m_camera.GetLatestResult();
    bool hasTarget = result.HasTargets();
    frc::SmartDashboard::PutBoolean("Has Target:  ", hasTarget);
    return hasTarget;
}

double VisionSub::GetYaw()
{
    double yaw = 0.0;

    if(GetHasTarget() == true)
    {
        photonlib::PhotonPipelineResult result = m_camera.GetLatestResult();
        photonlib::PhotonTrackedTarget besttarget = result.GetBestTarget();
        yaw = besttarget.GetPitch(); //90 Degrees
    }

    return yaw;
}

double VisionSub::GetPitch()
{
    double pitch = 0.0;

    if(GetHasTarget() == true)
    {
        photonlib::PhotonPipelineResult result = m_camera.GetLatestResult();
        photonlib::PhotonTrackedTarget besttarget = result.GetBestTarget();
        pitch = besttarget.GetYaw(); //90 Degrees
    }

    return pitch;
}
