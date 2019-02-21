/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Measure plugins list

*******************************************************************************************************/
#include <stdlib.h>
#include <stdint.h>

#include "PluginsList.h"

//void vTask_MeasureX( void *pvParameters );

void (*pluginsPointerList[])( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms ) = {    
#ifdef PLUGIN_0
    PLUGIN_0_POINTER,
#endif
#ifdef PLUGIN_1
    PLUGIN_1_POINTER,
#endif
#ifdef PLUGIN_2
    PLUGIN_2_POINTER,
#endif
#ifdef PLUGIN_3
    PLUGIN_3_POINTER,
#endif
#ifdef PLUGIN_4
    PLUGIN_4_POINTER,
#endif
#ifdef PLUGIN_5
    PLUGIN_5_POINTER,
#endif
#ifdef PLUGIN_6
    PLUGIN_6_POINTER,
#endif
#ifdef PLUGIN_7
    PLUGIN_7_POINTER,
#endif
#ifdef PLUGIN_8
    PLUGIN_8_POINTER,
#endif
#ifdef PLUGIN_9
    PLUGIN_9_POINTER,
#endif
#ifdef PLUGIN_10
    PLUGIN_10_POINTER,
#endif
#ifdef PLUGIN_11
    PLUGIN_11_POINTER,
#endif
#ifdef PLUGIN_12
    PLUGIN_12_POINTER,
#endif
#ifdef PLUGIN_13
    PLUGIN_13_POINTER,
#endif
#ifdef PLUGIN_14
    PLUGIN_14_POINTER,
#endif
#ifdef PLUGIN_15
    PLUGIN_15_POINTER,
#endif
#ifdef PLUGIN_16
    PLUGIN_16_POINTER,
#endif
#ifdef PLUGIN_17
    PLUGIN_17_POINTER,
#endif
#ifdef PLUGIN_18
    PLUGIN_18_POINTER,
#endif
#ifdef PLUGIN_19
    PLUGIN_19_POINTER,
#endif
#ifdef PLUGIN_20
    PLUGIN_20_POINTER,
#endif
#ifdef PLUGIN_21
    PLUGIN_21_POINTER,
#endif
#ifdef PLUGIN_22
    PLUGIN_22_POINTER,
#endif
#ifdef PLUGIN_23
    PLUGIN_23_POINTER,
#endif
#ifdef PLUGIN_24
    PLUGIN_24_POINTER,
#endif
#ifdef PLUGIN_25
    PLUGIN_25_POINTER,
#endif
#ifdef PLUGIN_26
    PLUGIN_26_POINTER,
#endif
#ifdef PLUGIN_27
    PLUGIN_27_POINTER,
#endif
#ifdef PLUGIN_28
    PLUGIN_28_POINTER,
#endif
#ifdef PLUGIN_29
    PLUGIN_29_POINTER,
#endif
#ifdef PLUGIN_30
    PLUGIN_30_POINTER,
#endif
#ifdef PLUGIN_31
    PLUGIN_31_POINTER,
#endif
#ifdef PLUGIN_32
    PLUGIN_32_POINTER,
#endif
#ifdef PLUGIN_33
    PLUGIN_33_POINTER,
#endif
#ifdef PLUGIN_34
    PLUGIN_34_POINTER,
#endif
#ifdef PLUGIN_35
    PLUGIN_35_POINTER,
#endif
#ifdef PLUGIN_36
    PLUGIN_36_POINTER,
#endif
#ifdef PLUGIN_37
    PLUGIN_37_POINTER,
#endif
#ifdef PLUGIN_38
    PLUGIN_38_POINTER,
#endif
#ifdef PLUGIN_39
    PLUGIN_39_POINTER,
#endif
#ifdef PLUGIN_40
    PLUGIN_40_POINTER,
#endif
#ifdef PLUGIN_41
    PLUGIN_41_POINTER,
#endif
#ifdef PLUGIN_42
    PLUGIN_42_POINTER,
#endif
#ifdef PLUGIN_43
    PLUGIN_43_POINTER,
#endif
#ifdef PLUGIN_44
    PLUGIN_44_POINTER,
#endif
#ifdef PLUGIN_45
    PLUGIN_45_POINTER,
#endif
#ifdef PLUGIN_46
    PLUGIN_46_POINTER,
#endif
#ifdef PLUGIN_47
    PLUGIN_47_POINTER,
#endif
#ifdef PLUGIN_48
    PLUGIN_48_POINTER,
#endif
#ifdef PLUGIN_49
    PLUGIN_49_POINTER,
#endif
#ifdef PLUGIN_50
    PLUGIN_50_POINTER,
#endif
#ifdef PLUGIN_51
    PLUGIN_51_POINTER,
#endif
#ifdef PLUGIN_52
    PLUGIN_52_POINTER,
#endif
#ifdef PLUGIN_53
    PLUGIN_53_POINTER,
#endif
#ifdef PLUGIN_54
    PLUGIN_54_POINTER,
#endif
#ifdef PLUGIN_55
    PLUGIN_55_POINTER,
#endif
#ifdef PLUGIN_56
    PLUGIN_56_POINTER,
#endif
#ifdef PLUGIN_57
    PLUGIN_57_POINTER,
#endif
#ifdef PLUGIN_58
    PLUGIN_58_POINTER,
#endif
#ifdef PLUGIN_59
    PLUGIN_59_POINTER,
#endif
#ifdef PLUGIN_60
    PLUGIN_60_POINTER,
#endif
#ifdef PLUGIN_61
    PLUGIN_61_POINTER,
#endif
#ifdef PLUGIN_62
    PLUGIN_62_POINTER,
#endif
#ifdef PLUGIN_63
    PLUGIN_63_POINTER,
#endif
#ifdef PLUGIN_64
    PLUGIN_64_POINTER,
#endif
#ifdef PLUGIN_65
    PLUGIN_65_POINTER,
#endif
#ifdef PLUGIN_66
    PLUGIN_66_POINTER,
#endif
#ifdef PLUGIN_67
    PLUGIN_67_POINTER,
#endif
#ifdef PLUGIN_68
    PLUGIN_68_POINTER,
#endif
#ifdef PLUGIN_69
    PLUGIN_69_POINTER,
#endif
#ifdef PLUGIN_70
    PLUGIN_70_POINTER,
#endif
#ifdef PLUGIN_71
    PLUGIN_71_POINTER,
#endif
#ifdef PLUGIN_72
    PLUGIN_72_POINTER,
#endif
#ifdef PLUGIN_73
    PLUGIN_73_POINTER,
#endif
#ifdef PLUGIN_74
    PLUGIN_74_POINTER,
#endif
#ifdef PLUGIN_75
    PLUGIN_75_POINTER,
#endif
#ifdef PLUGIN_76
    PLUGIN_76_POINTER,
#endif
#ifdef PLUGIN_77
    PLUGIN_77_POINTER,
#endif
#ifdef PLUGIN_78
    PLUGIN_78_POINTER,
#endif
#ifdef PLUGIN_79
    PLUGIN_79_POINTER,
#endif
#ifdef PLUGIN_80
    PLUGIN_80_POINTER,
#endif
#ifdef PLUGIN_81
    PLUGIN_81_POINTER,
#endif
#ifdef PLUGIN_82
    PLUGIN_82_POINTER,
#endif
#ifdef PLUGIN_83
    PLUGIN_83_POINTER,
#endif
#ifdef PLUGIN_84
    PLUGIN_84_POINTER,
#endif
#ifdef PLUGIN_85
    PLUGIN_85_POINTER,
#endif
#ifdef PLUGIN_86
    PLUGIN_86_POINTER,
#endif
#ifdef PLUGIN_87
    PLUGIN_87_POINTER,
#endif
#ifdef PLUGIN_88
    PLUGIN_88_POINTER,
#endif
#ifdef PLUGIN_89
    PLUGIN_89_POINTER,
#endif
#ifdef PLUGIN_90
    PLUGIN_90_POINTER,
#endif
#ifdef PLUGIN_91
    PLUGIN_91_POINTER,
#endif
#ifdef PLUGIN_92
    PLUGIN_92_POINTER,
#endif
#ifdef PLUGIN_93
    PLUGIN_93_POINTER,
#endif
#ifdef PLUGIN_94
    PLUGIN_94_POINTER,
#endif
#ifdef PLUGIN_95
    PLUGIN_95_POINTER,
#endif
#ifdef PLUGIN_96
    PLUGIN_96_POINTER,
#endif
#ifdef PLUGIN_97
    PLUGIN_97_POINTER,
#endif
#ifdef PLUGIN_98
    PLUGIN_98_POINTER,
#endif
#ifdef PLUGIN_99
    PLUGIN_99_POINTER,
#warning "Last plugin number defined! Please check plugins numbers sequence or add additional plugin numbers to pluginList[]."
#endif
    NULL
};

/* End of file */
