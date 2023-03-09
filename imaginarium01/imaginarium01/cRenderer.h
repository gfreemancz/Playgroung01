#pragma once

#include "stdafx.h"
#include "cShaderProgram.h"
#include "cFrameBuffer.h"
#include "c_Camera.h"
#include "cMesh.h"

#include <vector>


class cRenderer
{
	nsGLI::cFrameBuffer *TargetFrameBuffer;
  cShaderProgram   *ShaderProgram;
  ui32 CleaningFlags;
  float ClearColor_R;
  float ClearColor_G;
  float ClearColor_B;
  float ClearColor_A;
  cCamera* ActiveCamera;
  

public:
  std::vector<cMeshT*> MeshPackage;



  cRenderer();
  cRenderer(nsGLI::cFrameBuffer * arg_TargetFBO);
	~cRenderer();
  void SetCleanColor(float arg_R, float arg_G, float arg_B, float arg_A );
  void SetCleaninFlags(ui32 arg_Flags) { CleaningFlags = arg_Flags; }
  void AddCleaninFlags(ui32 arg_Flags) { CleaningFlags |= arg_Flags; }
  void ClearCleaninFlags(void) { CleaningFlags = 0U; }
  ui32 GetCleaninFlags(void) { return CleaningFlags; }
  void AttachShaderProgram(cShaderProgram* arg_ShProg) { ShaderProgram = arg_ShProg; }
	void Draw(void);
  void AsignCamera(cCamera* arg_Camera);
  void AddMesh(cMeshT * arg_pMesh);
};

