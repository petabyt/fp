#include <stdint.h>

enum FujiFileType {
	FP_JPG,
};

enum FujiImageSize {
	FP_L3x2 = 0x0,
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

enum FujiPushPullProcessing {
	FP_PLUS_3_EV = 3000,
	FP_PLUS_2_2_3_EV = 0xa6b,
	FP_PLUS_2_1_3_EV = 0x91d,
	FP_ZERO_EV = 0x0,
	FP_MIN_1_3_EV = (int)0xfffffeb3,
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

//#define FP_PLUS_4 40
//#define FP_PLUS_3 30
//#define FP_PLUS_2 20
//#define FP_PLUS_1 10
//#define FP_ZERO 0
//#define FP_MIN_1 0xfffffff6
//#define FP_MIN_2 0xffffffec
//#define FP_MIN_4 0xffffffd8

enum FujiRange {
	FP_PLUS_4 = 40,
	FP_PLUS_3 = 30,
	FP_PLUS_2 = 20,
	FP_PLUS_1 = 10,
	FP_ZERO = 0,
	FP_MIN_1 = (int)0xfffffff6,
	FP_MIN_2 = (int)0xffffffec,
	FP_MIN_4 = (int)0xffffffd8
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
	int TetherRAWConditonCode;
	enum FujiBool Editable;
	enum FujiOnOff ShootingCondition;
	enum FujiFileType FileType;
	enum FujiImageSize ImageSize;
	int RotationAngle;
	enum FujiImageQuality ImageQuality;
	int ExposureBias;
	int DynamicRange;
	int WideDRange;
	enum FujiSim FilmSimulation;
	int BlackImageTone;
	int MonochromaticColor_RG;
	enum FujiGrainEffect GrainEffect;
	enum FujiGrainEffectSize GrainEffectSize;
	enum FujiOnOff ChromeEffect;
	enum FujiOnOff ColorChromeBlue; // no value
	int SmoothSkinEffect;
	int WBShootCond;
	int WhiteBalance;
	int WBShiftR;
	int WBShiftB;
	// 10,000K - 2500k
	int WBColorTemp;
	int HighlightTone;
	int ShadowTone;
	int Color;
	enum FujiRange Sharpness;
	enum FujiRange NoisReduction;
	int Clarity;
	int LensModulationOpt;
	int ColorSpace;
	enum FujiBool HDRPresent;
};

struct __attribute__((packed)) FujiBinaryProfile {
	uint8_t n_props;
	char iop_codes[0x200];
	union Props {
		struct Raw {
			uint32_t props[22];
		}raw;
		struct XH1 {
			uint32_t prop0;
			uint32_t prop1;
			uint32_t prop2;
			uint32_t ImageSize;
			uint32_t ImageQuality;
			uint32_t prop5;
			uint32_t prop6;
			uint32_t prop7;
			uint32_t FilmSimulation;
			uint32_t GrainEffect;
			uint32_t prop10;
			uint32_t WBShootCond;
			uint32_t WhiteBalance;
			uint32_t WBShiftR;
			uint32_t WBShiftB;
			uint32_t WBColorTemp;
			uint32_t HighlightTone;
			uint32_t prop17;
			uint32_t prop18;
			uint32_t Sharpness;
			uint32_t prop20;
			uint32_t prop21;
			uint32_t ColorSpace;
		}xh1;
	}props;
};
