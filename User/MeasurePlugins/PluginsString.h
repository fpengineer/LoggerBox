/*****************************************************************************************************

    Plugins strings



*******************************************************************************************************/
#ifndef _PLUGINS_STRING_H_
#define _PLUGINS_STRING_H_

#include <stdint.h>

#define PLUGINS_STRING_SIZE         2000
#define MEASURE_PLAN_FILENAME_SIZE  100
#define MEASURE_DATA_FILENAME_SIZE  100

extern char pluginsTempString[];
extern char measurePlanFilename[];

/* Exported types ------------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/
int32_t GetSizeof_pluginsTempString( void );
int32_t GetSizeof_pluginsTempStringElement( void );
int32_t GetSizeof_measurePlanFilename( void );
int32_t GetSizeof_measurePlanFilenameElement( void );
void PrepareTimeString( char *timeString );

#endif /* _PLUGINS_STRING_H_ */
/* End of file */
