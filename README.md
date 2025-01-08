# Fujifilm Profile parser
This library parses Fujifilm profiles and converts between formats.

- [ ] FP1 to struct
- [ ] raw to struct
- [ ] struct to raw
- [ ] struct to FP1

## What is a profile?
A profile (you could call it a 'recipe') stores all information needed to produce a jpeg from a RAF file. These settings are fed into
the image processor.

## Profile Formats
### FP1/FP2/FP3
XML user profile files created by X Raw Studio
### raw
The data structure sent between X Raw Studio and the camera
### struct
Intermediate data structure for other software to modify
