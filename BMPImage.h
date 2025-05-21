#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

#pragma pack(push, 1)
struct BmpFileHeader {
    uint16_t fileType{0x4D42}; // "BM"
    uint32_t fileSize{0};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offsetData{0};
};

struct BmpInfoHeader {
    uint32_t size{0};
    int32_t width{0};
    int32_t height{0};
    uint16_t planes{1};
    uint16_t bitCount{0};
    uint32_t compression{0};
    uint32_t sizeImage{0};
    int32_t xPixelsPerMeter{0};
    int32_t yPixelsPerMeter{0};
    uint32_t colorsUsed{0};
    uint32_t colorsImportant{0};
};
#pragma pack(pop)

/**
 * @brief Estructura de color RGB.
 * Esta estructura representa un color en el espacio de color RGB.
 * Cada canal (rojo, verde, azul) está representado como un unsigned int de 8 bits.
 */
struct RGB {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

/**
 * @brief Clase de imagen BMP.
 * Esta clase proporciona métodos para cargar, guardar y manipular imágenes BMP.
 */
class BmpImage {
private:
    BmpFileHeader fileHeader;
    BmpInfoHeader infoHeader;
    vector<uint8_t> data;

public:
    /**
     * @brief Carga una imagen BMP desde un archivo.
     * @param filename El nombre del archivo a cargar.
     * @return True si la imagen se cargó correctamente, false en caso contrario.
     */
    bool load(const string& filename);
    /**
     * @brief Guarda la imagen en un archivo.
     * @param filename El nombre del archivo a donde se guardará la imagen. Importante incluir la extensión .bmp.
     * @note El archivo será sobrescrito si ya existe.
     * @return True si la imagen se guardó correctamente, false en caso contrario.
     */
    bool save(const string& filename) const;

    /**
     * @brief Obtiene el ancho de la imagen.
     * @return El ancho de la imagen en píxeles.
     */
    int getWidth() const { return infoHeader.width; }
    /**
     * @brief Obtiene la altura de la imagen.
     * @return La altura de la imagen en píxeles.
     */
    int getHeight() const { return infoHeader.height; }

    /**
     * @brief Obtiene el valor de un píxel en las coordenadas especificadas.
     * @param x La coordenada x del píxel.
     * @param y La coordenada y del píxel.
     * @return El color RGB del píxel.
     */
    RGB getPixel(int x, int y) const;
    /**
     * @brief Establece el valor de un píxel en las coordenadas especificadas.
     * @param x La coordenada x del píxel.
     * @param y La coordenada y del píxel.
     * @param color El color RGB a establecer en el píxel.
     */
    void setPixel(int x, int y, RGB color);

    /**
     * @brief Obtiene el row stride de la imagen.
     * @return El número de bytes en una fila de datos de píxeles.
     * Esto incluye los bytes de padding para asegurar que cada fila sea múltiplo de 4 bytes.
     */
    int getRowStride() const { return infoHeader.width * 3; }

    /**
     * @brief Obtiene el padding de la imagen.
     * @return El número de bytes de padding al final de cada fila.
     * Esto se calcula para asegurar que cada fila sea múltiplo de 4 bytes.
     */
    int getPadding() const { return (4 - (getRowStride() % 4)) % 4; }

    /**
     * @brief Obtiene los píxeles de una sección de la imagen.
     * @param x La coordenada x de la esquina superior izquierda de la sección.
     * @param y La coordenada y de la esquina superior izquierda de la sección.
     * @param width El ancho de la sección en píxeles.
     * @param height La altura de la sección en píxeles.
     * @return Un vector que contiene los datos de píxeles de la sección especificada.
     * @note Los valores de los píxeles se almacenan en un vector 1D, con cada píxel representado como una estructura RGB.
     * Los datos se almacenan en orden de filas. Si se quiere acceder al píxel por sus coordenadas,
     * se puede usar: pixelData[y * width + x].
     */
    vector<RGB> getSection(int x, int y, int width, int height) const;

    /**
     * @brief Establece los píxeles para una sección de la imagen.
     * @param x La coordenada x de la esquina superior izquierda de la sección.
     * @param y La coordenada y de la esquina superior izquierda de la sección.
     * @param sectionData Un vector que contiene los datos de píxeles de la sección especificada.
     * @param width El ancho de la sección en píxeles.
     * @param height La altura de la sección en píxeles.
     * @note Los datos en la sección especificada deben cumplir con el mismo formato que los que se obtienen
     * con getSection. Es decir, deben ser un vector 1D de estructuras RGB.
     */
    void setSection(int x, int y, const vector<RGB>& sectionData, int width, int height);
};