#pragma once

#ifndef STDAFX_H
#include "stdafx.h"
#endif

#include <SDL.h>

//#define GLEW_STATIC
#include <glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>



#include "vector"

namespace nsGLI {

  template<class T,  ui16 T_GL>
  class cGLBufferObject
  {
    std::vector<T> Data;
    GLuint GL_BO_id;
    ui16 GL_BO_usage;
    ui16 GL_BO_Tarrget;
    ui8  Atr_index;
    ui8  Atr_Size;
  

  public:
    cGLBufferObject();
    cGLBufferObject(ui16 arg_usage, ui8 Arg_AtrIdx, ui8 Arg_AtrSize, ui16 art_BufferTarget);
    ~cGLBufferObject();

    void AddElement(T arg_element);
    //load data of whole VBO in GPU and setup atribute access for shaders
    void LoadDataToGPU(void);
    //update data of whole VBO in GPU 
    void UpdateDataInGPU(void)
    {
      glNamedBufferSubData(GL_BO_id, 0, Data.size() * Atr_Size * 4, &Data[0]);
    }
    //update data of part of VBO in GPU 
    void UpdateDataInGPU(ui32 arg_offset, ui32 arg_UpdateVertexCount)
    {
      glNamedBufferSubData(GL_BO_id, arg_offset, arg_UpdateVertexCount * sizeof(T), &Data[0]);
    }

    //activate VBO in GPU
    void BindBufferObject(void)
    {
      glBindBuffer(GL_BO_Tarrget, GL_BO_id);
    }
    void UnBindBufferObject(void)
    {
      glBindBuffer(GL_BO_Tarrget, 0);
    }
    //create VBO in GPU
    void CreateBufferObject(void)
    {
      glGenBuffers(1, &GL_BO_id);
    }
    void DeleteBuffer(void)
    {
      glDeleteBuffers(1, &VBO_id);
    }

    T GetElement(ui32 arg_idx)
    {
      return Data[arg_idx];
    }

    ui32 GetBufferSize(void)
    {
      return static_cast<ui32>(Data.size());
    }

    void ActivateAtribute(void)
    {
      glVertexAttribPointer(Atr_index, Atr_Size, T_GL, GL_FALSE, Atr_Size * 4, (void*)0);
      glEnableVertexAttribArray(Atr_index);
    }

  };

  template<class T, ui16 T_GL>
  inline cGLBufferObject<T, T_GL>::cGLBufferObject() :
    GL_BO_id(-1),
    GL_BO_usage(0),
    GL_BO_Tarrget(0),
    Atr_index(0),
    Atr_Size(1)
  {
  }

  template<class T,  ui16 T_GL>
  inline cGLBufferObject<T,  T_GL>::cGLBufferObject(ui16 arg_usage, ui8 Arg_AtrIdx, ui8 Arg_AtrSize, ui16 art_BufferTarget):
    GL_BO_id(-1 ),
    GL_BO_usage(arg_usage),
    GL_BO_Tarrget(art_BufferTarget),
    Atr_index(Arg_AtrIdx),
    Atr_Size(Arg_AtrSize)
  {

  }

  template<class T,  ui16 T_GL>
  inline cGLBufferObject<T,  T_GL>::~cGLBufferObject()
  {
    //if not empty, delete data in RAM
    if (Data.size() > 0)
    {
      Data.clear();
      //  delete &Data;
    }
    //if needed, delete VBO in GPU
    if (GL_BO_id != -1)
    {
      glDeleteBuffers(1, &GL_BO_id);
    }
  }



  template<class T,  ui16 T_GL>
  inline void cGLBufferObject<T,  T_GL>::LoadDataToGPU(void)
  {
    glBindBuffer(GL_BO_Tarrget, GL_BO_id);
    glBufferData(GL_BO_Tarrget, Data.size() * Atr_Size * 4, &Data[0], GL_BO_usage);
    //glNamedBufferSubData(GL_BO_id, 0, Data.size() * Atr_Size * 4, &Data[0]);
  //  glBindBuffer(GL_BO_Tarrget, 0);

    GLenum loc_ErrorState = glGetError();
  }
  
  

  template<class T,  ui16 T_GL>
  inline void cGLBufferObject<T,  T_GL>::AddElement(T arg_element)
  {
    Data.push_back(arg_element);
  }

}