//============================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//============================================================================
#ifndef vtkm_m_worklet_Mask_h
#define vtkm_m_worklet_Mask_h

#include <vtkm/worklet/WorkletMapTopology.h>

#include <vtkm/cont/ArrayCopy.h>
#include <vtkm/cont/ArrayHandle.h>
#include <vtkm/cont/ArrayHandleCounting.h>
#include <vtkm/cont/ArrayHandlePermutation.h>
#include <vtkm/cont/CellSetPermutation.h>

namespace vtkm
{
namespace worklet
{

// Subselect points using stride for now, creating new cellset of vertices
class Mask
{
public:
  template <typename CellSetType>
  vtkm::cont::CellSetPermutation<CellSetType> Run(const CellSetType& cellSet, const vtkm::Id stride)
  {
    using OutputType = vtkm::cont::CellSetPermutation<CellSetType>;

    vtkm::Id numberOfInputCells = cellSet.GetNumberOfCells();
    vtkm::Id numberOfSampledCells = numberOfInputCells / stride;
    vtkm::cont::ArrayHandleCounting<vtkm::Id> strideArray(0, stride, numberOfSampledCells);

    vtkm::cont::ArrayCopy(strideArray, this->ValidCellIds);

    return OutputType(this->ValidCellIds, cellSet);
  }

  vtkm::cont::ArrayHandle<vtkm::Id> GetValidCellIds() const { return this->ValidCellIds; }

private:
  vtkm::cont::ArrayHandle<vtkm::Id> ValidCellIds;
};
}
} // namespace vtkm::worklet

#endif // vtkm_m_worklet_Mask_h
