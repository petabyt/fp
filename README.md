# Fujifilm Profile parser
This library parses Fujifilm profiles and converts between formats.

## What is a profile?
A profile (you could call it a 'recipe') stores all information needed to produce a jpeg from a RAF file. These settings are fed into
the image processor.

- [ ] FP1 to struct
- [ ] struct to FP1
- [ ] raw to struct
- [ ] struct to raw

## Profile Formats
### FP1/FP2/FP3
Files created by X Raw Studio
### Raw
The data structure sent from X Raw Studio to the camera
### Struct
C struct created by this library for frontend libraries to modify