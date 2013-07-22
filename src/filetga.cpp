#include "filetga.h"

#include <cstring> // memcmp
#include <iostream>
#include <fstream>

using namespace std;

// These are offsets into the TGA header, relative from the start of the file.
// See https://en.wikipedia.org/wiki/Truevision_TGA
enum {
    ID_LENGTH = 0,       // 1 byte
    COLOR_MAP_TYPE = 1,  // 1 byte
    IMAGE_TYPE = 2,      // 1 byte
    COLOR_MAP_SPEC = 3,  // 5 bytes
    IMAGE_SPEC = 8,      // 10 bytes
        X_ORIGIN = 8,    // 2 bytes
        Y_ORIGIN = 10,   // 2 bytes
        WIDTH = 12,      // 2 bytes, little endian
        HEIGHT = 14,     // 2 bytes, little endian
        BPP = 16,        // 1 byte
        IMAGE_DESC = 17, // 1 byte
    DATA = 18            // The rest of the file.
};

static const int SIGNATURE_LEN = 12;
static const GLubyte uncompressedTgaSignature[SIGNATURE_LEN] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static const GLubyte compressedTgaSignature[SIGNATURE_LEN] = { 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static bool loadHeader(const string& fileName, const vector<GLubyte>& data, File::Tga::Image& image) {
    if (memcmp(uncompressedTgaSignature, &data[0], sizeof(SIGNATURE_LEN)) == 0) {
        image.isCompressed = false;
	} else if (memcmp(compressedTgaSignature, &data[0], sizeof(SIGNATURE_LEN)) == 0) {
        image.isCompressed = true;
	} else {
        cerr << "Unrecognized TGA file format in " << fileName << endl;
        return false;
	}

    image.width = data[WIDTH + 1] * 256 + data[WIDTH];
    image.height = data[HEIGHT + 1] * 256 + data[HEIGHT];
    image.bpp = data[BPP];

    if (image.width <= 0 || image.height <= 0 || (image.bpp != 24 && image.bpp !=32)) {
        cerr << "Bad header values (width/height/bpp) for " << fileName << endl;
        return false;
	}

    image.internalFormat = (image.bpp == 24) ? GL_RGB8 : GL_RGBA8;
    image.format = (image.bpp == 24) ? GL_RGB : GL_RGBA;
    
    const auto bytespp = image.bpp / 8;
    image.data = vector<GLubyte>(bytespp * image.width * image.height);
    return true;
}

static bool loadUncompressed(const string& fileName, const vector<GLubyte>& data, File::Tga::Image& image) {
    image.isValid = false;

    auto availableData = data.size() - DATA;
    if (availableData != image.data.size()) {
        cerr << "Not enough data in " << fileName << endl;
        return false;
    }
    memcpy(reinterpret_cast<char*>(&image.data[0]),
           reinterpret_cast<const char*>(&data[DATA]),
           image.data.size());

    // BGRA -> RGBA conversion
    const auto bytespp = image.bpp / 8;
    const auto len = image.data.size();
    for (auto i = 0u; i < len; i += bytespp) {
        auto temp = image.data[i + 0];
        image.data[i + 0] = image.data[i + 2];
        image.data[i + 2] = temp;
    }

    image.isValid = true;
    return true;
}

// NOTE: The performance of this loader is not very good!
// It causes a delay at startup when we load the textures.
static bool loadCompressed(const string& fileName, const vector<GLubyte>& data, File::Tga::Image& image) {
    image.isValid = false;

    auto p = unsigned(DATA); // Current position in data.
    auto availableData = data.size() - DATA;
    const auto bytespp = image.bpp / 8;
    const auto totalBytes = bytespp * image.width * image.height;
    auto offs = 0u;
    GLubyte chunkHeader = 0u;

    while (offs < totalBytes) {
        if (availableData < 1) {
            cerr << "Error! Cannot read chunk header from " << fileName << endl;
            return false;
        }
        chunkHeader = data[p++];
        if (chunkHeader < 128) {
            // chunkHeader : number of raw color packets - 1.
            ++chunkHeader;
            for (auto i = 0u; i < chunkHeader; ++i, offs += bytespp, p += bytespp) {
                if (offs >= totalBytes) {
                    cerr << "Error! Too many bytes in " << fileName << endl;
                    return false;
                }
                if (availableData < bytespp) {
                    cerr << "Cannot read pixel data from " << fileName << endl;
                    return false;
				}
                image.data[offs] = data[p + 2]; // R
                image.data[offs + 1] = data[p + 1]; // G
                image.data[offs + 2] = data[p]; // B
                if (bytespp == 4) {
                    image.data[offs + 3] = data[p + 3]; // A
                }
            }
        } else {
            // chunkHeader : next color repeated chunkHeader - 127 times.
            chunkHeader -= 127;
            if (availableData < bytespp) {
                cerr << "Cannot read pixel from " << fileName << endl;
                return false;
			}
			for (auto i = 0u; i < chunkHeader; ++i, offs += bytespp) {
                if (offs >= totalBytes) {
                    cerr << "Error! Too much data in " << fileName << endl;
                    return false;
                }
                image.data[offs] = data[p + 2]; // R
                image.data[offs + 1] = data[p + 1]; // G
                image.data[offs + 2] = data[p]; // B
                if (bytespp == 4) {
                    image.data[offs + 3] = data[p + 3]; // A
                }
            }
            p += bytespp;
        }
    } while (offs < totalBytes);

    image.isValid = true;
    return true;
}

bool File::Tga::texImage2d(const string& fileName) {
    const auto& image = load(fileName);
    if (!image.isValid) {
        return false;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, image.internalFormat,
                image.width, image.height, 0,
                image.format, GL_UNSIGNED_BYTE,
                reinterpret_cast<const void*>(&image.data[0]));
    return true;
}

File::Tga::Image File::Tga::load(const string& fileName) {
    // Read the entire file into memory.
    ifstream ifs;
    ifs.open(fileName, ios::binary | ios::in);
    if (!ifs.is_open()) {
        cerr << "Cannot open TGA from " << fileName << endl;
        return Image();
	}
    ifs.seekg(0, ios::end);
    auto fileSize = ifs.tellg();
    ifs.seekg(0, ios::beg);
    auto data = vector<GLubyte>(static_cast<unsigned int>(fileSize));
    ifs.read(reinterpret_cast<char*>(&data[0]), fileSize);
    if (ifs.eof() || ifs.fail()) {
        cerr << "Cannot read data from " << fileName << endl;
        return Image();
    }
    ifs.close();

    Image image;
    if (!loadHeader(fileName, data, image)) {
        cerr << "Cannot load header from " << fileName << endl;
        return Image();
    }
    if (image.isCompressed && !loadCompressed(fileName, data, image)) {
        cerr << "Cannot load compressed data from " << fileName << endl;
        return Image();
	}
    if (!image.isCompressed && !loadUncompressed(fileName, data, image)) {
        cerr << "Cannot load uncompressed data from " << fileName << endl;
        return Image();
    }
    return image;
}

