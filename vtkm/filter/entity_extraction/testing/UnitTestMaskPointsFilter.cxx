//============================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//============================================================================

#include <vtkm/cont/testing/MakeTestDataSet.h>
#include <vtkm/cont/testing/Testing.h>

#include <vtkm/filter/entity_extraction/MaskPoints.h>

using vtkm::cont::testing::MakeTestDataSet;

namespace
{

class TestingMaskPoints
{
public:
  static void TestRegular2D()
  {
    std::cout << "Testing mask points on 2D regular dataset" << std::endl;
    vtkm::cont::DataSet dataset = MakeTestDataSet().Make2DUniformDataSet1();

    vtkm::filter::entity_extraction::MaskPoints maskPoints;
    maskPoints.SetStride(2);
    maskPoints.SetFieldsToPass("pointvar");
    vtkm::cont::DataSet output = maskPoints.Execute(dataset);
    VTKM_TEST_ASSERT(test_equal(output.GetNumberOfCells(), 12),
                     "Wrong number of cells for MaskPoints");
    VTKM_TEST_ASSERT(test_equal(output.GetField("pointvar").GetNumberOfValues(), 12),
                     "Wrong number of points for MaskPoints");
  }

  static void TestRegular3D()
  {
    std::cout << "Testing mask points on 3D regular dataset" << std::endl;
    vtkm::cont::DataSet dataset = MakeTestDataSet().Make3DUniformDataSet1();

    vtkm::filter::entity_extraction::MaskPoints maskPoints;
    maskPoints.SetStride(5);
    maskPoints.SetFieldsToPass("pointvar");
    vtkm::cont::DataSet output = maskPoints.Execute(dataset);
    VTKM_TEST_ASSERT(test_equal(output.GetNumberOfCells(), 25),
                     "Wrong number of cells for MaskPoints");
    VTKM_TEST_ASSERT(test_equal(output.GetField("pointvar").GetNumberOfValues(), 25),
                     "Wrong number of points for MaskPoints");
  }

  static void TestExplicit3D()
  {
    std::cout << "Testing mask points on 3D explicit dataset" << std::endl;
    vtkm::cont::DataSet dataset = MakeTestDataSet().Make3DExplicitDataSet5();

    vtkm::filter::entity_extraction::MaskPoints maskPoints;
    maskPoints.SetStride(3);
    maskPoints.SetCompactPoints(false);
    maskPoints.SetFieldsToPass("pointvar");
    vtkm::cont::DataSet output = maskPoints.Execute(dataset);
    VTKM_TEST_ASSERT(test_equal(output.GetNumberOfCells(), 3),
                     "Wrong number of cells for MaskPoints");
    VTKM_TEST_ASSERT(test_equal(output.GetField("pointvar").GetNumberOfValues(), 11),
                     "Wrong number of points for MaskPoints");
  }

  void operator()() const
  {
    TestingMaskPoints::TestRegular2D();
    TestingMaskPoints::TestRegular3D();
    TestingMaskPoints::TestExplicit3D();
  }
};
}

int UnitTestMaskPointsFilter(int argc, char* argv[])
{
  return vtkm::cont::testing::Testing::Run(TestingMaskPoints(), argc, argv);
}
