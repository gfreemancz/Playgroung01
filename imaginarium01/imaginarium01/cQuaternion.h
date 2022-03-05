#pragma once
#include "glm\vec3.hpp"
#include <math.h> 


class cQuaternion
{
public:
   double x, y, z, w;

   cQuaternion() : x(0), y(0), z(0), w(1) {}
   cQuaternion(double arg_x, double arg_y, double arg_z, double arg_w) : x(arg_x), y(arg_y), z(arg_z), w(arg_w) {}
   cQuaternion(glm::vec3 arg_axis, double arg_angle);
   cQuaternion(cQuaternion& ag_in);

   double lenght(void);
   void normalize(void);

   cQuaternion operator * (cQuaternion const& arg_obj);
   cQuaternion operator + (cQuaternion const& arg_obj);
   cQuaternion operator ! (void);

};

