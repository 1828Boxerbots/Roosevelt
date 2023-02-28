// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/VisionSub.h"

VisionSub::VisionSub(VisionSub::Pipelines* pPipeline)
{
    m_pPipeline = pPipeline;
}

//Periodic:
// This method will be called once per scheduler run
void VisionSub::Periodic() 
{
    if(m_previousPipeline != *m_pPipeline)
    {
        SetPipeline(*m_pPipeline);
        m_previousPipeline = *m_pPipeline;
    }
   //ShowData();
}

//Initialize:
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

    //If Target is Detected:
    if(hastargets == true)
    {
        //Best Target Variables:
        photonlib::PhotonTrackedTarget besttarget = result.GetBestTarget();
        std::vector<std::pair<double, double>> besttargetcorners = besttarget.GetDetectedCorners();

        frc::SmartDashboard::PutNumber("TargetBest corners Size", besttargetcorners.size());

        //If Target Size has Value:
        if (besttargetcorners.size() > 1)
        {
            //Top Left of Blob (Possibly):
            double x1 = besttargetcorners[0].first;
            double y1 = besttargetcorners[0].second;

            frc::SmartDashboard::PutNumber("TargetBest corners x1", x1);
            frc::SmartDashboard::PutNumber("TargetBest corners y1", y1);

            //Bottom Right of Blob (Possibly):
            double x2 = besttargetcorners[1].first;
            double y2 = besttargetcorners[1].second;

            frc::SmartDashboard::PutNumber("TargetBest corners x2", x2);
            frc::SmartDashboard::PutNumber("TargetBest corners y2", y2);

            //Center of Blob:
            double x3 = x1 + 0.5 * (x2 - x1);
            double y3 = y1 + 0.5 * (y2 - y1);

            frc::SmartDashboard::PutNumber("TargetBest corners x3", x3);
            frc::SmartDashboard::PutNumber("TargetBest corners y3", y3);
        }

        //Other Best Target Data Variables:
        frc::SmartDashboard::PutNumber("TargetBest Area", besttarget.GetArea());
        frc::SmartDashboard::PutNumber("TargetBest Pitch", besttarget.GetPitch());
        frc::SmartDashboard::PutNumber("TargetBest Pose", besttarget.GetPoseAmbiguity());
        frc::SmartDashboard::PutNumber("TargetBest Skew", besttarget.GetSkew());

        //For General Amount of Targets Detected:
        for(int i = 0; i<numtargets; i++)
        {
            //General Target Variables and Initialization:
            photonlib::PhotonTrackedTarget target = result.GetTargets()[i];
            std::vector<std::pair<double, double>> targetcorners = target.GetDetectedCorners();
            char message[256];

            //Rawbytes:
            sprintf(message, "Target[%d] Area", i);
            frc::SmartDashboard::PutNumber(message, target.GetArea());

            sprintf(message, "Target[%d] Pitch", i);
            frc::SmartDashboard::PutNumber(message, target.GetPitch());

            sprintf(message, "Target[%d] Pose", i);
            frc::SmartDashboard::PutNumber(message, target.GetPoseAmbiguity());

            sprintf(message, "Target[%d] Skew", i);
            frc::SmartDashboard::PutNumber(message, target.GetSkew());

            sprintf(message, "Target[%d] Yaw", i);
            frc::SmartDashboard::PutNumber(message, target.GetYaw());

            sprintf(message, "Target[%d] Corners Size", i);
            frc::SmartDashboard::PutNumber(message, targetcorners.size());

            //If Target Size has Value:
            if (targetcorners.size() > 1)
            {
                //Top Left of Blob (Possibly):
                double x1 = targetcorners[0].first;
                double y1 = targetcorners[0].second;

                sprintf(message, "Target[%d] Corners x1", i);
                frc::SmartDashboard::PutNumber(message, x1);
                sprintf(message, "Target[%d] Corners y1", i);
                frc::SmartDashboard::PutNumber(message, y1);

                //Bottom Right of Blob (Possibly):
                double x2 = targetcorners[1].first;
                double y2 = targetcorners[1].second;

                sprintf(message, "Target[%d] Corners x2", i);
                frc::SmartDashboard::PutNumber(message, x2);
                sprintf(message, "Target[%d] Corners y2", i);
                frc::SmartDashboard::PutNumber(message, y2);

                // center of blob
                double x3 = x1 + 0.5 * (x2 - x1);
                double y3 = y1 + 0.5 * (y2 - y1);

                sprintf(message, "Target[%d] Corners x3", i);
                frc::SmartDashboard::PutNumber(message, x3);
                sprintf(message, "Target[%d] Corners y3", i);
                frc::SmartDashboard::PutNumber(message, y3);
            }
        }
    }

    //Display Data:
    frc::SmartDashboard::PutBoolean("Driver Mode: ", drivemode);
    frc::SmartDashboard::PutBoolean("Has Targets: ", hastargets);
    frc::SmartDashboard::PutNumber("Number of Targets: ", numtargets);
    frc::SmartDashboard::PutNumber("Pipeline Index: ", pipelineindex);
}

//Set Pipeline:
void VisionSub::SetPipeline(Pipelines pipeline)
{
    //Determines Pipeline Mode:
    switch(pipeline)
    {
        case ReflectiveTapeBottom:
            m_camera.SetPipelineIndex(kPipelineReflectiveTapeBottom);
            break;

        case ReflectiveTapeTop:
            m_camera.SetPipelineIndex(kPipelineReflectiveTapeTop);
            break;

        case PseudoReflectiveTape:
            m_camera.SetPipelineIndex(kPipelinePseudoRT);
            break;

        case Cone:
            m_camera.SetPipelineIndex(kPipelineIndexCone);
            break;

        case Cube:
            m_camera.SetPipelineIndex(kPipelineIndexCube);
            break;

        case AprilTags:
        default:
            m_camera.SetPipelineIndex(kPipelineAprilTags);
            break;
    }
}

//Data Functions:
int VisionSub::GetPipelineIndex()
{
    //Displays Current Pipeline:
    return m_camera.GetPipelineIndex();
}

bool VisionSub::HasTarget()
{
    //Has Target Variables:
    photonlib::PhotonPipelineResult result = m_camera.GetLatestResult();
    bool hasTarget = result.HasTargets();

    //Has Target Data:
    frc::SmartDashboard::PutBoolean("Has Target:  ", hasTarget);

    return hasTarget;
}

double VisionSub::Yaw()
{
    //Yaw Variable:
    double yaw = 0.0;

    //If Target is Detected:
    if(HasTarget() == true)
    {
        //Variables:
        photonlib::PhotonPipelineResult result = m_camera.GetLatestResult();
        photonlib::PhotonTrackedTarget besttarget = result.GetBestTarget();
    
        //Pitch 90 Degrees Sideways:
        yaw = besttarget.GetPitch();
    }

    return yaw;
}

double VisionSub::Pitch()
{
    //Pitch Variable:
    double pitch = 0.0;

    //If Target is Detected:
    if(HasTarget() == true)
    {
        //Variables:
        photonlib::PhotonPipelineResult result = m_camera.GetLatestResult();
        photonlib::PhotonTrackedTarget besttarget = result.GetBestTarget();

        //Yaw 90 Degrees Sideways:
        pitch = besttarget.GetYaw();
    }

    return pitch;
}
