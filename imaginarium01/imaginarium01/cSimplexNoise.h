/*
 * cSimplexNoise.h
 *
 *  Created on: 3. 3. 2017
 *      Author: GFreeman
 */

#ifndef CSIMPLEXNOISE_H_
#define CSIMPLEXNOISE_H_

#ifndef STDAFX_H
  #include "stdafx.h"
#endif



class cSimplexNoise
{
public:
  cSimplexNoise();
  ~cSimplexNoise();

  double noise(double xin, double yin);
  double noise(double xin, double yin, double zin);
  double noise(double x, double y, double z, double w);
private:
  static const si8 grad3[][3];

  static const si8 grad4[][4];

  static const ui8 perm[];

  static const ui8 simplex[][4];

  int fastfloor(double x) {return x>0 ? (int)x : (int)x-1;}

  double dot(const si8 g[], double x, double y) { return g[0]*x + g[1]*y; }

  double dot(const si8 g[], double x, double y, double z) { return g[0]*x + g[1]*y + g[2]*z; }

  double dot(const si8 g[], double x, double y, double z, double w) { return g[0]*x + g[1]*y + g[2]*z + g[3]*w; }



};



#endif /* CSIMPLEXNOISE_H_ */
