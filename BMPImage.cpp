#include "BmpImage.h"

bool BmpImage::load(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) return false;

    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    if (fileHeader.fileType != 0x4D42 || infoHeader.bitCount != 24 || infoHeader.compression != 0) {
        cerr << "Unsupported BMP format or compression." << endl;
        return false;
    }

    if (infoHeader.width <= 0 || infoHeader.height <= 0) {
        cerr << "Invalid image dimensions." << endl;
        return false;
    }

    int padding = getPadding();
    int rowStride = getRowStride();

    size_t dataSize = (rowStride + padding) * infoHeader.height;
    data.resize(dataSize);

    file.seekg(fileHeader.offsetData, ios::beg);
    file.read(reinterpret_cast<char*>(data.data()), dataSize);

    return true;
}

bool BmpImage::save(const std::string& filename) const {
    std::ofstream out(filename, std::ios::binary);
    if (!out) return false;

    // Escribir headers
    out.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    out.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));

    // Relleno si el offset es mayor que 54
    int headerSize = sizeof(fileHeader) + sizeof(infoHeader);
    if (fileHeader.offsetData > headerSize) {
        int extraHeader = fileHeader.offsetData - headerSize;
        std::vector<char> padding(extraHeader, 0);
        out.write(padding.data(), extraHeader);
    }

    // Cálculo de padding
    int rowStride = infoHeader.width * 3;
    int padding = (4 - (rowStride % 4)) % 4;
    std::vector<uint8_t> rowPadding(padding, 0);

    int height = std::abs(infoHeader.height);
    for (int y = 0; y < height; ++y) {
        out.write(reinterpret_cast<const char*>(&data[y * rowStride]), rowStride);
        if (padding > 0)
            out.write(reinterpret_cast<const char*>(rowPadding.data()), padding);
    }

    return true;
}

RGB BmpImage::getPixel(int x, int y) const {
    int row = infoHeader.height - 1 - y;
    int rowStride = getRowStride();
    int padding = getPadding();
    int index = row * (rowStride + padding) + x * 3;
    return { data[index], data[index + 1], data[index + 2] };
}

void BmpImage::setPixel(int x, int y, RGB color) {
    int row = infoHeader.height - 1 - y;
    int rowStride = getRowStride();
    int padding = getPadding();
    int index = row * (rowStride + padding) + x * 3;
    data[index]     = color.blue;
    data[index + 1] = color.green;
    data[index + 2] = color.red;
}

vector<RGB> BmpImage::getSection(int xStart, int yStart, int xEnd, int yEnd) const {
    int width = xEnd - xStart;
    int height = yEnd - yStart;
    if (width <= 0 || height <= 0) {
        cerr << "Invalid section dimensions." << endl;
        throw invalid_argument("Invalid section dimensions");
    }

    vector<RGB> sectionData(width * height);

    if (xStart < 0 || yStart < 0 || xStart + width > infoHeader.width || yStart + height > infoHeader.height) {
        cerr << "Section out of bounds." << endl;
        throw invalid_argument("Section out of bounds");
    }

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            if (xStart + i >= infoHeader.width || yStart + j >= infoHeader.height) {
                sectionData[(j * width + i)] = { 0, 0, 0 }; // Out of bounds, set to black
                continue;
            }
            sectionData[(j * width + i)] = getPixel(xStart + i, yStart + j);
        }
    }
    return sectionData;
}

void BmpImage::setSection(int xStart, int yStart, const vector<RGB>& sectionData, int xEnd, int yEnd) {
    int width = xEnd - xStart;
    int height = yEnd - yStart;
    if (width <= 0 || height <= 0) {
        cerr << "Invalid section dimensions." << endl;
        throw invalid_argument("Invalid section dimensions");
    }

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            setPixel(xStart + i, yStart + j, sectionData[j * width + i]);
        }
    }
}