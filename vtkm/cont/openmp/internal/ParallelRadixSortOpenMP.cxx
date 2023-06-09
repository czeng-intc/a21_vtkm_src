//============================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//============================================================================

#include <vtkm/cont/internal/ParallelRadixSort.h>

#include <vtkm/cont/RuntimeDeviceInformation.h>
#include <vtkm/cont/openmp/internal/DeviceAdapterTagOpenMP.h>

#include <omp.h>

namespace vtkm
{
namespace cont
{
namespace openmp
{
namespace sort
{
namespace radix
{

struct RadixThreaderOpenMP
{
  size_t GetAvailableCores() const
  {
    vtkm::Id result;
    vtkm::cont::RuntimeDeviceInformation{}
      .GetRuntimeConfiguration(vtkm::cont::DeviceAdapterTagOpenMP())
      .GetThreads(result);
    return static_cast<size_t>(result);
  }

  template <typename TaskType>
  void RunParentTask(TaskType task) const
  {
    assert(!omp_in_parallel());
#pragma omp parallel default(none) shared(task)
    {
#pragma omp single
      {
        task();
      }
    } // Implied barrier ensures that child tasks will finish.
  }

  template <typename TaskType, typename ThreadData>
  void RunChildTasks(ThreadData, TaskType left, TaskType right) const
  {
    assert(omp_in_parallel());
#pragma omp task default(none) firstprivate(right)
    {
      right();
    }

    // Execute the left task in the existing thread.
    left();
  }
};

VTKM_INSTANTIATE_RADIX_SORT_FOR_THREADER(RadixThreaderOpenMP)
}
} // end namespace sort::radix
}
}
} // end namespace vtkm::cont::openmp
