//============================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//============================================================================

#ifndef vtk_m_worklet_CoordinateSystemTransform_h
#define vtk_m_worklet_CoordinateSystemTransform_h

#include <vtkm/Math.h>
#include <vtkm/worklet/WorkletMapField.h>

namespace vtkm
{
namespace worklet
{
struct CylToCar : public vtkm::worklet::WorkletMapField
{
  using ControlSignature = void(FieldIn, FieldOut);
  using ExecutionSignature = _2(_1);

  //Functor
  template <typename T>
  VTKM_EXEC vtkm::Vec<T, 3> operator()(const vtkm::Vec<T, 3>& vec) const
  {
    vtkm::Vec<T, 3> res(vec[0] * static_cast<T>(vtkm::Cos(vec[1])),
                        vec[0] * static_cast<T>(vtkm::Sin(vec[1])),
                        vec[2]);
    return res;
  }
};

struct CarToCyl : public vtkm::worklet::WorkletMapField
{
  using ControlSignature = void(FieldIn, FieldOut);
  using ExecutionSignature = _2(_1);

  //Functor
  template <typename T>
  VTKM_EXEC vtkm::Vec<T, 3> operator()(const vtkm::Vec<T, 3>& vec) const
  {
    T R = vtkm::Sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
    T Theta = 0;

    if (vec[0] == 0 && vec[1] == 0)
      Theta = 0;
    else if (vec[0] < 0)
      Theta = -vtkm::ASin(vec[1] / R) + static_cast<T>(vtkm::Pi());
    else
      Theta = vtkm::ASin(vec[1] / R);

    vtkm::Vec<T, 3> res(R, Theta, vec[2]);
    return res;
  }
};

struct SphereToCar : public vtkm::worklet::WorkletMapField
{
  using ControlSignature = void(FieldIn, FieldOut);
  using ExecutionSignature = _2(_1);

  //Functor
  template <typename T>
  VTKM_EXEC vtkm::Vec<T, 3> operator()(const vtkm::Vec<T, 3>& vec) const
  {
    T R = vec[0];
    T Theta = vec[1];
    T Phi = vec[2];

    T sinTheta = static_cast<T>(vtkm::Sin(Theta));
    T cosTheta = static_cast<T>(vtkm::Cos(Theta));
    T sinPhi = static_cast<T>(vtkm::Sin(Phi));
    T cosPhi = static_cast<T>(vtkm::Cos(Phi));

    T x = R * sinTheta * cosPhi;
    T y = R * sinTheta * sinPhi;
    T z = R * cosTheta;

    vtkm::Vec<T, 3> r(x, y, z);
    return r;
  }
};

struct CarToSphere : public vtkm::worklet::WorkletMapField
{
  using ControlSignature = void(FieldIn, FieldOut);
  using ExecutionSignature = _2(_1);

  //Functor
  template <typename T>
  VTKM_EXEC vtkm::Vec<T, 3> operator()(const vtkm::Vec<T, 3>& vec) const
  {
    T R = vtkm::Sqrt(vtkm::Dot(vec, vec));
    T Theta = 0;
    if (R > 0)
      Theta = vtkm::ACos(vec[2] / R);
    T Phi = vtkm::ATan2(vec[1], vec[0]);
    if (Phi < 0)
      Phi += static_cast<T>(vtkm::TwoPi());

    return vtkm::Vec<T, 3>(R, Theta, Phi);
  }
};
}
} // namespace vtkm::worklet

#endif // vtk_m_worklet_CoordinateSystemTransform_h
