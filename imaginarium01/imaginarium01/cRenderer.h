#pragma once

#include "stdafx.h"

#include "cFrameBuffer.h"




class cRenderer
{
	nsGLI::cFrameBuffer *TargetFrameBuffer;
  ui32 CleaningFlags;
public:
  cRenderer();
  cRenderer(nsGLI::cFrameBuffer * arg_TargetFBO);
	~cRenderer();

  void SetCleaninFlags(ui32 arg_Flags) { CleaningFlags = arg_Flags; }
  void AddCleaninFlags(ui32 arg_Flags) { CleaningFlags |= arg_Flags; }
  void ClearCleaninFlags(void) { CleaningFlags = 0U; }
  ui32 AddCleaninFlags(void) { return CleaningFlags; }
	void Draw(void);
};

