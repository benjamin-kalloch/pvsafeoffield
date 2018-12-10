#include "FieldTemplate.h"
#include "TemplateString.h"

//////////
// We now directly take the template text from a header file.
// No reading of a template file is needed anymore...
//
FieldTemplate::FieldTemplate( ) :
    mFieldName( FieldTemplate::DEFAULT_FIELD_NAME ),
    mDimensionString( FieldTemplate::DEFAULT_DIMENSION_VEC ),
    mTemplateText( getTemplateText() ) // 'getTemplateText' from 'TemplateString.h'
{
    while( replaceString( mTemplateText, FieldTemplate::TOKEN_VERSION_STR, FieldTemplate::VERSION_STRING ) );
}


bool FieldTemplate::readTemplateFile( const std::string &_path )
{
    std::ifstream file( _path );

    if( ! file.fail() )
    {
        std::string line;
        while( std::getline( file,  line ) )
        {
            mTemplateText.append( line );
            mTemplateText.push_back( '\n' );
        }
        return true;
    }
    else
    {
        std::cout << "There was an error when trying to read the template file at '" << _path << "'" << std::endl;
    }

    return false;
}
////////

void FieldTemplate::prepareWritingToFile( std::string _directory )
{
    _directory.append( "/" );
    _directory.append( mFieldName );

    mOutFileHandle.open( _directory, std::ofstream::out | std::ofstream::app );

    mOutFileHandle << mTemplateText;
}

bool FieldTemplate::appendFieldValue( const double* _values, size_t numComponents )
{
    std::stringstream line;
    switch( numComponents )
    {
        case 1:
            line << _values[0];
        break;

        case 2:
        case 3:
        case 6:
        case 9:
            line << "( ";
            for( unsigned char n = 0; n < numComponents; n++ )
                line << _values[ n ] << " ";
            line << ")";
        break;

        default:
            std::cout << "Unsupported number of components! Field cannot be written" << std::endl;
            return false;
    };

    return appendFieldValue( line.str() );
}

bool FieldTemplate::appendFieldValue( const std::string _value )
{
    if( mOutFileHandle.is_open() )
    {
        mOutFileHandle << _value << std::endl;
    }
    else
    {
        std::cout << "ERROR: FieldTemplate is not associated to its output-file."
                  << " Make sure to call 'prepareWritingToFile' before attempting to append any values."
                  << std::endl;
        return false;
    }

    return true;
}

void FieldTemplate::finalizeFile( )
{
    mOutFileHandle << ");";
    mOutFileHandle.close();
}

void FieldTemplate::setFieldType( FieldType _type )
{
    switch( _type )
    {
        case scalar:
            mFieldType = FieldTemplate::FIELDTYPE_SCALAR;
            mFieldElemType = FieldTemplate::FIELDELEMTYPE_SCALAR;
        break;

        case vector:
            mFieldType = FieldTemplate::FIELDTYPE_VECTOR;
            mFieldElemType = FieldTemplate::FIELDELEMTYPE_VECTOR;
        break;

        case tensor:
            mFieldType = FieldTemplate::FIELDTYPE_TENSOR;
            mFieldElemType = FieldTemplate::FIELDELEMTYPE_TENSOR;
        break;

        default:
            std::cout << "Invalid field type provided!" << std::endl;
            mFieldType.clear();
            mFieldElemType.clear();
    }

    while( replaceString( mTemplateText, FieldTemplate::TOKEN_FIELD_TYPE, mFieldType ) );
    while( replaceString( mTemplateText, FieldTemplate::TOKEN_FIELD_ELEM_TYPE, mFieldElemType ) );
}

void FieldTemplate::setFieldType( size_t _numComponents )
{
    FieldType type;

    switch( _numComponents )
    {
        case 1:
            type = scalar;
        break;

        case 3:
            type = vector;
        break;

        case 6:
        case 9:
            type = tensor;
        break;

        default:
            type = notype;
    }

    std::cout << "NumComponents: " << _numComponents << std::endl;

    setFieldType( type );
}

void FieldTemplate::setFieldName( std::string _name  )
{
    if( !_name.empty() ) mFieldName = _name;

    while( replaceString( mTemplateText, FieldTemplate::TOKEN_FIELD_NAME, mFieldName ) );
}

void FieldTemplate::setFieldName( const char* _name )
{
    std::string name( _name );
    setFieldName( name ) ;
}

void FieldTemplate::setNumValues( size_t _numValues )
{
    mNumValues = _numValues;

    std::string num( std::to_string( mNumValues ) );
    while( replaceString( mTemplateText, FieldTemplate::TOKEN_NUM_VALS, num ) );
}

void FieldTemplate::setDimensionString( const char* _dims )
{
    std::string dims( _dims );
    setDimensionString( dims );
}

void FieldTemplate::setDimensionString( std::string _dims )
{
    if( !_dims.empty() ) mDimensionString = _dims;

    while( replaceString( mTemplateText, FieldTemplate::TOKEN_DIMENSION_VEC, mDimensionString ) );
}

bool FieldTemplate::replaceString( std::string &_text, const char* _toBeReplaced, const char* _replacement )
{
    std::string toBeReplaced( _toBeReplaced );
    std::string replacement( _replacement );

    return replaceString( _text, toBeReplaced, replacement );
}

bool FieldTemplate::replaceString( std::string &_text, const char* _toBeReplaced, const std::string &_replacement )
{
    std::string toBeReplaced( _toBeReplaced );

    return replaceString( _text, toBeReplaced, _replacement );
}


bool FieldTemplate::replaceString( std::string &_text, const std::string &_toBeReplaced, const char* _replacement )
{
    std::string replacement( _replacement );

    return replaceString( _text, _toBeReplaced, replacement );
}

bool FieldTemplate::replaceString( std::string &_text, const std::string &_toBeReplaced, const std::string &_replacement )
{
    size_t startPos = _text.find( _toBeReplaced, 0 );

    bool tokenInText = (startPos != std::string::npos);

    if( tokenInText )
    {
        _text.replace( startPos, _toBeReplaced.size(), _replacement );
    }

    // if the token was present, we have to skim through the file at
    // least once again to check whether there are further tokens
    // of this kind, so we return true
    return tokenInText;
}
