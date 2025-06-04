#ifndef FILTERS_H
#define FILTERS_H

#include "../BMPImage.h"
#include <functional>
#include <vector>
#include <string>
#include <map>

/**
 * @brief Estructura para representar una función de filtro.
 * @details Esta estructura es un "tipo" que representa una función cualquiera que recibe
 * un objeto BmpImage, una lista de parámetros y un número de threads como argumentos.
 * Se utiliza para registrar filtros en el sistema.
 */
using FilterFunc = function<void(BmpImage&, const vector<string>&, int threads)>;

/**
 * @brief Registra un nuevo filtro en el sistema.
 * @param name Nombre del filtro.
 * @param func Función que implementa el filtro.
 */
void registerFilter(const string& name, FilterFunc func);

/**
 * @brief Registra todos los filtros disponibles.
 * @details Esta función se llama al inicio del programa para registrar todos los filtros
 * disponibles en el sistema.
 */
void registerFilters();

/**
 * @brief Aplica un filtro a una imagen.
 * @param img Imagen a la que se le aplicará el filtro.
 * @param filterName Nombre del filtro a aplicar.
 * @param params Parámetros del filtro.
 * @param threads Número de threads a utilizar (opcional).
 */
void applyFilter(BmpImage& img, const string& filterName, const vector<string>& params, int threads = 1);

/**
 * @brief Filtro de identidad (no realiza ninguna operación).
 * @param img Imagen a la que se le aplicará el filtro.
 * @param params Parámetros del filtro (no utilizados).
 * @param threads Número de threads a utilizar (opcional).
 */
void identityFilter(BmpImage& img, const vector<string>& params, int threads = 1);

/**
 * @brief Filtro de escala de grises (convierte la imagen a blanco y negro).
 * @param img Imagen a la que se le aplicará el filtro.
 * @param params Parámetros del filtro (no utilizados).
 * @param threads Número de threads a utilizar (opcional).
 */
void grayscaleFilter(BmpImage& img, const vector<string>& params, int threads = 1);

/**
 * @brief Filtro de escala de grises discreta (convierte la imagen a blanco y negro con una cantidad de grises fija)
 * @param img Imagen a la que se le aplicará el filtro.
 * @param params Parámetros del filtro (params[0] = cantidad de niveles de gris).
 * @param threads Número de threads a utilizar (opcional).
 */
void thresholdFilter(BmpImage& img, const vector<string>& params, int threads = 1);

/**
 * @brief Filtro negativo (invierte los colores de la imagen).
 * @param img Imagen a la que se le aplicará el filtro.
 * @param params Parámetros del filtro (no utilizados).
 * @param threads Número de threads a utilizar (opcional).
 */
void negativeFilter(BmpImage& img, const vector<string>& params, int threads = 1);

/**
 * @brief Aplica una función pixel a pixel sobre la imagen, usando múltiples hilos.
 * @param img Imagen a la que se le aplicará el filtro.
 * @param pixelFunc Función que toma un pixel y devuelve el pixel modificado.
 * @param params Parámetros del filtro. Dependen del filtro específico que se esté aplicando. No se modifican, simplemente se pasan a la función del pixel.
 * @param threads Número de threads a utilizar.
 */
void applyPixelFilter(BmpImage& img, function<RGB(const RGB&, const vector<string>&)> pixelFunc, const vector<string>& params,  int threads = 1);

/**
 * @brief Aplica una función basada en kernel sobre la imagen, usando múltiples hilos.
 * @param img Imagen a la que se le aplicará el filtro.
 * @param kernelFunc Función que toma la imagen, coordenadas x, y y el tamaño del kernel, y devuelve el pixel modificado.
 * @param params Parámetros del filtro. Dependen del filtro específico que se esté aplicando. No se modifican, simplemente se pasan a la función del kernel.
 * @param threads Número de threads a utilizar.
 */
void applyKernelFilter(BmpImage& img, function<RGB(const BmpImage&, int, int, const vector<string>&)> kernelFunc, const vector<string>& params, int threads = 1);

/**
 * @brief Filtro de umbral (threshold filter).
 * @param img Imagen a la que se le aplicará el filtro.
 * @param params Parámetros del filtro (params[0] = la cantidad de niveles de gris)
 * @param threads Número de threads a utilizar (opcional).
 */
RGB thresholdPixel(const RGB& pixel, const vector<string>& params);

/**
 * @brief Filtro de desenfoque de caja (box blur).
 * @param img Imagen a la que se le aplicará el filtro.
 * @param params Parámetros del filtro (params[0] = tamaño del kernel).
 * @param threads Número de threads a utilizar (opcional).
 */
void boxBlurFilter(BmpImage& img, const vector<string>& params, int threads = 1);

/**
 * @brief Filtro de máscara de desenfoque (unsharp mask).
 * @param img Imagen a la que se le aplicará el filtro.
 * @param params Parámetros del filtro (params[0] = tamaño del kernel, params[1] = fuerza de la máscara).
 * @param threads Número de threads a utilizar (opcional).
 */
void unsharpMaskFilter(BmpImage& img, const vector<string>& params, int threads = 1);

/* ----------------- AGREGAR ACÁ ↓↓↓ TODAS LAS DECLARACIONES DE FUNCIONES ----------------- */

#endif // FILTERS_H