#include "cQuaternion.h"

#include <glm/glm.hpp>


cQuaternion::cQuaternion(glm::vec3 arg_axis, double arg_angle)
{
  glm::vec3 loc_vec = glm::normalize(arg_axis);
  
  w = cos(arg_angle/2.0);
  x = loc_vec.x * sin(arg_angle / 2.0);
  y = loc_vec.y * sin(arg_angle / 2.0);
  z = loc_vec.z * sin(arg_angle / 2.0);
}

cQuaternion::cQuaternion(cQuaternion& ag_in)
{
  w = ag_in.w;
  x = ag_in.x;
  y = ag_in.y;
  z = ag_in.z;
}

double cQuaternion::lenght(void)
{
  return sqrt(x*x+y*y+z*z+w*w);
}

void cQuaternion::normalize(void)
{
  const double L = lenght();
  x /= L;
  y /= L;
  z /= L;
  w /= L;
}

cQuaternion cQuaternion::operator*(cQuaternion const& arg_obj)
{
 double new_w = (w * arg_obj.w) - (x * arg_obj.x) - (y * arg_obj.y) - (z * arg_obj.z);
 double new_x = (w * arg_obj.x) + (x * arg_obj.w) + (y * arg_obj.z) + (z * arg_obj.y);
 double new_y = (w * arg_obj.y) + (x * arg_obj.z) + (y * arg_obj.w) + (z * arg_obj.x);
 double new_z = (w * arg_obj.z) + (x * arg_obj.y) + (y * arg_obj.x) + (z * arg_obj.w);
 
  return cQuaternion(new_x, new_y, new_z, new_w);
}

cQuaternion cQuaternion::operator+(cQuaternion const& arg_obj)
{
  const double new_w = w + arg_obj.w;
  const double new_x = x + arg_obj.x;
  const double new_y = y + arg_obj.y;
  const double new_z = z + arg_obj.z;
  return cQuaternion();
}

//cQuaternion cQuaternion::operator!(void)
//{
//  const double loc_squaresum = (w * w) + (x * x) + (y * y) + (z * z);
//  return cQuaternion(w/ loc_squaresum, x / loc_squaresum, y / loc_squaresum, z / loc_squaresum);
//}




cQuaternion cQuaternion::operator!(void)
{
  const double loc_SquareSumInv = 1 / ((w * w) + (x * x) + (y * y) + (z * z));
  return cQuaternion(w * loc_SquareSumInv, x * loc_SquareSumInv, y * loc_SquareSumInv, z * loc_SquareSumInv);
}