/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Measure plugins strings

*******************************************************************************************************/
#include <stdlib.h>
#include <stdint.h>

#include "PluginsString.h"


char pluginsString[ PLUGINS_STRING_SIZE ];
char measurePlanFilename[ MEASURE_PLAN_FILENAME_SIZE ];




// Get size of the 'pluginsString' 
int32_t GetSizeof_pluginsString( void )
{
    return sizeof( pluginsString );
}

// Get size of the 'pluginsString' element
int32_t GetSizeof_pluginsStringElement( void )
{
    return sizeof( pluginsString[ 0 ] );
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
