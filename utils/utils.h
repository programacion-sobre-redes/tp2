#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <functional>
#include <map>

using namespace std;

struct FilterStep {
    string name;
    vector<string> parameters;
};

vector<FilterStep> parsePipeline(int argc, char* argv[]);

#endif // UTILS_H