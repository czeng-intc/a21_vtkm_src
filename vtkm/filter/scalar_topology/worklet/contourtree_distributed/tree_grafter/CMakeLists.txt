##============================================================================
##  Copyright (c) Kitware, Inc.
##  All rights reserved.
##  See LICENSE.txt for details.
##
##  This software is distributed WITHOUT ANY WARRANTY; without even
##  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
##  PURPOSE.  See the above copyright notice for more information.
##============================================================================

set(headers
  GetHierarchicalIdsWorklet.h
  InitActiceSuperarcIdWorklet.h
  InitActiceSuperarcsWorklet.h
  GraftInteriorForestsSetTransferIterationWorklet.h
  FindCriticalPointsSetUpDownNeighboursWorklet.h
  FindCriticalPointsFindSaddlesWorklet.h
  FindCriticalPointsFindLeafsWorklet.h
  FindCriticalPointsFindTerminalElementsWorklet.h
  CollapseRegularChainsWorklet.h
  IdentifyLeafHyperarcsWorklet.h
  SuperarcWasNotTransferredPredicate.h
  NewHypernodePredicate.h
  HyperNodeWhenComparator.h
  SuperNodeWhenComparator.h
  NewNodePredicate.h
  ListNewNodesCopyIdsWorklet.h
  CopyNewHypernodesWorklet.h
  CopyNewSupernodesWorklet.h
  CopyNewSupernodesSetSuperchildrenWorklet.h
  PermuteComparator.h
  CopyNewNodesSetSuperparentsWorklet.h
  CopyFirstSupernodePerIterationWorklet.h
  CopyFirstHypernodePerIterationWorklet.h
  CalculateAttachementCounterWorklet.h
)

vtkm_declare_headers(${headers})
