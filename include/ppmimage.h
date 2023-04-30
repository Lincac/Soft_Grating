#ifndef _IMAGE_H_
#define _IMAGE_H_

#include<fstream>
#include<iostream>
#include<string.h>
#include"stb_image.h"
#include"vec.h"

#define bytespp 3

struct PPMColor {
    union{// 联合体（其中只能有一个变量可以有值，并且大小按照变量最大的来存,如果有结构体，则需要内存对齐）
        struct{
            float r,g,b;
        };
        float raw[3] = {};
    };

    PPMColor() : r(0),g(0),b(0){};

    PPMColor(float v) : r(v),g(v),b(v){};

    PPMColor(const float* r) {
        for (int i = 0; i < bytespp; i++)
            raw[i] = r[i];
    }

    PPMColor(const vec3& v){
        r = v.x;
        g = v.y;
        b = v.z;
    }

    PPMColor(float R,float G,float B) : r(R),g(G),b(B){}

    PPMColor(const PPMColor &ppm){
        for (int i = 0; i < bytespp; i++)
            raw[i] = ppm.raw[i];
    };

    PPMColor& operator = (const PPMColor &ppm){
        if(this != &ppm){
            for (int i = 0; i < bytespp; i++)
                raw[i] = ppm.raw[i];
        }
        return *this;
    }
    
    PPMColor& operator *=(float t){
        r *= t;
        g *= t;
        b *= t;

        return *this;
    }
};

class PPMImage {
protected:
    float *data;
    int width;
    int height;
public:
    PPMImage();
    ~PPMImage();
    PPMImage(const PPMImage& ppm);
    PPMImage(const int w, const int h,float c = 0);

    bool  read_ppm_file(const char* filename);
    bool write_ppm_file(const char* filename) const;

    bool flip_horizontally();
    bool flip_vertically();
    bool scale(int w,int h);

    bool set(const int x, const int y, const PPMColor &c);
    PPMColor get_color(int x,int y);

    int get_width()  const;
    int get_height() const;

    void clear(float d = 0);
};

#endif 