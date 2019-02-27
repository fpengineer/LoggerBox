/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Measure plugins strings

*******************************************************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "PluginsString.h"


char pluginsTempString[ PLUGINS_STRING_SIZE ];
char measurePlanFilename[ MEASURE_PLAN_FILENAME_SIZE ];




// Get size of the 'pluginsTempString' 
int32_t GetSizeof_pluginsTempString( void )
{
    return sizeof( pluginsTempString );
}

// Get size of the 'pluginsTempString' element
int32_t GetSizeof_pluginsTempStringElement( void )
{
    return sizeof( pluginsTempString[ 0 ] );
}

// Get size of the 'measurePlanFilename' 
int32_t GetSizeof_measurePlanFilename( void )
{
    return sizeof( measurePlanFilename );
}

// Get size of the 'measurePlanFilename' element
int32_t GetSizeof_measurePlanFilenameElement( void )
{
    return sizeof( measurePlanFilename[ 0 ] );
}


void PrepareTimeString( char *timeString )
{
    char *token = NULL;
    
    token = strchr( timeString, ' ' );
	while ( token != NULL )
	{
		*token = '_';
	    token = strchr( token + 1, ' ' );
	}

    token = strchr( timeString, ':' );
	while ( token != NULL )
	{
		*token = '.';
	    token = strchr( token + 1, ':' );
	}
}


/* End of file */
