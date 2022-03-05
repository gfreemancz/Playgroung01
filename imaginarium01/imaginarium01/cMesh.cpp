#include "stdafx.h"
#include "cMesh.h"


cMeshT::cMeshT():
  PositionBuffer(GL_STATIC_DRAW,0,3, GL_ARRAY_BUFFER),
  IndexBuffer(GL_STATIC_DRAW, 0,1, GL_ELEMENT_ARRAY_BUFFER),
  NormalBuffer(GL_STATIC_DRAW, 1,3, GL_ARRAY_BUFFER),
  UV_Buffer(GL_STATIC_DRAW,2,2, GL_ARRAY_BUFFER)
{
}


cMeshT::~cMeshT()
{
  //VertexBuffer.DeleteBuffer();
}

void cMeshT::AddVertexPosition(glm::vec3 arg_Position)
{
  VertexPositions.push_back(arg_Position);
}

void cMeshT::AddVertexNormal(glm::vec3 arg_Normal)
{
  VertexNormals.push_back(arg_Normal);
}

void cMeshT::AddVertexUV(glm::vec2 arg_UV)
{
  VertexUVs.push_back(arg_UV);
}

void cMeshT::AddTriangle(cVertex arg_VertexA, cVertex arg_VertexB, cVertex arg_VertexC)
{
  sTriangle loc_triangle;
  ui32 loc_VertId_A = CheckAndAddVertex(arg_VertexA);
  ui32 loc_VertId_B = CheckAndAddVertex(arg_VertexB);
  ui32 loc_VertId_C = CheckAndAddVertex(arg_VertexC);

  loc_triangle.VertexID[0] = loc_VertId_A;
  loc_triangle.VertexID[1] = loc_VertId_B;
  loc_triangle.VertexID[2] = loc_VertId_C;
  
  Triangles.push_back(loc_triangle);
}

void cMeshT::AddQuad(cVertex arg_VertexA, cVertex arg_VertexB, cVertex arg_VertexC, cVertex arg_VertexD)
{
  AddTriangle(arg_VertexA, arg_VertexC ,arg_VertexB );
  AddTriangle(arg_VertexA, arg_VertexD, arg_VertexC);
}

void cMeshT::CreateVBO(void)
{
  ui32 loc_TmpIdx_V, loc_TmpIdx_N, loc_TmpIdx_UV;
  ui32 loc_bufferSize = PositionBuffer.GetBufferSize();
  ui32 loc_CheckedBufferReturn;

  VertexArrayObject.CreateVAO();


  PositionBuffer.CreateBufferObject();
  NormalBuffer.CreateBufferObject();
  UV_Buffer.CreateBufferObject();
  IndexBuffer.CreateBufferObject();
  GLenum loc_ErrorState = glGetError();

  for (ui32 loc_TIdx = 0; loc_TIdx < Triangles.size(); loc_TIdx++)
  {
    for (ui8 i = 0; i < 3; i++)
    {
    
      loc_TmpIdx_V = VertexIdx[Triangles[loc_TIdx].VertexID[i]].pos_id;
      loc_TmpIdx_N = VertexIdx[Triangles[loc_TIdx].VertexID[i]].normal_id;
      loc_TmpIdx_UV = VertexIdx[Triangles[loc_TIdx].VertexID[i]].UV_id;

      loc_CheckedBufferReturn = CheckBufferCombination(VertexPositions[loc_TmpIdx_V], VertexNormals[loc_TmpIdx_N], VertexUVs[loc_TmpIdx_UV]);

      if (loc_CheckedBufferReturn < loc_bufferSize)
      {
        IndexBuffer.AddElement(loc_CheckedBufferReturn);
      }
      else  if (loc_CheckedBufferReturn == loc_bufferSize)
      {
        PositionBuffer.AddElement(VertexPositions[loc_TmpIdx_V]);
        NormalBuffer.AddElement(VertexNormals[loc_TmpIdx_N]);
        UV_Buffer.AddElement(VertexUVs[loc_TmpIdx_UV]);
        loc_bufferSize++;

        IndexBuffer.AddElement(loc_CheckedBufferReturn);
      }
      else
      {
        //TODO report error - inconsistent buffers
        return;

      }
    }
  } 
  
  
  


  PositionBuffer.LoadDataToGPU();
  PositionBuffer.ActivateAtribute();

  NormalBuffer.LoadDataToGPU();
  NormalBuffer.ActivateAtribute();

  UV_Buffer.LoadDataToGPU();
  UV_Buffer.ActivateAtribute();


  IndexBuffer.LoadDataToGPU();


  VertexArrayObject.BindVAO();

  PositionBuffer.BindBufferObject();
  PositionBuffer.ActivateAtribute();

  NormalBuffer.BindBufferObject();
  NormalBuffer.ActivateAtribute();

  UV_Buffer.BindBufferObject();
  UV_Buffer.ActivateAtribute();

  IndexBuffer.BindBufferObject();

  loc_ErrorState = glGetError();

  VertexArrayObject.UnBindVAO();

}

