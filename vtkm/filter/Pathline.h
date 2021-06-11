//============================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//============================================================================

#ifndef vtk_m_filter_Pathline_h
#define vtk_m_filter_Pathline_h

#include <vtkm/filter/FilterTemporalParticleAdvection.h>

namespace vtkm
{
namespace filter
{
/// \brief generate streamlines from a vector field.

/// Takes as input a vector field and seed locations and generates the
/// paths taken by the seeds through the vector field.
class Pathline : public vtkm::filter::FilterTemporalParticleAdvection<Pathline>
{
public:
  VTKM_CONT
  Pathline();

  template <typename DerivedPolicy>
  vtkm::cont::PartitionedDataSet PrepareForExecution(
    const vtkm::cont::PartitionedDataSet& input,
    const vtkm::filter::PolicyBase<DerivedPolicy>& policy);

protected:
private:
};

}
} // namespace vtkm::filter

#ifndef vtk_m_filter_Pathline_hxx
#include <vtkm/filter/Pathline.hxx>
#endif

#endif // vtk_m_filter_Pathline_h
