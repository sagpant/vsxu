//****************************************************************************//
// coremesh.h                                                                 //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_COREMESH_H
#define CAL_COREMESH_H


#include "cal3d/global.h"


class CalCoreSubmesh;


class CAL3D_API CalCoreMesh
{
public:
  CalCoreMesh();
  ~CalCoreMesh();

  int addCoreSubmesh(CalCoreSubmesh *pCoreSubmesh);
  CalCoreSubmesh *getCoreSubmesh(int id);
  int getCoreSubmeshCount();
  std::vector<CalCoreSubmesh *>& getVectorCoreSubmesh();
  int addAsMorphTarget(CalCoreMesh *pCoreMesh);
  void scale(float factor);
  void setFilename(const std::string& filename);
  const std::string& getFilename(void);
  void setName(const std::string& name);
  const std::string& getName(void);
  void incRef();
  bool decRef();  

private:
  std::vector<CalCoreSubmesh *> m_vectorCoreSubmesh;
  std::string m_name;
  std::string m_filename;
  int m_referenceCount;
};

#endif
