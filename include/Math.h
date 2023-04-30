#ifndef _Math_H_
#define _Math_H_

#include <math.h>

namespace Math{
    const float PI = 3.1415926;

    inline float radians(float r){
        return r * (PI / 180);
    }

    inline float cot(float angle){
        return 1 / tan(radians(angle));
    }
}


#endif 