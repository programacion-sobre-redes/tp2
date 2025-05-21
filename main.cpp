#include "utils/utils.h"
#include "filters/filters.h"
#include <vector>
#include <iostream>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {
    // Comprobar si se pasaron argumentos
    if (argc < 4) {
        cerr << "Uso: " << argv[0] << " <entrada.bmp> <salida.bmp> <threads> <filtro1:p1?,p2?,...> [<filtro2:p1?,p2?> ...]\n";
        return 1;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];
    int threads = stoi(argv[3]);
    vector<FilterStep> steps = parsePipeline(argc, argv);

    // Imprimir los pasos del pipeline
    for (const auto& step : steps) {
        cout << "Filtro: " << step.name << "\n";
        if (!step.parameters.empty()) {
            cout << "   Parametros: ";
            for (const auto& param : step.parameters) {
                cout << param << " ";
            }
            cout << "\n";
        }
    }

    BmpImage img;
    if (!img.load(inputFile)) {
        cerr << "No se pudo cargar la imagen.\n";
        return 1;
    }

    // Registrar todos los filtros disponibles
    registerFilters();

    auto start = std::chrono::high_resolution_clock::now();

    for (const auto& step : steps) {
        try {
            applyFilter(img, step.name, step.parameters, threads);
        } catch (const exception& e) {
            cerr << "Error aplicando el filtro " << step.name << ": " << e.what() << "\n";
            return 1;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    cout << "Tiempo de procesamiento: " << elapsed.count() << " segundos" << endl;

    img.save(outputFile);
    return 0;
}
