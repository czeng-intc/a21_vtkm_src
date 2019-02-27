//============================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//
//  Copyright 2014 National Technology & Engineering Solutions of Sandia, LLC (NTESS).
//  Copyright 2014 UT-Battelle, LLC.
//  Copyright 2014 Los Alamos National Security.
//
//  Under the terms of Contract DE-NA0003525 with NTESS,
//  the U.S. Government retains certain rights in this software.
//
//  Under the terms of Contract DE-AC52-06NA25396 with Los Alamos National
//  Laboratory (LANL), the U.S. Government retains certain rights in
//  this software.
//============================================================================
#ifndef vtk_m_cont_Timer_h
#define vtk_m_cont_Timer_h

#include <vtkm/ListTag.h>
#include <vtkm/cont/DeviceAdapter.h>
#include <vtkm/cont/DeviceAdapterListTag.h>

#include <vtkm/cont/vtkm_cont_export.h>

namespace vtkm
{
namespace cont
{
namespace detail
{
struct TimerFunctor;
}
class EnabledDeviceTimerImpls;

/// A class that can be used to time operations in VTK-m that might be occuring
/// in parallel. Users are recommended to provide a device adapter at construction
/// time which matches the one being used to execute algorithms to ensure that thread
/// synchronization is correct and accurate.
/// If no device adapter is provided at construction time, the maximum
/// elapsed time of all enabled deivces will be returned. Normally cuda is expected to
/// have the longest execution time if enabled.
/// Per device adapter time query is also supported. It's useful when users want to reuse
/// the same timer to measure the cuda kernal call as well as the cuda device execution.
///
/// The there is no guaranteed resolution of the time but should generally be
/// good to about a millisecond.
///
class VTKM_CONT_EXPORT Timer
{
  friend struct detail::TimerFunctor;

public:
  VTKM_CONT
  Timer();

  VTKM_CONT Timer(vtkm::cont::DeviceAdapterId device);

  VTKM_CONT ~Timer();

  /// Resets the timer.
  VTKM_CONT void Reset();

  /// Start would call Reset function before starting the timer for convenience
  VTKM_CONT void Start();

  VTKM_CONT void Stop();

  VTKM_CONT bool Started();

  VTKM_CONT bool Stopped();

  /// Used to check if Timer has finished the synchronization to get the result from the device.
  VTKM_CONT bool Ready();

  /// Get the elapsed time measured by the given device adapter. If no device is
  /// specified, the max time of all device measurements will be returned.
  VTKM_CONT
  vtkm::Float64 GetElapsedTime(DeviceAdapterId id = DeviceAdapterTagAny());

private:
  VTKM_CONT void Init();
  /// Some timers are ill-defined when copied, so disallow that for all timers.
  VTKM_CONT Timer(const Timer&) = delete;
  VTKM_CONT void operator=(const Timer&) = delete;

  DeviceAdapterId Device;
  DeviceAdapterId DeviceForQuery;
  EnabledDeviceTimerImpls* Internal;
};
}
} // namespace vtkm::cont

#endif //vtk_m_cont_Timer_h
