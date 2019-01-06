/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Spark.h>
#include <frc/Servo.h>

class CoverKey : public frc::Subsystem {
 public:
  CoverKey();
  void InitDefaultCommand() override;

 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  frc::Servo keyMotor;
  frc::Spark keyLift;
};
