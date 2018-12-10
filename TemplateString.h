#include <string>
#include <ostream>
#include <iostream>

std::string getTemplateText()
{
	std::ostringstream text;

	text << "/*--------------------------------*- C++ -*----------------------------------*\\" << std::endl;
	text << "| =========                 |                                                 |"  << std::endl;
	text << "| \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |"  << std::endl;
	text << "|  \\    /   O peration     | Version:  %VERSIONSTRING%                                   |" << std::endl;
	text << "|   \\  /    A nd           | Web:      www.OpenFOAM.org                      |"	<< std::endl;
	text << "|    \\/     M anipulation  |                                                 |"	<< std::endl;
	text << "\\*---------------------------------------------------------------------------*/"	<< std::endl;
	text << "FoamFile"	<< std::endl;
	text << "{"	<< std::endl;
	text << "    version     2.0;"	<< std::endl;
	text << "    format      ascii;"	<< std::endl;
	text << "    class       %FIELDTYPE%"	<< std::endl;
	text << "    location    '0';"	<< std::endl;
	text << "    object      %FIELDNAME%;"	<< std::endl;
	text << "}"	<< std::endl;
	text << "// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //"	<< std::endl;
	text << ""	<< std::endl;
	text << "dimensions      %DIMENSIONVECTOR%;"	<< std::endl;
	text << ""	<< std::endl;
	text << "internalField   nonuniform List<%FIELDELEMTYPE%>"	<< std::endl;
	text << "%NUMFIELDVALUES%"	<< std::endl;
	text << "("	<< std::endl;


	return text.str();
}
