/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RobotDrive.h"

#include "Robot.h"

RobotDrive::RobotDrive() {
  // Use Requires() here to declare subsystem dependencies
  Requires(m_drivetrain);
}

// Called just before this Command runs the first time
void RobotDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RobotDrive::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool RobotDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void RobotDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RobotDrive::Interrupted() {}
