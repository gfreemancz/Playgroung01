#include "stdafx.h"
#include "cShaderProgram.h"


ui8 cShaderProgram::InitShaderProgram(cShader * arg_VertexShader, cShader * arg_FragmentShader)
{
  ui8     loc_ReturnValue = 0;
  GLint   loc_GL_ResultStatus = 0;
  GLchar  loc_GL_infoLog[1024];

  // put pointers to shader in list
  ShaderList.push_back(arg_VertexShader);
  ShaderList.push_back(arg_FragmentShader);

  ShaderProgID = glCreateProgram(); // create/alocate shader program in GPU

  glAttachShader(ShaderProgID, ShaderList[0]->getID()); // attach 1st shader
  glAttachShader(ShaderProgID, ShaderList[1]->getID()); // attach 2nd shader
  glLinkProgram(ShaderProgID);                          // link shader program

  glGetProgramiv(ShaderProgID, GL_LINK_STATUS, &loc_GL_ResultStatus);
  if (!loc_GL_ResultStatus) 
  {  // if linkinng failed - report error
    glGetProgramInfoLog(ShaderProgID, 1023, NULL, loc_GL_infoLog);
    std::cout << "error: linking of shader program failed \n" << loc_GL_infoLog << std::endl;
    loc_ReturnValue++;
  }
    
  return loc_ReturnValue;
}

ui8 cShaderProgram::InitShaderProgram(cShader * arg_VertexShader, cShader * arg_FragmentShader, cShader * arg_GeometryShader)
{
  ui8     loc_ReturnValue = 0;
  GLint   loc_GL_ResultStatus;
  GLchar  loc_GL_infoLog[1024];

  // put pointers to shader in list
  ShaderList.push_back(arg_VertexShader);
  ShaderList.push_back(arg_FragmentShader);
  ShaderList.push_back(arg_GeometryShader);

  ShaderProgID = glCreateProgram(); // create/alocate shader program in GPU

  glAttachShader(ShaderProgID, ShaderList[0]->getID());// attach 1st shader
  glAttachShader(ShaderProgID, ShaderList[1]->getID());// attach 2nd shader
  glAttachShader(ShaderProgID, ShaderList[2]->getID());// attach 3th shader

  //glBindAttribLocation(ShaderProgID, 0, "aPos");

  glLinkProgram(ShaderProgID);                         // link shader program

  glGetProgramiv(ShaderProgID, GL_LINK_STATUS, &loc_GL_ResultStatus);
  if (!loc_GL_ResultStatus) 
  { // if linkinng failed - report error
    glGetProgramInfoLog(ShaderProgID, 1023, NULL, loc_GL_infoLog);
    std::cout << "error: linking of shader program failed \n" << loc_GL_infoLog << std::endl;
    loc_ReturnValue++;
  }

  return loc_ReturnValue;
}

void cShaderProgram::Use(void)
{
  if (ShaderList.size() > 0) // if list of shaders > 0 -> shader program was initialized
  {
    glUseProgram(ShaderProgID);
  }
  else
  {   // if shaderprogram was not initialized, report error
    std::cout << "error: Trying to use uninitialized shader program" << std::endl;
  }
}

void cShaderProgram::Stop(void)
{
  glUseProgram(0U);
}

ui32 cShaderProgram::GetUniformLocation(std::string arg_UniformVariableName)
{
  return (ui32)glGetUniformLocation(ShaderProgID, arg_UniformVariableName.c_str());
}

void cShaderProgram::SetUniformMatrix4x4(ui32 arg_id, glm::mat4x4 * arg_MatrixPtr)
{
  glUniformMatrix4fv(arg_id, 1, GL_FALSE, (float*)arg_MatrixPtr);
}

cShaderProgram::cShaderProgram() :
  ShaderProgID(0),
  ShaderList()
{
}


cShaderProgram::~cShaderProgram()
{
  // clear memory
  if (ShaderProgID!=0)
  {
    glDeleteProgram(ShaderProgID);
  }
  ShaderList.clear();
}
