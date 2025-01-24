#include "fp.h"

struct FujiLookup fp_film_sim[] = {
	{"Provia", FP_Provia},
	{"Velvia", FP_Velvia},
	{"Astia", FP_Astia},
	{"Classic", FP_ClassicChrome},
//	{"ClassicNEGA", -1},
	{"NEGAStd", FP_ProNegStd},
	{"NEGAhi", FP_PRONegHi},
	{"AcrosR", FP_AcrosR},
	{"AcrosG", FP_AcrosG},
	{"AcrosYe", FP_AcrosYe},
	{"Acros", FP_AcrosSTD},
	{"Eterna", FP_Eterna},
//	{"BleachBypass", -1},
	{"BW", FP_Monochrome},
	{"BYe", FP_MonochromeYe},
	{"BR", FP_MonochromeR},
	{"BG", FP_MonochromeG},
	{"Sepia", FP_Sepia},
	{0, 0},
};
struct FujiLookup fp_on_off[] = {
	{"ON", FP_ON},
	{"OFF", FP_OFF},
	{0, 0},
};
struct FujiLookup fp_drange[] = {
	{"DR100", 100},
	{"DR200", 200},
	{0, 0},
};
struct FujiLookup fp_drange_priority[] = {
	{"OFF", 0},
	{"WEAK", 1},
	{0, 0},
};
struct FujiLookup fp_bool[] = {
	{"TRUE", FP_TRUE},
	{"FALSE", FP_FALSE},
	{0, 0},
};
struct FujiLookup fp_grain_effect[] = {
	{"OFF", FP_GRAIN_OFF},
	{"WEAK", FP_GRAIN_WEAK},
	{"STRONG", FP_GRAIN_STRONG},
	{0, 0},
};
struct FujiLookup fp_chrome_effect[] = {
	{"OFF", FP_CHROME_OFF},
	{"WEAK", FP_CHROME_WEAK},
	{"STRONG", FP_CHROME_STRONG},
	{0, 0},
};
struct FujiLookup fp_file_type[] = {
	{"JPG", FP_JPG},
	{0, 0},
};
struct FujiLookup fp_grain_effect_size[] = {
	{"SMALL", FP_GRAIN_SIZE_SMALL},
	{0, 0},
};
struct FujiLookup fp_image_size[] = {
	{"L3x2", FP_L3x2},
	{"L16x9", FP_L16x9},
	{"L1x1", FP_L1x1},
	{"L3x2", FP_M1x1},
	{"L16x9", FP_M16x9},
	{"L1x1", FP_M1x1},
	{"S3x2", FP_S1x1},
	{"S16x9", FP_S16x9},
	{"S1x1", FP_S1x1},
	{0, 0},
};
struct FujiLookup fp_image_quality[] = {
	// What is 0?
	{"Fine", FP_FINE},
	{"Normal", FP_NORMAL},
	{0, 0},
};
struct FujiLookup fp_exposure_bias[] = {
	{"P3P00", FP_PLUS_3_EV},
	{"P2P67", FP_PLUS_2_2_3_EV},
	{"P2P33", FP_PLUS_2_1_3_EV},
	{"P2P0", FP_PLUS_2_EV},
	{"P1P67", FP_PLUS_1_2_3_EV},
	{"P1P33", FP_PLUS_1_1_3_EV},
	{"P1P00", FP_PLUS_1_EV},
	{"P0P67", FP_PLUS_2_3_EV},
	{"P0P33", FP_PLUS_1_3_EV},
	{"0", FP_ZERO_EV}, // No mention of P0P00 anywhere
	{"M0P33", FP_MIN_1_3_EV},
	{"M0P67", FP_MIN_2_3_EV},
	{"M1P00", FP_MIN_1_EV},
	{"M1P33", FP_MIN_1_1_3_EV},
	{"M1P67", FP_MIN_1_2_3_EV},
	{"M2P00", FP_MIN_2_EV},
	{"M2P33", FP_MIN_2_1_3_EV},
	{"M2P67", FP_MIN_2_2_3_EV},
	{"M3P00", FP_MIN_3_EV},
	{0, 0},
};
struct FujiLookup fp_white_balance[] = {
	{"AsShot", FP_WB_AsShot},
	{"INVALID", 1},
	{"Auto", FP_WB_Auto},
	{"Temperature", FP_WB_Temperature},
	{"Daylight", FP_WB_Daylight},
	{"FLight1", 123}, // ???
	{0, 0},
};
struct FujiLookup fp_color_temp[] = {
	{"10000K", 10000},
	{"9100K", 9100},
	{"8300K", 8300},
	{"7700K", 7700},
	{"7100K", 7100},
	{"6700K", 6700},
	{"6300K", 6300},
	{"5900K", 5900},
	{"5600K", 5600},
	{"5300K", 5300},
	{"5000K", 5000},
	{"4800K", 4800},
	{"4500K", 4500},
	{"4300K", 4300},
	{"4200K", 4200},
	{"4000K", 4000},
	{"3800K", 3800},
	{"3700K", 3700},
	{"3600K", 3600},
	{"3400K", 3400},
	{"3300K", 3300},
	{"3200K", 3200},
	{"3100K", 3100},
	{"3000K", 3000},
	{"2950K", 2950},
	{"2850K", 2850},
	{"2800K", 2800},
	{"2700K", 2700},
	{"2650K", 2650},
	{"2550K", 2550},
	{"2500K", 2500},
	{"0K", 0}, // Only valid if WhiteBalance is set to Temperature
	{0, 0},
};
struct FujiLookup fp_range[] = {
	{"4", FP_PLUS_4},
	{"3", FP_PLUS_3},
	{"2", FP_PLUS_2},
	{"1", FP_PLUS_1},
	{"0", FP_ZERO},
	{"-1", FP_MIN_1},
	{"-2", FP_MIN_2},
	{"-3", FP_MIN_3},
	{"-4", FP_MIN_4},
	{0, 0},
};
struct FujiLookup fp_noise_reduction[] = {
	{"4", FP_NR_PLUS_4},
	{"3", FP_NR_PLUS_3},
	{"2", FP_NR_PLUS_2},
	{"1", FP_NR_PLUS_1},
	{"0", FP_NR_ZERO},
	{"-1", FP_NR_MIN_1},
	{"-2", FP_NR_MIN_2},
	{"-3", FP_NR_MIN_3},
	{"-4", FP_NR_MIN_4},
	{0, 0},
};
struct FujiLookup fp_clarity[] = {
	{"4", 4},
	{"3", 3},
	{"2", 2},
	{"1", 1},
	{"0", 0},
	// TODO: Not understood yet
//	{"-1", FP_NR_MIN_1},
//	{"-2", FP_NR_MIN_2},
//	{"-3", FP_NR_MIN_3},
//	{"-4", FP_NR_MIN_4},
	{0, 0},
};
struct FujiLookup fp_range_p4_n2[] = {
	{"4", FP_PLUS_4},
	{"3", FP_PLUS_3},
	{"2", FP_PLUS_2},
	{"1", FP_PLUS_1},
	{"0", FP_ZERO},
	{"-1", FP_MIN_1},
	{"-2", FP_MIN_2},
	{0, 0},
};
struct FujiLookup fp_color_space[] = {
	{"sRGB", 1},
	{"Adobe sRGB", 2}, // TODO
	{0, 0},
};
