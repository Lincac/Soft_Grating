
#ifndef _MODEL_H_
#define _MODEL_H_

#include <vector>
#include <string>
#include <sstream>
#include "ppmimage.h"
#include "vec.h"

#define INF 123456.0

class Model{
public:
    Model(const char* filenema);
    ~Model();

    std::vector<vec3> vertices;
    std::vector<int> index;
    std::vector<vec2> uv;
};

#endif