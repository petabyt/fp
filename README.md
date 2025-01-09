# Fujifilm Profile parser
This library parses Fujifilm profiles and converts between formats.

## What is a profile?
A profile (you could also call it a 'recipe') stores all information needed to produce a jpeg from a RAF file. These settings are fed into
the camera image processor to produce the same jpeg as if it were taken on the camera.

## Profile Formats
### FP1/FP2/FP3
XML user profile files created by X Raw Studio
### raw
The data structure sent between X Raw Studio and the camera over PTP
### struct
Intermediate data structure created for this project for other software to modify

- [ ] FP1 to struct
- [ ] raw to struct
- [ ] struct to raw
- [ ] struct to FP1
