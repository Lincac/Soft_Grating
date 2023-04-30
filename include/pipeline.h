#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include<iostream>
#include"ppmimage.h"
#include"mat.h"
#include<map>
#include<vector>

struct vertex_Shader{
    vec3 normal;

    mat4 MVP;

    vec2 uv[3];

    vec3 out_vec[3];
};

struct fragment_Shader{
    PPMColor color;
};

class Pipeline{
public:
    Pipeline(int w,int h);
    ~Pipeline();

    void set_vertex(std::vector<vec3> vertex);
    void set_index(std::vector<int> index);
    void set_uv(std::vector<vec2> texcoord);

    void set_vertexShader(vertex_Shader &shader);
    void set_fragmentShader(fragment_Shader &shader);

    void set_texbuffer(PPMImage &tex);

    void clearColor(){
        colorbuffer.clear();
    };
    void clearZ(){
        zbuffer.clear(1);
    };

    void Draw_line() ;
    void Draw_triangle() ;
protected:
    std::vector<vec3> vertices;
    std::vector<int> indexs;
    std::vector<vec2> uv;

    vertex_Shader vertshader;
    fragment_Shader fragshader;

    PPMImage colorbuffer;
    PPMImage zbuffer;
    PPMImage texbuffer;

    void vertexShader_process(const vec3 &v1,const vec3 &v2,const vec3 &v3);
    void fragmentShader_process(const vec3 &v1,const vec3 &v2,const vec3 &v3);

    void line(int x0,int y0,int x1,int y1);

    vec3 barycentric(vec2 A,vec2 B,vec2 C,vec2 P);
    void triangle(vec2 v1,vec2 v2,vec2 v3);
};

#endif 