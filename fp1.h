#include <stdint.h>

enum FujiFileType {
	FP_JPG,
};

enum FujiImageSize {
	FP_L3x2 = 0,
	FP_L16x9,
	FP_L1x1,
};

enum FujiSim {
	FP_Provia = 0,
	FP_Velvia,
	FP_Astia,
	FP_ClassicChrome,
	FP_PRONegHi,
	FP_ProNegStd,
	FP_Eterna,
	FP_AcrosSTD,
	FP_AcrosYe,
	FP_AcrosR,
	FP_AcrosG,
	FP_Monochrome,
	FP_Sepia,
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
	FP_GRAIN_OFF = 0,
	FP_GRAIN_WEAK,
	FP_GRAIN_STRONG,
};

enum FujiGrainEffectSize {
	FP_GRAIN_SIZE_SMALL = 0,
};

enum FujiWhiteBalance {
	FP_WB_Auto = 0,
	FP_WB_Temperature,
	FP_WB_Daylight,
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
	int ImageQuality;
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
	int WBColorTemp;
	int HighlightTone;
	int ShadowTone;
	int Color;
	int Sharpness;
	int NoisReduction;
	int Clarity;
	int LensModulationOpt;
	int ColorSpace;
	enum FujiBool HDRPresent;
};

struct __attribute__((packed)) FujiBinaryProfile {
	uint8_t n_props;
	char iop_codes[0x200];
	uint32_t props[22];
};
