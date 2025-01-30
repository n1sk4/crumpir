# How to run

From PowerShell
#### defaults to 64x64 format
```
.\crumpir.exe "input_file.pgm" 
```
#### generates only CLI ASCII grayscale art
```
.\crumpir.exe "input_file.pgm" -w 32 -h 32 
```
#### full sintax
```
.\crumpir.exe "input_file.pgm" "output_file.txt" -width 32 -height 32
```
#### with PNG -> PGM conversion
```
.\crumpir.exe "input_file.png" "output_file.txt" -width 32 -height 32 
```


# Dependencies and Build
This project uses [OpenCV library 4.10.0](https://opencv.org/releases/)
Library is just extracted to desired path and set as Environment variable (or copied into build path)

CMake used for setting up the build environment

![image](https://github.com/user-attachments/assets/0082dde7-9b13-43f9-973e-0d1070adf9b6)
