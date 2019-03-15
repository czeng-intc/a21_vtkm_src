//============================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//
//  Copyright 2018 National Technology & Engineering Solutions of Sandia, LLC (NTESS).
//  Copyright 2018 UT-Battelle, LLC.
//  Copyright 2018 Los Alamos National Security.
//
//  Under the terms of Contract DE-NA0003525 with NTESS,
//  the U.S. Government retains certain rights in this software.
//
//  Under the terms of Contract DE-AC52-06NA25396 with Los Alamos National
//  Laboratory (LANL), the U.S. Government retains certain rights in
//  this software.
//============================================================================

#include <vtkm/cont/RuntimeDeviceInformation.h>
#include <vtkm/cont/RuntimeDeviceTracker.h>

#include <vtkm/cont/cuda/DeviceAdapterCuda.h>
#include <vtkm/cont/internal/DeviceAdapterError.h>
#include <vtkm/cont/openmp/DeviceAdapterOpenMP.h>
#include <vtkm/cont/serial/DeviceAdapterSerial.h>
#include <vtkm/cont/tbb/DeviceAdapterTBB.h>

#include <vtkm/cont/testing/Testing.h>

#include <cctype> //for tolower

namespace
{

// Invalid tag for testing. Returns the default "InvalidDeviceId" from
// vtkm::cont::RuntimeDeviceTracker::GetName.
struct VTKM_ALWAYS_EXPORT DeviceAdapterTagInvalidDeviceId : vtkm::cont::DeviceAdapterId
{
  constexpr DeviceAdapterTagInvalidDeviceId()
    : DeviceAdapterId(VTKM_MAX_DEVICE_ADAPTER_ID)
  {
  }
};

template <typename Tag>
void TestName(const std::string& name, Tag tag, vtkm::cont::DeviceAdapterId id)
{
  auto tracker = vtkm::cont::GetRuntimeDeviceTracker();

#if 0
  std::cerr << "Expected: " << name << "\n"
            << "\t" << id.GetName() << "\n"
            << "\t" << tag.GetName() << "\n"
            << "\t" << tracker.GetDeviceName(id) << "\n"
            << "\t" << tracker.GetDeviceName(tag) << "\n";
#endif
  VTKM_TEST_ASSERT(id.GetName() == name, "Id::GetName() failed.");
  VTKM_TEST_ASSERT(tag.GetName() == name, "Tag::GetName() failed.");
  VTKM_TEST_ASSERT(vtkm::cont::make_DeviceAdapterId(id.GetValue()) == id,
                   "make_DeviceAdapterId(int8) failed");

  VTKM_TEST_ASSERT(tracker.GetDeviceName(id) == name, "RTDeviceTracker::GetName(Id) failed.");
  VTKM_TEST_ASSERT(tracker.GetDeviceName(tag) == name, "RTDeviceTracker::GetName(Tag) failed.");

  //check going from name to device id
  auto lowerCaseFunc = [](char c) {
    return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
  };

  auto upperCaseFunc = [](char c) {
    return static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
  };

  if (id.IsValueValid())
  { //only test make_DeviceAdapterId with valid device ids
    VTKM_TEST_ASSERT(
      vtkm::cont::make_DeviceAdapterId(name) == id, "make_DeviceAdapterId(", name, ") failed");

    std::string casedName = name;
    std::transform(casedName.begin(), casedName.end(), casedName.begin(), lowerCaseFunc);
    VTKM_TEST_ASSERT(
      vtkm::cont::make_DeviceAdapterId(casedName) == id, "make_DeviceAdapterId(", name, ") failed");

    std::transform(casedName.begin(), casedName.end(), casedName.begin(), upperCaseFunc);
    VTKM_TEST_ASSERT(
      vtkm::cont::make_DeviceAdapterId(casedName) == id, "make_DeviceAdapterId(", name, ") failed");
  }
}

void TestNames()
{
  DeviceAdapterTagInvalidDeviceId invalidTag;
  vtkm::cont::DeviceAdapterTagError errorTag;
  vtkm::cont::DeviceAdapterTagUndefined undefinedTag;
  vtkm::cont::DeviceAdapterTagSerial serialTag;
  vtkm::cont::DeviceAdapterTagTBB tbbTag;
  vtkm::cont::DeviceAdapterTagOpenMP openmpTag;
  vtkm::cont::DeviceAdapterTagCuda cudaTag;

  TestName("InvalidDeviceId", invalidTag, invalidTag);
  TestName("Error", errorTag, errorTag);
  TestName("Undefined", undefinedTag, undefinedTag);
  TestName("Serial", serialTag, serialTag);
  TestName("TBB", tbbTag, tbbTag);
  TestName("OpenMP", openmpTag, openmpTag);
  TestName("Cuda", cudaTag, cudaTag);
}

} // end anon namespace

int UnitTestRuntimeDeviceNames(int argc, char* argv[])
{
  return vtkm::cont::testing::Testing::Run(TestNames, argc, argv);
}
