# Fujifilm Profile parser
Parser, validator, and converter for Fujifilm profile formats

A profile (you could also call it a 'recipe') stores all information needed to produce a jpeg from a raw file.
Most Fuji cameras are capable of applying these profiles to existing raw files, allowing settings for a photo to be altered
afterwards and produce jpegs as if they were taken on the scene.

This library aims to be able to parse and validate profile formats used by [X Raw Studio](https://fujifilm-x.com/global/products/software/x-raw-studio/), mainly the
raw data structure sent over PTP/USB.

The results for this project were obtained through black-box reversing with [vcam](https://github.com/petabyt/vcam).

## Profile Formats
### FP1/FP2/FP3
XML user profile files created by X Raw Studio
### raw
The data structure sent between X Raw Studio and the camera over PTP
### struct
Intermediate data structure created for this project for other software to modify

- [x] FP1/XML to struct
- [ ] Apply struct to raw
- [ ] raw to struct
- [ ] struct to raw
- [ ] struct to FP1
