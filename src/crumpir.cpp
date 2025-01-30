#include "..\include\crumpir.hpp"

CrumpirGenerator::CrumpirGenerator(int argc, char** argv)
                  : m_argc(argc), m_argv(argv), 
                    m_width(0), m_height(0), 
                    m_newWidth(64), m_newHeight(64) {
  if (!checkInput()) {
    return;
  }

  if (isPNG() && !convertPNGtoPGM()) {
    return;
  }

  if (!readPGM()) {
    return;
  }

  std::vector<unsigned char> resizedImage = resizeImage();

  std::stringstream generatedImage;
  for (int y = 0; y < m_newHeight; ++y) {
    for (int x = 0; x < m_newWidth; ++x) {
      int pixelValue = resizedImage[y * m_newWidth + x];
      generatedImage << pixelToChar(pixelValue);
    }
    generatedImage << "\n";
  }

  std::cout << generatedImage.str() << "\n";

  if (!m_outputFile.empty()) {
    writeToFile(generatedImage.str());
  }
}

bool CrumpirGenerator::isPNG() {
  return hasExtension(".png");
}

bool CrumpirGenerator::hasExtension(const std::string& extension) {
  std::filesystem::path filePath = m_inputFile;
  return filePath.extension() == extension;
}

bool CrumpirGenerator::convertPNGtoPGM() {
  checkOpenCVDLL();

  cv::Mat image = cv::imread(m_inputFile, cv::IMREAD_GRAYSCALE);
  if (image.empty()) {
    std::cout << "Error: Could not open or find the image.\n";
    return false;
  }

  std::filesystem::path tempDir = std::filesystem::temp_directory_path();
  std::filesystem::path tempFile = tempDir / "temp_image.pgm";  // Generate temp file path

  if (!cv::imwrite(tempFile.string(), image)) {
    std::cout << "Error: Could not save the temporary image.\n";
    return false;
  }

  m_inputFile = tempFile.string();
  return true;
}

bool CrumpirGenerator::checkOpenCVDLL() {
  const char* opencvLib =
#if defined(_WIN32) || defined(_WIN64)
    "opencv_world4100.dll"; // Windows
#elif defined(__APPLE__)
    "libopencv_world.4.1.0.dylib"; // macOS
#else
    "libopencv_world.so.4.1"; // Linux
#endif

  LIB_HANDLE handle = LoadLibrary(opencvLib);
  if (!handle) {
    std::cerr << "Error: OpenCV library (" << opencvLib << ") is missing!\n";
    return false;
  }
  FreeLibrary(handle);
  return true;
}

char CrumpirGenerator::pixelToChar(int pixelValue) {
  int index = (pixelValue * (m_charGradient.size() - 1)) / 255;
  return m_charGradient[index];
}

bool CrumpirGenerator::readPGM() {
  std::ifstream file(m_inputFile, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Unable to open file: " << m_inputFile << "\n";
    return false;
  }

  std::string magicNumber;
  file >> magicNumber;
  if (magicNumber != "P5") {
    std::cerr << "Invalid PGM file" << "\n";
    return false;
  }

  file >> m_width >> m_height;
  int maxVal;
  file >> maxVal;
  file.ignore(1); // Ignore the newline character after maxVal

  m_image.resize(m_width * m_height);
  file.read(reinterpret_cast<char*>(m_image.data()), m_image.size());

  return true;
}

std::vector<unsigned char> CrumpirGenerator::resizeImage() {
  std::vector<unsigned char> resizedImage(m_newWidth * m_newHeight);

  for (int y = 0; y < m_newHeight; ++y) {
    for (int x = 0; x < m_newWidth; ++x) {
      int srcX = x * m_width / m_newWidth;
      int srcY = y * m_height / m_newHeight;
      resizedImage[y * m_newWidth + x] = m_image[srcY * m_width + srcX];
    }
  }

  return resizedImage;
}

bool CrumpirGenerator::checkInput() {
  if (m_argc < 2) {
    std::cerr << "Usage: " << m_argv[0] << " <input_file> [<output_file>] [-height <height>] [-width <width>]\n";
    return false;
  }

  m_inputFile = m_argv[1];

  for (int i = 2; i < m_argc; ++i) {
    if (std::strcmp(m_argv[i], "-height") == 0 || std::strcmp(m_argv[i], "-h") == 0) {
      if (i + 1 < m_argc) {
        m_newHeight = std::stoi(m_argv[++i]);
      }
      else {
        std::cerr << "Error: missing value for " << m_argv[i] << "\n";
        return false;
      }
    }
    else if (std::strcmp(m_argv[i], "-width") == 0 || std::strcmp(m_argv[i], "-w") == 0) {
      if (i + 1 < m_argc) {
        m_newWidth = std::stoi(m_argv[++i]);
      }
      else {
        std::cerr << "Error: missing value for " << m_argv[i] << "\n";
        return false;
      }
    }
    else if (i == 2) {
      m_outputFile = m_argv[i];
    }
    else {
      std::cerr << "Unknown argument: " << m_argv[i] << "\n";
      return false;
    }
  }

  return true;
}

void CrumpirGenerator::writeToFile(const std::string& generatedImage) const {
  std::ofstream outFile(m_outputFile);

  if (outFile.is_open()) {
    outFile << generatedImage;
    outFile.close();
  }
  else {
    std::cerr << "Unable to open file.\n";
  }
}