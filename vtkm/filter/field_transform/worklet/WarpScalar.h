//============================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//============================================================================

#ifndef vtk_m_worklet_WarpScalar_h
#define vtk_m_worklet_WarpScalar_h

#include <vtkm/worklet/WorkletMapField.h>

namespace vtkm
{
namespace worklet
{
// A functor that modify points by moving points along point normals by the scalar
// amount times the scalar factor. It's a VTK-m version of the vtkWarpScalar in VTK.
// Useful for creating carpet or x-y-z plots.
// It doesn't modify the point coordinates, but creates a new point coordinates
// that have been warped.
class WarpScalar : public vtkm::worklet::WorkletMapField
{
public:
  using ControlSignature = void(FieldIn, FieldIn, FieldIn, FieldOut);
  using ExecutionSignature = void(_1, _2, _3, _4);
  VTKM_CONT
  explicit WarpScalar(vtkm::FloatDefault scaleAmount)
    : ScaleAmount(scaleAmount)
  {
  }

  VTKM_EXEC
  void operator()(const vtkm::Vec3f& point,
                  const vtkm::Vec3f& normal,
                  const vtkm::FloatDefault& scaleFactor,
                  vtkm::Vec3f& result) const
  {
    result = point + this->ScaleAmount * scaleFactor * normal;
  }

  template <typename T1, typename T2, typename T3>
  VTKM_EXEC void operator()(const vtkm::Vec<T1, 3>& point,
                            const vtkm::Vec<T2, 3>& normal,
                            const T3& scaleFactor,
                            vtkm::Vec<T1, 3>& result) const
  {
    result = point + static_cast<T1>(this->ScaleAmount * scaleFactor) * normal;
  }

private:
  vtkm::FloatDefault ScaleAmount;
};
}
} // namespace vtkm::worklet

#endif // vtk_m_worklet_WarpScalar_h
