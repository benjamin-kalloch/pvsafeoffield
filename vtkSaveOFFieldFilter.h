/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile$

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

// .NAME vtkSaveOFFieldFilter - mask a tensor field according to a scalar field

// .SECTION Description
// A Class to mask a tensor field according to the iso values in a
// provided scalar field. Both fields need to be defined on the same
// domain.

// .SECTION Thanks
// noone

#ifndef vtkSaveOFFieldFilter_h
#define vtkSaveOFFieldFilter_h

#include "vtkDataSetAlgorithm.h"

class vtkSaveOFFieldFilter : public vtkDataSetAlgorithm
{
public:
  vtkGetStringMacro( filePath );
  vtkSetStringMacro( filePath );
  vtkGetStringMacro( fieldName );
  vtkSetStringMacro( fieldName );
  vtkGetStringMacro( dimensionString );
  vtkSetStringMacro( dimensionString );

  vtkTypeMacro(vtkSaveOFFieldFilter, vtkDataSetAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);
  static vtkSaveOFFieldFilter *New();
                                                // I did not find a better solution to include rssource files so far.... -.-
  static constexpr const char* PATH_TEMPLATE = "/home/kalloch/OpenFOAM/kalloch-3.0.1/additional_stuff/PVCustomClasses/FieldTemplate/template";
  static constexpr const char* PATH_WORKDIR  = "/home/kalloch/OpenFOAM/kalloch-3.0.1/additional_stuff/PVSaveOFField/";

protected:
  vtkSaveOFFieldFilter();
  ~vtkSaveOFFieldFilter();

  /* implementation of algorithm */
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  virtual int FillInputPortInformation(int port, vtkInformation* info);

protected:
  char* filePath;
  char* fieldName;
  char* dimensionString;

private:
  vtkSaveOFFieldFilter(const vtkSaveOFFieldFilter&);  // Not implemented.
  void operator=(const vtkSaveOFFieldFilter&);  // Not implemented.
};

#endif