void cMeshT::UpdateVBO(void)
{

}

void cMeshT::Draw(void)
{
  VertexArrayObject.BindVAO();

#if (READOUT_OF_OGL_ERRORS==1)
   GLenum loc_ErrorState = glGetError();
#endif    
   
  glDrawElements(GL_TRIANGLES, IndexBuffer.GetBufferSize(), GL_UNSIGNED_INT, (GLvoid*)0);

#if (READOUT_OF_OGL_ERRORS==1)
  loc_ErrorState = glGetError();
#endif

  VertexArrayObject.UnBindVAO();
}



ui32 cMeshT::CheckAndAddVertex(cVertex arg_Vertex)
{
  ui32 loc_PosId    = CheckPosList(arg_Vertex.Position);
  ui32 loc_NormalId = CheckNormalPosList(arg_Vertex.Normal);
  ui32 UV_Id        = CheckUVPosList(arg_Vertex.UV);
  ui32 loc_VertexID;
  sVertexIdx loc_VertId;


  //check if vertex position is already registered, if not, append to vector of positions
  if (loc_PosId >= VertexPositions.size()|| VertexPositions.size() == 0)
  {
    VertexPositions.push_back(arg_Vertex.Position);
  }
  //check if vertex normal is already registered, if not, append to vector of normals
  if (loc_NormalId >= VertexNormals.size() || VertexNormals.size() == 0)
  {
    VertexNormals.push_back(arg_Vertex.Normal);
  }
  //check if vertex UV coordinate is already registered, if not, append to vector of UV coordinates
  if (UV_Id >= VertexUVs.size() || VertexUVs.size() == 0)
  {
    VertexUVs.push_back(arg_Vertex.UV);
  }

  loc_VertId.pos_id = loc_PosId;
  loc_VertId.normal_id = loc_NormalId;
  loc_VertId.UV_id = UV_Id;

  loc_VertexID = CheckVertexList(loc_VertId);

  //check if idx combination for vertex is already registered, if not, append to vector vertex id combinations
  if (loc_VertexID >= VertexIdx.size() || VertexIdx.size() == 0)
  {
    VertexIdx.push_back(loc_VertId);
  }
  return loc_VertexID;
}


ui32 cMeshT::CheckPosList(glm::vec3 arg_elementCheck)
{
  ui32 loc_idx;
  for (loc_idx = 0; loc_idx < VertexPositions.size() ; loc_idx++)
  {
    if (VertexPositions[loc_idx] == arg_elementCheck)
    {
      break;
    }
  }
  return loc_idx;
}

ui32 cMeshT::CheckNormalPosList(glm::vec3 arg_elementCheck)
{
  ui32 loc_idx;
  for (loc_idx = 0; loc_idx < VertexNormals.size(); loc_idx++)
  {
    if (VertexNormals[loc_idx] == arg_elementCheck)
    {
      break;
    }
  }
  return loc_idx;
}


ui32 cMeshT::CheckUVPosList(glm::vec2 arg_elementCheck)
{
  ui32 loc_idx;
  for (loc_idx = 0; loc_idx < VertexUVs.size(); loc_idx++)
  {
    if (VertexUVs[loc_idx] == arg_elementCheck)
    {
      break;
    }
  }
  return loc_idx;
}

ui32 cMeshT::CheckVertexList(sVertexIdx arg_elementCheck)
{
  ui32 loc_idx;
  for (loc_idx = 0; loc_idx < VertexIdx.size(); loc_idx++)
  {
    if (   (VertexIdx[loc_idx].pos_id == arg_elementCheck.pos_id)
      && (VertexIdx[loc_idx].normal_id == arg_elementCheck.normal_id)
      && (VertexIdx[loc_idx].UV_id == arg_elementCheck.UV_id))
    {
      break;
    }
  }
  return loc_idx;
}

ui32 cMeshT::CheckBufferCombination(glm::vec3 arg_position, glm::vec3 arg_normal, glm::vec2 arg_uv)
{
  ui32 loc_BufferSize = PositionBuffer.GetBufferSize();
  ui32 loc_bufferIdx;


  if (loc_BufferSize != NormalBuffer.GetBufferSize() || loc_BufferSize != UV_Buffer.GetBufferSize())
  {
    //TODO report error in buffer sizes
    return -1;
  }

  for (loc_bufferIdx = 0; loc_bufferIdx < loc_BufferSize; loc_bufferIdx++)
  {
    if((arg_position == PositionBuffer.GetElement(loc_bufferIdx)) &&
       (arg_normal == NormalBuffer.GetElement(loc_bufferIdx)) &&
       (arg_uv == UV_Buffer.GetElement(loc_bufferIdx)))
    {
      break;
    }
  }

  return loc_bufferIdx;
}





