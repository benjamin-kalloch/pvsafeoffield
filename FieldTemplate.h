#ifndef FIELDTEMPLATE_H
#define FIELDTEMPLATE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

enum FieldType
{
    scalar,
    vector,
    tensor,
    notype
};

class FieldTemplate
{
public:
    FieldTemplate( );
    FieldTemplate( const std::string& );

    void setFieldType( FieldType );
    void setFieldType( size_t _numComponents );
    void setFieldName( std::string );
    void setFieldName( const char* );
    void setDimensionString( std::string );
    void setDimensionString( const char* );
    void setNumValues( size_t );


    void prepareWritingToFile( std::string );
    bool appendFieldValue( const double*, size_t );
    bool appendFieldValue( const std::string _value );
    void finalizeFile( );

    static constexpr const char* VERSION_STRING        = "4.0";
    static constexpr const char* DEFAULT_FIELD_NAME    = "field";
    static constexpr const char* DEFAULT_DIMENSION_VEC = "[0 0 0 0 0 0 0]";

    static constexpr const char* TOKEN_VERSION_STR     = "%VERSIONSTRING%";
    static constexpr const char* TOKEN_FIELD_NAME      = "%FIELDNAME%";
    static constexpr const char* TOKEN_FIELD_TYPE      = "%FIELDTYPE%";
    static constexpr const char* TOKEN_FIELD_ELEM_TYPE = "%FIELDELEMTYPE%";
    static constexpr const char* TOKEN_NUM_VALS        = "%NUMFIELDVALUES%";
    static constexpr const char* TOKEN_DIMENSION_VEC   = "%DIMENSIONVECTOR%";

    static constexpr const char* FIELDTYPE_SCALAR = "volScalarField";
    static constexpr const char* FIELDTYPE_VECTOR = "volVectorField";
    static constexpr const char* FIELDTYPE_TENSOR = "volTensorField";

    static constexpr const char* FIELDELEMTYPE_SCALAR = "scalar";
    static constexpr const char* FIELDELEMTYPE_VECTOR = "vector";
    static constexpr const char* FIELDELEMTYPE_TENSOR = "tensor";

private:
    bool readTemplateFile( const std::string& );
    void writeBufferContent();
    void writetoBuffer( const std::string& );


    bool replaceString( std::string&, const std::string&, const std::string & );
    bool replaceString( std::string&, const char*, const char* );
    bool replaceString( std::string&, const char*, const std::string& );
    bool replaceString( std::string&, const std::string&, const char*t );

    std::string mTemplateText;
    std::ofstream mOutFileHandle;

    std::string mFieldName;
    std::string mFieldType;
    std::string mFieldElemType;
    std::string mDimensionString;
    size_t mNumValues;
};


#endif /* FIELDTEMPLATE_H */
