/*
 * cMainApp.h
 *
 *  Created on: 1. 2. 2017
 *      Author: GFreeman
 */

#ifndef CMAINAPP_H_
#define CMAINAPP_H_

#include "cTimeMeasure.h"

class cMainApp {
public:
  static cTimeMeasure InitTime;
  static cTimeMeasure RunLoopTime;
  static cTimeMeasure ShutDownInitTime;

  static void Init(void);
  static void RunLoop(void);
  static void ShutDown(void);
};

#endif /* CMAINAPP_H_ */
