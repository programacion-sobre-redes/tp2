#include <iostream>
#include <unistd.h> // Para utilizar la función sleep
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "utils.h"

using namespace std;

vector<FilterStep> parsePipeline(int argc, char* argv[]) {
    vector<FilterStep> steps;
    for (int i = 4; i < argc; ++i) {
        string arg = argv[i];
        FilterStep step;

        // split on ':' para parámetros
        size_t colon = arg.find(':');
        if (colon != string::npos) {
            step.name = arg.substr(0, colon);
            string params = arg.substr(colon + 1);
            stringstream ss(params);
            string token;
            while (getline(ss, token, ',')) {
                step.parameters.push_back(token);
            }
        } else {
            step.name = arg;
        }

        steps.push_back(step);
    }
    return steps;
}
