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

#include "vtkSaveOFFieldFilter.h"

#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkCellData.h"
#include "vtkPolyData.h"
#include "vtkImageData.h"
#include "vtkDataArray.h"
#include "vtkCellArray.h"
#include "vtkAppendPolyData.h"
#include "vtkMath.h"
#include "vtkDoubleArray.h"
#include "vtkIdTypeArray.h"

#include "vtkCompositeDataIterator.h"
#include "vtkSelectEnclosedPoints.h"
#include "vtkSmartPointer.h"

#include "FieldTemplate.h"

vtkStandardNewMacro(vtkSaveOFFieldFilter);

vtkSaveOFFieldFilter::vtkSaveOFFieldFilter() :
    fieldName( NULL ),
    filePath( NULL ),
    dimensionString( NULL )
{
    this->SetNumberOfInputPorts(1);
}

vtkSaveOFFieldFilter::~vtkSaveOFFieldFilter()
{
}

int vtkSaveOFFieldFilter::FillInputPortInformation
(
  int               port,
  vtkInformation*   info
)
{
    info->Remove( vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE() );
    info->Set( vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkDataSet" );

    return 1;
}


int vtkSaveOFFieldFilter::RequestData
(
  vtkInformation        *vtkNotUsed(request),
  vtkInformationVector  **inputVector,
  vtkInformationVector  *outputVector
  )
{
    // get the information objects
    vtkSmartPointer<vtkInformation> inInfo( inputVector[0]->GetInformationObject(0) );
    vtkSmartPointer<vtkInformation> outInfo( outputVector->GetInformationObject(0) );

    std::cout << filePath << std::endl;
    std::cout << fieldName << std::endl;
    std::cout << dimensionString << std::endl;


    // get the plugin settings
    std::string path( filePath );
    std::string nameOfField( fieldName );
    std::string dimensionVector( dimensionString );

    if( path.empty() )
    {
        path.append( "./" );
    }

    // get the input and output
    vtkSmartPointer<vtkDataSet> field( vtkDataSet::SafeDownCast( inInfo->Get(vtkDataSet::DATA_OBJECT()) ) );
    vtkSmartPointer<vtkDataSet> output( vtkDataSet::SafeDownCast( outInfo->Get(vtkDataSet::DATA_OBJECT()) ) );

    // pass the values through as we do not want to modify the data, just save it
    output->DeepCopy( field );

    // open template file for writing
    //FieldTemplate templ( vtkSaveOFFieldFilter::PATH_TEMPLATE );
    FieldTemplate templ;

    vtkSmartPointer<vtkCellData> fieldCD( field->GetCellData() );
    // proceed only, if the field has cell-data
    if( fieldCD->GetNumberOfArrays() > 0)
    {
        // retrieve the data-points              // use can select which array to save via the StringProperty 'SelectInputArray'
        vtkSmartPointer<vtkDataArray> fieldData( this->GetInputArrayToProcess( 0, inputVector ) );

                                // note that we do not get the number
                                // of tuples & components from the
                                // 'field' which would also be possible
                                // but from the fieldData itself
                                // otherwise numberOfComponents would be
                                // the sum of components of all
                                // fieldData-arrays, e.g. 10 in case
                                // of one 9-element tensor-field and
                                // one 1-element scalar-field
        vtkIdType numOfTuples  = fieldData->GetNumberOfTuples();
        int componentsPerValue = fieldData->GetNumberOfComponents();

        templ.setFieldType( componentsPerValue );
        templ.setNumValues( numOfTuples );
        templ.setFieldName( nameOfField );          // default values will
        templ.setDimensionString( dimensionVector );// be used if name &
                                                    // dims empty
        templ.prepareWritingToFile( path );

        double tensor[ componentsPerValue ];
        for( vtkIdType t = 0; t < numOfTuples; )
        {
            fieldData->GetTuple( t, tensor );
            t = templ.appendFieldValue( tensor, componentsPerValue ) ? t+1 : numOfTuples;
        }

        templ.finalizeFile();
    }
    else
    {
        vtkErrorMacro(<<"The input fields does not conatin any cell-data. Convert point-data first!");
    }

    return 1;
}

void vtkSaveOFFieldFilter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
