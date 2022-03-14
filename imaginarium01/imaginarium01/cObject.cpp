#include "cObject.h"

glm::mat4x4 cObject::GetModelTransformaMatrix(void)
{
  glm::mat4x4 loc_ReturnMatrix(1.0f);

  loc_ReturnMatrix = glm::rotate(loc_ReturnMatrix, Rotation.x, glm::vec3(1, 0, 0));
  loc_ReturnMatrix = glm::rotate(loc_ReturnMatrix, Rotation.y, glm::vec3(0, 1, 0));
  loc_ReturnMatrix = glm::rotate(loc_ReturnMatrix, Rotation.z, glm::vec3(0, 0, 1));
  loc_ReturnMatrix = glm::translate(loc_ReturnMatrix, Position);

  return glm::mat4x4();
}

void cObject::SetPosition(glm::vec3 arg_Position)
{
  Position = arg_Position;
}

void cObject::SetRotation(glm::vec3 arg_Rotation)
{
  Rotation = arg_Rotation;
}

void cObject::LinkTexture(cTexture* arg_TexturePtr)
{
  pTexture = arg_TexturePtr;
}
