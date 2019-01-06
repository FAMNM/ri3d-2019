/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/Spark.h>
#include <frc/SpeedControllerGroup.h>

class Chassis : public frc::Subsystem {
 public:
  Chassis();
  void InitDefaultCommand() override;
  void move();
  void stop();

 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  frc::Spark frontLeft;
  frc::Spark frontRight;
  frc::Spark backLeft;
  frc::Spark backRight;
  frc::SpeedControllerGroup left;
  frc::SpeedControllerGroup right;
  frc::DifferentialDrive dDrive;
};
