/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Measure plugins list

*******************************************************************************************************/
#include <stdlib.h>
#include <stdint.h>

#include "PluginsList.h"


const char *pluginsList[] = {    
#ifdef PLUGIN_0
    PLUGIN_0_NAME,
#endif
#ifdef PLUGIN_1
    PLUGIN_1_NAME,
#endif
#ifdef PLUGIN_2
    PLUGIN_2_NAME,
#endif
#ifdef PLUGIN_3
    PLUGIN_3_NAME,
#endif
#ifdef PLUGIN_4
    PLUGIN_4_NAME,
#endif
#ifdef PLUGIN_5
    PLUGIN_5_NAME,
#endif
#ifdef PLUGIN_6
    PLUGIN_6_NAME,
#endif
#ifdef PLUGIN_7
    PLUGIN_7_NAME,
#endif
#ifdef PLUGIN_8
    PLUGIN_8_NAME,
#endif
#ifdef PLUGIN_9
    PLUGIN_9_NAME,
#endif
#ifdef PLUGIN_10
    PLUGIN_10_NAME,
#endif
#ifdef PLUGIN_11
    PLUGIN_11_NAME,
#endif
#ifdef PLUGIN_12
    PLUGIN_12_NAME,
#endif
#ifdef PLUGIN_13
    PLUGIN_13_NAME,
#endif
#ifdef PLUGIN_14
    PLUGIN_14_NAME,
#endif
#ifdef PLUGIN_15
    PLUGIN_15_NAME,
#endif
#ifdef PLUGIN_16
    PLUGIN_16_NAME,
#endif
#ifdef PLUGIN_17
    PLUGIN_17_NAME,
#endif
#ifdef PLUGIN_18
    PLUGIN_18_NAME,
#endif
#ifdef PLUGIN_19
    PLUGIN_19_NAME,
#endif
#ifdef PLUGIN_20
    PLUGIN_20_NAME,
#endif
#ifdef PLUGIN_21
    PLUGIN_21_NAME,
#endif
#ifdef PLUGIN_22
    PLUGIN_22_NAME,
#endif
#ifdef PLUGIN_23
    PLUGIN_23_NAME,
#endif
#ifdef PLUGIN_24
    PLUGIN_24_NAME,
#endif
#ifdef PLUGIN_25
    PLUGIN_25_NAME,
#endif
#ifdef PLUGIN_26
    PLUGIN_26_NAME,
#endif
#ifdef PLUGIN_27
    PLUGIN_27_NAME,
#endif
#ifdef PLUGIN_28
    PLUGIN_28_NAME,
#endif
#ifdef PLUGIN_29
    PLUGIN_29_NAME,
#endif
#ifdef PLUGIN_30
    PLUGIN_30_NAME,
#endif
#ifdef PLUGIN_31
    PLUGIN_31_NAME,
#endif
#ifdef PLUGIN_32
    PLUGIN_32_NAME,
#endif
#ifdef PLUGIN_33
    PLUGIN_33_NAME,
#endif
#ifdef PLUGIN_34
    PLUGIN_34_NAME,
#endif
#ifdef PLUGIN_35
    PLUGIN_35_NAME,
#endif
#ifdef PLUGIN_36
    PLUGIN_36_NAME,
#endif
#ifdef PLUGIN_37
    PLUGIN_37_NAME,
#endif
#ifdef PLUGIN_38
    PLUGIN_38_NAME,
#endif
#ifdef PLUGIN_39
    PLUGIN_39_NAME,
#endif
#ifdef PLUGIN_40
    PLUGIN_40_NAME,
#endif
#ifdef PLUGIN_41
    PLUGIN_41_NAME,
#endif
#ifdef PLUGIN_42
    PLUGIN_42_NAME,
#endif
#ifdef PLUGIN_43
    PLUGIN_43_NAME,
#endif
#ifdef PLUGIN_44
    PLUGIN_44_NAME,
#endif
#ifdef PLUGIN_45
    PLUGIN_45_NAME,
#endif
#ifdef PLUGIN_46
    PLUGIN_46_NAME,
#endif
#ifdef PLUGIN_47
    PLUGIN_47_NAME,
#endif
#ifdef PLUGIN_48
    PLUGIN_48_NAME,
#endif
#ifdef PLUGIN_49
    PLUGIN_49_NAME,
#endif
#ifdef PLUGIN_50
    PLUGIN_50_NAME,
#endif
#ifdef PLUGIN_51
    PLUGIN_51_NAME,
#endif
#ifdef PLUGIN_52
    PLUGIN_52_NAME,
#endif
#ifdef PLUGIN_53
    PLUGIN_53_NAME,
#endif
#ifdef PLUGIN_54
    PLUGIN_54_NAME,
#endif
#ifdef PLUGIN_55
    PLUGIN_55_NAME,
#endif
#ifdef PLUGIN_56
    PLUGIN_56_NAME,
#endif
#ifdef PLUGIN_57
    PLUGIN_57_NAME,
#endif
#ifdef PLUGIN_58
    PLUGIN_58_NAME,
#endif
#ifdef PLUGIN_59
    PLUGIN_59_NAME,
#endif
#ifdef PLUGIN_60
    PLUGIN_60_NAME,
#endif
#ifdef PLUGIN_61
    PLUGIN_61_NAME,
#endif
#ifdef PLUGIN_62
    PLUGIN_62_NAME,
#endif
#ifdef PLUGIN_63
    PLUGIN_63_NAME,
#endif
#ifdef PLUGIN_64
    PLUGIN_64_NAME,
#endif
#ifdef PLUGIN_65
    PLUGIN_65_NAME,
#endif
#ifdef PLUGIN_66
    PLUGIN_66_NAME,
#endif
#ifdef PLUGIN_67
    PLUGIN_67_NAME,
#endif
#ifdef PLUGIN_68
    PLUGIN_68_NAME,
#endif
#ifdef PLUGIN_69
    PLUGIN_69_NAME,
#endif
#ifdef PLUGIN_70
    PLUGIN_70_NAME,
#endif
#ifdef PLUGIN_71
    PLUGIN_71_NAME,
#endif
#ifdef PLUGIN_72
    PLUGIN_72_NAME,
#endif
#ifdef PLUGIN_73
    PLUGIN_73_NAME,
#endif
#ifdef PLUGIN_74
    PLUGIN_74_NAME,
#endif
#ifdef PLUGIN_75
    PLUGIN_75_NAME,
#endif
#ifdef PLUGIN_76
    PLUGIN_76_NAME,
#endif
#ifdef PLUGIN_77
    PLUGIN_77_NAME,
#endif
#ifdef PLUGIN_78
    PLUGIN_78_NAME,
#endif
#ifdef PLUGIN_79
    PLUGIN_79_NAME,
#endif
#ifdef PLUGIN_80
    PLUGIN_80_NAME,
#endif
#ifdef PLUGIN_81
    PLUGIN_81_NAME,
#endif
#ifdef PLUGIN_82
    PLUGIN_82_NAME,
#endif
#ifdef PLUGIN_83
    PLUGIN_83_NAME,
#endif
#ifdef PLUGIN_84
    PLUGIN_84_NAME,
#endif
#ifdef PLUGIN_85
    PLUGIN_85_NAME,
#endif
#ifdef PLUGIN_86
    PLUGIN_86_NAME,
#endif
#ifdef PLUGIN_87
    PLUGIN_87_NAME,
#endif
#ifdef PLUGIN_88
    PLUGIN_88_NAME,
#endif
#ifdef PLUGIN_89
    PLUGIN_89_NAME,
#endif
#ifdef PLUGIN_90
    PLUGIN_90_NAME,
#endif
#ifdef PLUGIN_91
    PLUGIN_91_NAME,
#endif
#ifdef PLUGIN_92
    PLUGIN_92_NAME,
#endif
#ifdef PLUGIN_93
    PLUGIN_93_NAME,
#endif
#ifdef PLUGIN_94
    PLUGIN_94_NAME,
#endif
#ifdef PLUGIN_95
    PLUGIN_95_NAME,
#endif
#ifdef PLUGIN_96
    PLUGIN_96_NAME,
#endif
#ifdef PLUGIN_97
    PLUGIN_97_NAME,
#endif
#ifdef PLUGIN_98
    PLUGIN_98_NAME,
#endif
#ifdef PLUGIN_99
    PLUGIN_99_NAME,
#warning "Last plugin number defined! Please check plugins numbers sequence or add additional plugin numbers to pluginList[]."
#endif
    "empty"
};






// Get size of the pluginList 
int32_t GetSizeof_pluginsList( void )
{
    return sizeof( pluginsList );
}

// Get size of the pluginList element
int32_t GetSizeof_pluginsListElement( void )
{
    return sizeof( pluginsList[ 0 ] );
}
/* End of file */
