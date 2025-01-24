#pragma once
#include <stdint.h>

enum FujiFileType {
	FP_JPG,
};

enum FujiImageSize {
	FP_L3x2 = 0x7,
	FP_L16x9 = 0x8,
	FP_L1x1 = 0x9,
	FP_M3x2 = 0x4,
	FP_M16x9 = 0x5,
	FP_M1x1 = 0x6,
	FP_S3x2 = 0x1,
	FP_S16x9 = 0x2,
	FP_S1x1 = 0x3,
};

enum FujiImageQuality {
	FP_FINE = 0x2,
	FP_NORMAL = 0x3,
};

//enum FujiExposureBias {
//	FP_EXPO_BIAS_P0P67 = 1,
//	FP_EXPO_BIAS_P0P33,
//};

enum FujiExposureBias {
	FP_PLUS_3_EV = 3000,
	FP_PLUS_2_2_3_EV = 2667,
	FP_PLUS_2_1_3_EV = 2333,
	FP_PLUS_2_EV = 2000,
	FP_PLUS_1_2_3_EV = 1667,
	FP_PLUS_1_1_3_EV = 1333,
	FP_PLUS_1_EV = 1000,
	FP_PLUS_2_3_EV = 667,
	FP_PLUS_1_3_EV = 333,
	FP_ZERO_EV = 0x0,
	FP_MIN_1_3_EV = (int)0xfffffeb3,
	FP_MIN_2_3_EV = (int)0xfffffd65,
	FP_MIN_1_EV = (int)0xfffffc18,
	FP_MIN_1_1_3_EV = (int)0xfffffacb,
	FP_MIN_1_2_3_EV = (int)0xfffff97d,
	FP_MIN_2_EV = (int)0xfffff830,
	FP_MIN_2_1_3_EV = (int)0xfffff6e3,
	FP_MIN_2_2_3_EV = (int)0xfffff595,
	FP_MIN_3_EV = (int)0xfffff448,
};

enum FujiSim {
	FP_Provia = 0x1, // Standard
	FP_Velvia = 0x2, // Vivid
	FP_Astia = 0x3, // Soft
	FP_ClassicChrome = 0xb,
	FP_PRONegHi = 0x4,
	FP_ProNegStd = 0x5,
	FP_Eterna = 0x10,
	FP_AcrosSTD = 0xc,
	FP_AcrosYe = 0xd,
	FP_AcrosR = 0xe,
	FP_AcrosG = 0xf,
	FP_Monochrome = 0x6,
	FP_MonochromeYe = 0x7,
	FP_MonochromeR = 0x8,
	FP_MonochromeG = 0x9,
	FP_Sepia = 0xa,
};

enum FujiRange {
	FP_PLUS_4 = 40,
	FP_PLUS_3 = 30,
	FP_PLUS_2 = 20,
	FP_PLUS_1 = 10,
	FP_ZERO = 0,
	FP_MIN_1 = (int)0xfffffff6,
	FP_MIN_2 = (int)0xffffffec,
	FP_MIN_3 = (int)0xffffffe1,
	FP_MIN_4 = (int)0xffffffd8,
};

enum FujiNoiseReduction {
	FP_NR_PLUS_4 = 0x5000,
	FP_NR_PLUS_3 = 0x6000,
	FP_NR_PLUS_2 = 0x0,
	FP_NR_PLUS_1 = 0x1000,
	FP_NR_ZERO = 0x2000,
	FP_NR_MIN_1 = 0x3000,
	FP_NR_MIN_2 = 0x4000,
	FP_NR_MIN_3 = 0x7000,
	FP_NR_MIN_4 = 0x8000,
};

enum FujiOnOff {
	FP_OFF = 0,
	FP_ON,
};

enum FujiBool {
	FP_FALSE = 0,
	FP_TRUE,
};

enum FujiGrainEffect {
	FP_GRAIN_OFF = 1,
	FP_GRAIN_WEAK = 0x2,
	FP_GRAIN_STRONG = 0x3,
};

enum FujiChromeEffect {
	FP_CHROME_OFF = 0x1,
	FP_CHROME_WEAK = 0x2,
	FP_CHROME_STRONG = 0x3,
};

enum FujiGrainEffectSize {
	FP_GRAIN_SIZE_SMALL = 0,
};

enum FujiWhiteBalance {
	FP_WB_AsShot = 0,
	FP_WB_Auto = 0x2,
	FP_WB_Daylight = 0x4,
	FP_WB_INCANDESCENT = 0x6,
	FP_WB_UNDERWATER = 0x8,
	FP_WB_Custom1 = 0x8008,
	FP_WB_Custom2 = 0x8009,
	FP_WB_Custom3 = 0x800a,
	FP_WB_Temperature = 8007,
	FP_WB_Shade = 0x8006,
	FP_WB_FLORESCENT_1 = 0x8001,
	FP_WB_FLORESCENT_2 = 0x8002,
	FP_WB_FLORESCENT_3 = 0x8003,
	FP_WB_Invalid,
};

