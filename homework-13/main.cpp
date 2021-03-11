#include <fstream>
#include <iostream>
#include <vector>

enum class FileType { LittleEndian = 0x4D42, BigEndian = 0x424D };

enum class InfoHeaderVersion {
    Core = 12,
    V3 = 40,
    V4 = 108,
    V5 = 124,
};

#pragma pack(push, 1)
struct BitmapFileHeader {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offBits;
};
#pragma pack(pop)

struct BitmapCoreHeader {
    uint32_t size;
    uint16_t width;
    uint16_t height;
    uint16_t planes;
    uint16_t bitCount;
};

#pragma pack(push, 1)
struct BitmapV3Header {
    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t sizeImage;
    uint32_t xPelsPerMeter;
    uint32_t yPelsPerMeter;
    uint32_t clrUsed;
    uint32_t clrImportant;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BitmapV4Header : public BitmapV3Header {
    uint32_t redMask;
    uint32_t greenMask;
    uint32_t blueMask;
    uint32_t alphaMask;
    uint32_t cSType;
    uint8_t endpoints[36];
    uint32_t gammaRed;
    uint32_t gammaGreen;
    uint32_t gammaBlue;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BitmapV5Header : public BitmapV4Header {
    uint32_t intent;
    uint32_t profileData;
    uint32_t profileSize;
    uint32_t reserved;
};
#pragma pack(pop)

struct Color {
    float r;
    float g;
    float b;
    float a;
};

class BMP {
  public:
    enum class Format {
        RGB16 = 16,
        RGB24 = 24,
        RGBA32 = 32,
        RGB48 = 48,
        RGBA64 = 64
    };

  private:
    BitmapFileHeader m_FileHeader;
    BitmapV5Header m_InfoHeader;
    std::vector<Color> m_Pixels;

  public:
    std::vector<Color> &pixels() { return m_Pixels; }

    void load(const std::string &path) {
        std::ifstream source(path, std::ios::binary | std::ios::in);

        source.read(reinterpret_cast<char *>(&m_FileHeader),
                    sizeof(BitmapFileHeader));

        if (m_FileHeader.type !=
            static_cast<uint16_t>(FileType::LittleEndian)) {
            throw "Unsupported endianess";
        }

        uint32_t version;
        source.read(reinterpret_cast<char *>(&version), sizeof(uint32_t));

        if (version == static_cast<uint32_t>(InfoHeaderVersion::Core)) {
            throw "Unsupported version";
        }

        source.seekg(sizeof(BitmapFileHeader), std::ios_base::beg);
        source.read(reinterpret_cast<char *>(&m_InfoHeader),
                    sizeof(BitmapV5Header));

        uint32_t rowStride = m_InfoHeader.width * m_InfoHeader.bitCount / 8;
        uint32_t rowPadding = (4 - rowStride % 4) % 4;

        std::vector<uint8_t> buffer(m_InfoHeader.height * m_InfoHeader.width *
                                    m_InfoHeader.bitCount / 8);
        std::vector<uint8_t> paddingBuffer(rowPadding);

        source.seekg(m_FileHeader.offBits, std::ios_base::beg);
        for (size_t y = 0; y < m_InfoHeader.height; y++) {
            source.read(reinterpret_cast<char *>(buffer.data() + rowStride * y),
                        rowStride);
            source.read(reinterpret_cast<char *>(paddingBuffer.data()),
                        rowPadding);
        }
        source.close();

        if (m_InfoHeader.bitCount < static_cast<uint16_t>(Format::RGB16)) {
            std::cout << m_InfoHeader.bitCount << std::endl;
            throw "Unsupported bit count";
        }

        std::vector<Color> pixels;

        if (m_InfoHeader.bitCount == static_cast<uint16_t>(Format::RGB16)) {
            uint16_t *wbuffer = reinterpret_cast<uint16_t *>(buffer.data());
            for (size_t i = 0; i < buffer.size() / 2; i++) {
                float b = static_cast<float>(wbuffer[i] & 0x000F) / 127.0f;
                float g =
                    static_cast<float>((wbuffer[i] & 0x00F0) >> 4) / 127.0f;
                float r =
                    static_cast<float>((wbuffer[i] & 0x0F00) >> 8) / 127.0f;
                float a =
                    static_cast<float>((wbuffer[i] & 0xF000) >> 12) / 127.0f;

                pixels.push_back({r, g, b, a});
            }
        }

        if (m_InfoHeader.bitCount == static_cast<uint16_t>(Format::RGB24)) {
            for (size_t i = 0; i < buffer.size(); i += 3) {
                float r = static_cast<float>(buffer[i + 2]) / 255.0f;
                float g = static_cast<float>(buffer[i + 1]) / 255.0f;
                float b = static_cast<float>(buffer[i + 0]) / 255.0f;
                float a = 0.0f;

                pixels.push_back({r, g, b, a});
            }
        }

        if (m_InfoHeader.bitCount == static_cast<uint16_t>(Format::RGBA32)) {
            for (size_t i = 0; i < buffer.size(); i += 4) {
                float r = static_cast<float>(buffer[i + 2]) / 255.0f;
                float g = static_cast<float>(buffer[i + 1]) / 255.0f;
                float b = static_cast<float>(buffer[i + 0]) / 255.0f;
                float a = static_cast<float>(buffer[i + 3]) / 255.0f;

                pixels.push_back({r, g, b, a});
            }
        }

        if (m_InfoHeader.bitCount == static_cast<uint16_t>(Format::RGB48)) {
            uint16_t *wbuffer = reinterpret_cast<uint16_t *>(buffer.data());
            for (size_t i = 0; i < buffer.size() / 2; i += 3) {
                float r = static_cast<float>(wbuffer[i + 2]) / 65535.0f;
                float g = static_cast<float>(wbuffer[i + 1]) / 65535.0f;
                float b = static_cast<float>(wbuffer[i + 0]) / 65535.0f;
                float a = 0.0f;

                pixels.push_back({r, g, b, a});
            }
        }

        if (m_InfoHeader.bitCount == static_cast<uint16_t>(Format::RGBA64)) {
            uint16_t *wbuffer = reinterpret_cast<uint16_t *>(buffer.data());
            for (size_t i = 0; i < buffer.size() / 2; i += 4) {
                float r = static_cast<float>(wbuffer[i + 2]) / 65535.0f;
                float g = static_cast<float>(wbuffer[i + 1]) / 65535.0f;
                float b = static_cast<float>(wbuffer[i + 0]) / 65535.0f;
                float a = static_cast<float>(wbuffer[i + 3]) / 65535.0f;

                pixels.push_back({r, g, b, a});
            }
        }

        m_Pixels = std::move(pixels);
    }

    void save(const std::string &path) {
        std::vector<uint8_t> buffer;
        buffer.reserve(m_InfoHeader.height * m_InfoHeader.width *
                       m_InfoHeader.bitCount / 8);

        if (m_InfoHeader.bitCount == static_cast<uint16_t>(Format::RGB16)) {
            for (const auto &pixel : m_Pixels) {
                uint8_t r = static_cast<uint16_t>(pixel.r * 127.0f);
                uint8_t g = static_cast<uint16_t>(pixel.g * 127.0f);
                uint8_t b = static_cast<uint16_t>(pixel.b * 127.0f);
                uint8_t a = static_cast<uint16_t>(pixel.a * 127.0f);

                uint8_t bg = g << 4 & b;
                uint8_t ra = a << 4 & r;

                buffer.push_back(bg);
                buffer.push_back(ra);
            }
        }

        if (m_InfoHeader.bitCount == static_cast<uint16_t>(Format::RGB24)) {
            for (const auto &pixel : m_Pixels) {
                uint8_t r = static_cast<uint8_t>(pixel.r * 255.0f);
                uint8_t g = static_cast<uint8_t>(pixel.g * 255.0f);
                uint8_t b = static_cast<uint8_t>(pixel.b * 255.0f);

                buffer.push_back(b);
                buffer.push_back(g);
                buffer.push_back(r);
            }
        }

        if (m_InfoHeader.bitCount == static_cast<uint16_t>(Format::RGBA32)) {
            for (const auto &pixel : m_Pixels) {
                uint8_t r = static_cast<uint8_t>(pixel.r * 255.0f);
                uint8_t g = static_cast<uint8_t>(pixel.g * 255.0f);
                uint8_t b = static_cast<uint8_t>(pixel.b * 255.0f);
                uint8_t a = static_cast<uint8_t>(pixel.a * 255.0f);

                buffer.push_back(b);
                buffer.push_back(g);
                buffer.push_back(r);
                buffer.push_back(a);
            }
        }

        if (m_InfoHeader.bitCount == static_cast<uint16_t>(Format::RGB48)) {
            for (const auto &pixel : m_Pixels) {
                uint16_t r = static_cast<uint16_t>(pixel.r * 65535.0f);
                uint16_t g = static_cast<uint16_t>(pixel.g * 65535.0f);
                uint16_t b = static_cast<uint16_t>(pixel.b * 65535.0f);

                uint16_t wbuffer[3] = {b, g, r};
                uint8_t *bytes = reinterpret_cast<uint8_t *>(wbuffer);

                buffer.insert(buffer.end(), bytes, bytes + 6);
            }
        }

        if (m_InfoHeader.bitCount == static_cast<uint16_t>(Format::RGBA64)) {
            for (const auto &pixel : m_Pixels) {
                uint16_t r = static_cast<uint16_t>(pixel.r * 65535.0f);
                uint16_t g = static_cast<uint16_t>(pixel.g * 65535.0f);
                uint16_t b = static_cast<uint16_t>(pixel.b * 65535.0f);
                uint16_t a = static_cast<uint16_t>(pixel.a * 65535.0f);

                uint16_t wbuffer[4] = {b, g, r, a};
                uint8_t *bytes = reinterpret_cast<uint8_t *>(wbuffer);

                buffer.insert(buffer.end(), bytes, bytes + 8);
            }
        }

        std::ofstream dest(path,
                           std::ios::binary | std::ios::out | std::ios::trunc);

        dest.write(reinterpret_cast<char *>(&m_FileHeader),
                   sizeof(BitmapFileHeader));
        dest.write(reinterpret_cast<char *>(&m_InfoHeader),
                   sizeof(BitmapV5Header));

        uint32_t rowStride = m_InfoHeader.width * m_InfoHeader.bitCount / 8;
        uint32_t rowPadding = (4 - rowStride % 4) % 4;
        std::vector<uint8_t> paddingBuffer(rowPadding);

        dest.seekp(m_FileHeader.offBits, std::ios_base::beg);
        for (size_t y = 0; y < m_InfoHeader.height; y++) {
            dest.write(reinterpret_cast<char *>(buffer.data() + rowStride * y),
                       rowStride);
            dest.write(reinterpret_cast<char *>(paddingBuffer.data()),
                       paddingBuffer.size());
        }
        dest.close();
    }
};

void monoFilter(std::vector<Color> &pixels) {
    for (auto &pixel : pixels) {
        float mono =
            (0.2125f * pixel.r) + (0.7154f * pixel.g) + (0.0721f * pixel.b);
        pixel.r = pixel.g = pixel.b = mono;
    }
}

int main() {
    try {
        BMP bmp;
        bmp.load("test-samples/640x426.bmp");
        monoFilter(bmp.pixels());
        bmp.save("result.bmp");
    } catch (const char *message) {
        std::cerr << message << std::endl;
    }
}