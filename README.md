# foundation-package-extractor

Unofficial tool to inspect Foundation game packages.

## Usage

1. Install GCC, for example with MinGW 64.
    1. Using [Chocolatey](https://chocolatey.org/install): `choco install mingw` and `choco install make` 
2. Download latest release (sources zip) from [Releases](https://github.com/leonardfactory/foundation-package-extractor/releases) or clone the Repository
3. Run PowerShell in the sources folder and execute `make`. It should produce an `extractor.exe` file
4. Copy `game.package` or any other package in the same folder
5. Run from PowerShell the following command: `.\extractor.exe game.package`
6. All files will be placed in the `game-package` folder

## Disclaimer

This software is for educational use, I'm not responsible for the misuse of the code and explanations described in this repository and/or the use of the tools provided, also I do not assume responsibility for the actions carried out with the information of the same. Please use this tool for ethical purposes.

## Credits

This work has been inspired by the awesome community of Foundation and the previous work done by [PegasusEpsilon](https://github.com/PegasusEpsilon/foundation-package-tools). Given it's not working anymore, I made a new tool from scratch since I wanted it to be OSS and to be released under MIT.