struct FujiFP1 {
	int StructVer;
	char SerialNumber[64];
	uint32_t IOPCode;
	uint32_t TetherRAWConditonCode;
	uint32_t Editable;
	uint32_t ShootingCondition;
	uint32_t FileType;
	uint32_t ImageSize;
	uint32_t RotationAngle;
	uint32_t ImageQuality;
	uint32_t ExposureBias;
	uint32_t DynamicRange;
	uint32_t WideDRange;
	uint32_t FilmSimulation;
	uint32_t BlackImageTone;
	uint32_t MonochromaticColor_RG;
	uint32_t GrainEffect;
	uint32_t GrainEffectSize;
	uint32_t ChromeEffect;
	uint32_t ColorChromeBlue; // no value
	uint32_t SmoothSkinEffect;
	uint32_t WBShootCond;
	uint32_t WhiteBalance;
	uint32_t WBShiftR;
	uint32_t WBShiftB;
	uint32_t WBColorTemp;
	uint32_t HighlightTone;
	uint32_t ShadowTone;
	uint32_t Color;
	uint32_t Sharpness;
	uint32_t NoisReduction;
	uint32_t Clarity;
	uint32_t LensModulationOpt;
	uint32_t ColorSpace;
	uint32_t HDR;
};

struct __attribute__((packed)) FujiBinaryProfile {
	// So far this has been observed as 0x17 or 0x1d and seems to represent the number of properties following iop_codes.
	// The problem is, the camera appears to always send this structure as exactly 601 bytes regardless of n_props.
	// In that case, one would expect n_props to be 0x16, but it puts 0x17 instead.
	// X Raw Studio seems to always write this correctly as 0x1d and sends 629 bytes.
	// When this structure is read back from the camera, it again sends it back as 601 bytes with n_props being 0x1d.
	uint16_t n_props;
	// This seems to hold a series of (or just one) standard MTP strings.
	// The camera also seems to incorrectly format this property, writing the string as length 8 rather than 9.
	// (See MTP spec page 21 - length of a string includes the null terminator)
	char iop_codes[0x1ff];
	// (offset 0x201)
	// These appear to be in the same order as the props in the XML files
	union Props {
		uint32_t values[0x1d];
		// For reference:
		struct Props1 {
			uint32_t prop0;
			uint32_t prop1;
			uint32_t ImageSize;
			uint32_t ImageQuality;
			uint32_t ExposureBias;
			uint32_t DynamicRange;
			uint32_t WideDRange; // 6 D RangePriority
			uint32_t FilmSimulation;
			uint32_t GrainEffect;
			uint32_t GrainEffectSize;
			uint32_t WBShootCond; // 10
			uint32_t WhiteBalance; // 11
			uint32_t WBShiftR; // 12
			uint32_t WBShiftB; // 13
			uint32_t WBColorTemp; // 14
			uint32_t HighlightTone; // 15
			uint32_t ShadowTone; // 16
			uint32_t Color; // 17
			uint32_t Sharpness; // 18
			uint32_t NoisReduction; // 19
			uint32_t Clarity; // 20
			uint32_t ColorSpace; // 21
		}props_temp;
	}props;
};

struct FujiLookup {
	char *key;
	uint32_t value;
};

extern struct FujiLookup fp_film_sim[];
extern struct FujiLookup fp_on_off[];
extern struct FujiLookup fp_bool[];
extern struct FujiLookup fp_grain_effect[];
extern struct FujiLookup fp_chrome_effect[];
extern struct FujiLookup fp_file_type[];
extern struct FujiLookup fp_grain_effect_size[];
extern struct FujiLookup fp_image_size[];
extern struct FujiLookup fp_image_quality[];
extern struct FujiLookup fp_exposure_bias[];
extern struct FujiLookup fp_white_balance[];
extern struct FujiLookup fp_color_temp[];
extern struct FujiLookup fp_range[];
extern struct FujiLookup fp_color_space[];
extern struct FujiLookup fp_range_p4_n2[];
extern struct FujiLookup fp_drange[];
extern struct FujiLookup fp_drange_priority[];
extern struct FujiLookup fp_noise_reduction[];
extern struct FujiLookup fp_clarity[];

struct FPContext {
	struct FujiFP1 *fp;
	// TODO: IOPCode or some other capability code on the camera
};

int fp_parse_fp1(const char *path, struct FujiFP1 *fp1);
int fp_parse_raw(const uint8_t *bin, int len, struct FujiFP1 *fp1);
int fp_dump_struct(FILE *f, struct FujiFP1 *fp);
