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

#include "cShader.h"
#include "cShaderProgram.h"

#include <GLI/cVertexArrayObject.h>

#include "cRenderer.h"

#include "cOBJ_loader.h"

#include "c_Camera.h"

#include "cKeyBasedControlHandler.h"

#include "cTexture.h"

#include <vector>



void RegisterControlCommandToHandler(cKeyBasedControlHandler* arg_ControlHandler);


nsGLI::cVertexArrayObject iVAO;

cTimeMeasure cMainApp::InitTime;
cTimeMeasure cMainApp::RunLoopTime;
cTimeMeasure cMainApp::ShutDownInitTime;

cKeyBasedControlHandler KeyboardControl;
extern cEventHandler G_EventHandler;



nsGLI::cFrameBuffer instFrameBufferTest01(800,600);
nsGLI::cGL_Texture  instTextureTest01(800, 600, GL_TEXTURE_2D, GL_RGBA);

std::vector<cTexture> TextureContainer;

//instances of shaders
cShader testShader_V(std::string("../Shaders/VertexShader01.glsl"), GL_VERTEX_SHADER);
cShader testShader_F(std::string("../Shaders/FragmentShader01.glsl"), GL_FRAGMENT_SHADER);
cShaderProgram testShaderProgram;

//instance of renderer class
cRenderer iRenderer;

cCamera iMainCamera(glm::vec3(0,0,30.0f), glm::vec3(0,0,-1.0f), glm::vec3(0,1,0));


void cMainApp::Init(void)
{
  InitTime.Begin();

  //iVAO.CreateVAO();
  //iVAO.BindVAO();

  instTextureTest01.GenerateTexture();
  instTextureTest01.AlocateDataSpaceB();

  cTexture loc_texture;

  TextureContainer.push_back(cTexture());
  //TextureContainer[0].LoadPictureFromFile("C:\\development\\resources\\cottage\\cottage_diffuse_2.png");
  TextureContainer[0].LoadPictureFromFile("C:\\development\\resources\\cottage\\testTex.png");
  TextureContainer[0].LoadToGpu();

  instFrameBufferTest01.InitFBO();
  instFrameBufferTest01.BindFBO();
  instFrameBufferTest01.AddColorAttachement(instTextureTest01);
  
  std::cout << std::hex <<  instFrameBufferTest01.CheckFBStatus() << std::endl;

  instFrameBufferTest01.UnBindFBO();


  //initialization of shaders
  testShader_V.InitShader();
  testShader_F.InitShader();
  testShaderProgram.InitShaderProgram(&testShader_V, &testShader_F);

  //initialization of renderer
  iRenderer.AttachShaderProgram(&testShaderProgram);
  iRenderer.AddCleaninFlags(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
  iRenderer.SetCleanColor(0.0f,0.0f,1.0f,1.0f);

  iRenderer.AsignCamera(&iMainCamera);


  //add temporary mesh for testing - remove when draw package is implemented

  cVertex loc_TmpVertexA;
  cVertex loc_TmpVertexB;
  cVertex loc_TmpVertexC;
  cVertex loc_TmpVertexD;

  loc_TmpVertexA.Position = glm::vec3(-1.0f,  1.0f, 0.0f);
  loc_TmpVertexB.Position = glm::vec3( 1.0f,  1.0f, 0.0f);
  loc_TmpVertexC.Position = glm::vec3( 1.0f, -1.0f, 0.0f);
  loc_TmpVertexD.Position = glm::vec3(-1.0f, -1.0f, 0.0f);

  loc_TmpVertexA.Normal = glm::vec3(1.0, 0.0, 0.0);
  loc_TmpVertexB.Normal = glm::vec3(0.0, 1.0, 0.0);
  loc_TmpVertexC.Normal = glm::vec3(0.0, 0.0, 1.0);
  loc_TmpVertexD.Normal = glm::vec3(0.0, 0.0, 0.0);

  loc_TmpVertexA.UV = glm::vec2(0.0, 0.0);
  loc_TmpVertexB.UV = glm::vec2(0.0, 1.0);
  loc_TmpVertexC.UV = glm::vec2(1.0, 1.0);
  loc_TmpVertexD.UV = glm::vec2(1.0, 0.0);

 // iRenderer.tmp_mesh.AddQuad(loc_TmpVertexA, loc_TmpVertexB, loc_TmpVertexC, loc_TmpVertexD);

  iRenderer.tmp_mesh.LoadModel<cOBJ_loader>("C:\\development\\resources\\cottage\\TestCube01.obj");

  iRenderer.tmp_mesh.CreateVBO();



  //init of control handler
  RegisterControlCommandToHandler(&KeyboardControl);

  InitTime.End();
}

void cMainApp::RunLoop(void)
{
  RunLoopTime.Begin();

  KeyboardControl.Cyclic(&G_EventHandler);
  TextureContainer[0].BindTexture();
  iRenderer.Draw();
  TextureContainer[0].UnBindTexture();

  RunLoopTime.End();
}

void cMainApp::ShutDown(void)
{
  ShutDownInitTime.Begin();


  ShutDownInitTime.End();
}
