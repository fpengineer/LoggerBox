/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Measure plugins strings

*******************************************************************************************************/
#include <stdlib.h>
#include <stdint.h>

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
/* End of file */
