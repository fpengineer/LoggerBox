/*****************************************************************************************************

    Plugins strings



*******************************************************************************************************/
#ifndef _PLUGINS_STRING_H_
#define _PLUGINS_STRING_H_

#include <stdint.h>

#define PLUGINS_STRING_SIZE         2000
#define MEASURE_PLAN_FILENAME_SIZE  100

/* Exported types ------------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/
int32_t GetSizeof_pluginsString( void );
int32_t GetSizeof_measurePlanFilename( void );
int32_t GetSizeof_pluginsStringElement( void );
int32_t GetSizeof_measurePlanFilenameElement( void );

#endif /* _PLUGINS_STRING_H_ */
/* End of file */
