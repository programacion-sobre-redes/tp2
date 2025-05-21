#include "filters.h"
#include <cmath>
#include <thread>
#include <unistd.h>
#include <semaphore>

/**
 * @brief Estructura para almacenar los distintos filtros disponibles para aplicar a las imágenes.
 * @details Se utiliza un mapa para asociar el nombre del filtro con su función correspondiente.
 * Para registrar un nuevo filtro, se utiliza la función registerFilter.
 */
map<string, FilterFunc> filterRegistry = {
    // Aquí se pueden registrar los filtros disponibles
};

void applyFilter(BmpImage& img, const string& filterName, const vector<string>& params, int threads) {
    auto it = filterRegistry.find(filterName);
    if (it != filterRegistry.end()) {
        it->second(img, params, threads);
    } else {
        throw runtime_error("Filtro '" + filterName + "' no registrado.");
    }
}

void registerFilter(const string& name, FilterFunc func) {
    filterRegistry[name] = func;
}

void applyPixelFilter(BmpImage& img, function<RGB(const RGB&, const vector<string>&)> pixelFunc, const vector<string>& params, int threads) {
    // Completar (una vez que estén todos los filtros de la parte 1 implementados)
}

void applyKernelFilter(BmpImage& img, function<RGB(const BmpImage&, int, int, const vector<string>&)> kernelFunc, const vector<string>& params, int threads) {
    // Completar (una vez que estén todos los filtros de la parte 1 implementados)
}

void identityFilter(BmpImage& img, const vector<string>& params, int threads) {
    // Completar
}

void negativeFilter(BmpImage& img, const vector<string>& params, int threads) {
    // Completar
}

void grayscaleFilter(BmpImage& img, const vector<string>& params, int threads) {
    // Completar
}

void thresholdFilter(BmpImage& img, const vector<string>& params, int threads) {
    // Completar
}

void boxBlurFilter(BmpImage& img, const vector<string>& params, int threads) {
    // Completar
}

void unsharpMaskFilter(BmpImage& img, const vector<string>& params, int threads) {
    // Completar
}

void registerFilters() {
    // Registrar los que van implementando
    // registerFilter("identity", identityFilter);
    // registerFilter("negative", negativeFilter);
    // registerFilter("grayscale", grayscaleFilter);
    // registerFilter("threshold", thresholdFilter);
    // registerFilter("boxblur", boxBlurFilter);
    // registerFilter("unsharp", unsharpMaskFilter);
}