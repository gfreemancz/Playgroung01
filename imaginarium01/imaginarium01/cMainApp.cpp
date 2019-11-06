/*
 * cMainApp.cpp
 *
 *  Created on: 1. 2. 2017
 *      Author: GFreeman
 */
#include "stdafx.h"
#include "cMainApp.h"

#include "GLI/cFrameBuffer.h"
#include "cGL_Texture.h"



cTimeMeasure cMainApp::InitTime;
cTimeMeasure cMainApp::RunLoopTime;
cTimeMeasure cMainApp::ShutDownInitTime;



nsGLI::cFrameBuffer iFrameBufferTest01(800,600);
nsGLI::cGL_Texture  iTextureTest01(800, 600, GL_TEXTURE_2D, GL_RGBA);


void cMainApp::Init(void)
{
  InitTime.Begin();

  iTextureTest01.GenerateTexture();
  iTextureTest01.AlocateDataSpaceB();



  iFrameBufferTest01.InitFBO();
  iFrameBufferTest01.BindFBO();
  iFrameBufferTest01.AddColorAttachement(iTextureTest01);
  
  std::cout << std::hex <<  iFrameBufferTest01.CheckFBStatus() << std::endl;

  iFrameBufferTest01.UnBindFBO();

  InitTime.End();
}

void cMainApp::RunLoop(void)
{
  RunLoopTime.Begin();


  RunLoopTime.End();
}

void cMainApp::ShutDown(void)
{
  ShutDownInitTime.Begin();


  ShutDownInitTime.End();
}
