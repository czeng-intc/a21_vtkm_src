//============================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//
//  Copyright 2014 Sandia Corporation.
//  Copyright 2014 UT-Battelle, LLC.
//  Copyright 2014 Los Alamos National Security.
//
//  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
//  the U.S. Government retains certain rights in this software.
//
//  Under the terms of Contract DE-AC52-06NA25396 with Los Alamos National
//  Laboratory (LANL), the U.S. Government retains certain rights in
//  this software.
//============================================================================


//This sets up testing with the default device adapter and array container
#include <vtkm/cont/DeviceAdapterSerial.h>
#include <vtkm/interop/testing/TestingOpenGLInterop.h>

int UnitTestTransferToOpenGL(int, char *[])
{
  return vtkm::interop::testing::TestingOpenGLInterop<
            vtkm::cont::DeviceAdapterTagSerial >::Run();
}