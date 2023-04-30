#include"include/pipeline.h"
#include"include/model.h"

// g++ -pg -o main .\main.cpp .\include\tgaimage.cpp
// .\main.exe
// gprof.exe -b .\main.exe .\gmon.out > report.txt

//          ^  y
//          |
//          |
//          |
//          |
//          |
//          | 
//          -----------------> x
//         /
//        /
//       /
//      /
//     /  z
//    >

const int width = 400;
const int height = 400;

int main(int argc,char** argv){
    // 初始化相机
    vec3 camera(0,0,3);

    mat4 model(1);
    mat4 view = lookAt(camera,vec3(0,0,0),vec3(0,1,0));
    mat4 projection = perspective(45,float(width) / float(height),0.1,100);
    mat4 MVP = projection * view * model;

    // 加载数据
    Model object("resource/quad.obj");

    Pipeline pipeline(width,height);

    // 上传顶点数据
    pipeline.set_vertex(object.vertices);
    pipeline.set_index(object.index);
    pipeline.set_uv(object.uv);

    //管线渲染
    vertex_Shader vert;
    vert.MVP = MVP;
    fragment_Shader frag;
    frag.color = PPMColor(1);

    pipeline.set_vertexShader(vert);
    pipeline.set_fragmentShader(frag);

    // 最终显示
    pipeline.Draw_triangle();

    return 0;
}