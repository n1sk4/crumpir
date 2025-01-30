#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <filesystem>

#if defined(_WIN32) || defined(_WIN64)
  #include <windows.h>
  #define LIB_HANDLE HMODULE
#elif defined(__linux__) || defined(__APPLE__)
  #include <dlfcn.h>
  #define LIB_HANDLE void*
#endif

#include <opencv2/opencv.hpp>

class CrumpirGenerator {
public:
  CrumpirGenerator(int argc, char** argv);
  ~CrumpirGenerator() = default;

protected:
  char pixelToChar(int pixelValue);
  bool readPGM();
  std::vector<unsigned char> resizeImage();
  bool checkInput();
  void writeToFile(const std::string& generatedImage) const;
  bool convertPNGtoPGM();
  bool isPNG();
  bool hasExtension(const std::string& extension);
  bool checkOpenCVDLL();

private:
  std::string m_inputFile;
  std::string m_outputFile;
  int m_width, m_newWidth;
  int m_height, m_newHeight;
  std::vector<unsigned char> m_image;
  int m_argc;
  char** m_argv;

  const std::string m_invertedCharGradient 
    = "@&%QWNM0gB#$DR8mHXKAUbGOpV4d9h6PkqwSE2]ayjxY5Zoen[ult13If}C{iF|)7JvTLs?z/cr!+><;=^,_:'-. ";
  const std::string m_charGradient 
    = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
};
