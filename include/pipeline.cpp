#include"pipeline.h"

Pipeline::Pipeline(int w,int h):colorbuffer(w,h),zbuffer(w,h,1),texbuffer(){
    // 因为PPMimage中存在指针变量
    // colorbuffer = PPMimage(w,h);此处会调用PPMimage的构造函数，然后执行PPMimage的等号赋值运算符，然后执行PPMimage的析构函数
    // 如果没有则会引起内存泄露（因为默认的复制只是简单变量转移）

    texbuffer.read_ppm_file("resource/texture/brickwall.jpg");
}

Pipeline::~Pipeline(){}

void Pipeline::set_vertex(std::vector<vec3> vertex){
    vertices = vertex;
}

void Pipeline::set_index(std::vector<int> index){
    indexs = index;
}

void Pipeline::set_uv(std::vector<vec2> texcoord){
    uv = texcoord;
}

void Pipeline::set_vertexShader(vertex_Shader &shader){
    vertshader = shader;
}

void Pipeline::set_fragmentShader(fragment_Shader &shader){
    fragshader = shader;
}

void Pipeline::set_texbuffer(PPMImage &tex){
    texbuffer = tex;
}

void Pipeline::Draw_line(){
    int width = colorbuffer.get_width();
    int height = colorbuffer.get_height();

    for (int i = 0; i < indexs.size(); i+=3)
    {
        vec3 v0 = vertices[indexs[i + 0]];
        vec3 v1 = vertices[indexs[i + 1]];
        vec3 v2 = vertices[indexs[i + 2]];

        vertshader.uv[0] = uv[indexs[i + 0]];
        vertshader.uv[1] = uv[indexs[i + 1]];
        vertshader.uv[2] = uv[indexs[i + 2]];

        // // 顶点着色器处理（-1,1）
        vertexShader_process(v0,v1,v2);

        // // 视口变换
        vec3 vp0 = vec3(int((vertshader.out_vec[0].x + 1.0) * width / 2),int((vertshader.out_vec[0].y + 1.0) * height / 2),(vertshader.out_vec[0].z + 1) / 2);
        vec3 vp1 = vec3(int((vertshader.out_vec[1].x + 1.0) * width / 2),int((vertshader.out_vec[1].y + 1.0) * height / 2),(vertshader.out_vec[1].z + 1) / 2);
        vec3 vp2 = vec3(int((vertshader.out_vec[2].x + 1.0) * width / 2),int((vertshader.out_vec[2].y + 1.0) * height / 2),(vertshader.out_vec[2].z + 1) / 2);

        //  片段着色器处理
        fragmentShader_process(vp0,vp1,vp2);  
    }

    colorbuffer.write_ppm_file("out_line.ppm");
}

void Pipeline::Draw_triangle(){
    int width = colorbuffer.get_width();
    int height = colorbuffer.get_height();


    for (int i = 0; i < indexs.size(); i+=3)
    {
        //  此处所有顶点都是经过归一化的数据[-1,1]
        vec3 v0 = vertices[indexs[i + 0]];
        vec3 v1 = vertices[indexs[i + 1]];
        vec3 v2 = vertices[indexs[i + 2]];

        vertshader.uv[0] = uv[indexs[i + 0]];
        vertshader.uv[1] = uv[indexs[i + 1]];
        vertshader.uv[2] = uv[indexs[i + 2]];

        // 顶点着色器处理 
        vertexShader_process(v0,v1,v2);

        // 视口变换 x(0,width) y(0,height) z(0,1)
        vec3 vp0 = vec3(int((vertshader.out_vec[0].x + 1.0) * width / 2),int((vertshader.out_vec[0].y + 1.0) * height / 2),(vertshader.out_vec[0].z + 1) / 2);
        vec3 vp1 = vec3(int((vertshader.out_vec[1].x + 1.0) * width / 2),int((vertshader.out_vec[1].y + 1.0) * height / 2),(vertshader.out_vec[1].z + 1) / 2);
        vec3 vp2 = vec3(int((vertshader.out_vec[2].x + 1.0) * width / 2),int((vertshader.out_vec[2].y + 1.0) * height / 2),(vertshader.out_vec[2].z + 1) / 2);

        // 片段着色器处理
        fragmentShader_process(vp0,vp1,vp2); 
    }

    colorbuffer.write_ppm_file("out_triangle.ppm");
}

void Pipeline::vertexShader_process(const vec3 &v0,const vec3 &v1,const vec3 &v2){
    vertshader.normal = cross(v1 - v0,v2 - v0); 
    vertshader.normal.normalize();

    vec4 tempv0 = vertshader.MVP * vec4(v0,1);
    vec4 tempv1 = vertshader.MVP * vec4(v1,1);
    vec4 tempv2 = vertshader.MVP * vec4(v2,1); // MVP变换

    vertshader.out_vec[0] = vec3(tempv0.x / tempv0.w,tempv0.y / tempv0.w,tempv0.z / tempv0.w);
    vertshader.out_vec[1] = vec3(tempv1.x / tempv1.w,tempv1.y / tempv1.w,tempv1.z / tempv1.w);
    vertshader.out_vec[2] = vec3(tempv2.x / tempv2.w,tempv2.y / tempv2.w,tempv2.z / tempv2.w); // 透视除法
}

void Pipeline::fragmentShader_process(const vec3 &v1,const vec3 &v2,const vec3 &v3){
    // line(v1.x,v1.y,v2.x,v2.y);
    // line(v2.x,v2.y,v3.x,v3.y);
    // line(v3.x,v3.y,v1.x,v1.y);

    float itensity = dot(vertshader.normal,vec3(1));
    if(itensity > 0.){
        fragshader.color = PPMColor(itensity);
        triangle(vec2(v1.x,v1.y),vec2(v2.x,v2.y),vec2(v3.x,v3.y));        
    }
}

void Pipeline::line(int x0,int y0,int x1,int y1){
    bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    int dx = x1-x0; 
    int dy = y1-y0; 
    int derror2 = std::abs(dy)*2; 
    int error2 = 0; 
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            colorbuffer.set(y, x, fragshader.color); 
        } else { 
            colorbuffer.set(x, y, fragshader.color); 
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1>y0?1:-1); 
            error2 -= dx*2; 
        } 
    } 
}

vec3 Pipeline::barycentric(vec2 A,vec2 B,vec2 C,vec2 P){
    vec3 t1 = vec3(C.x - A.x,B.x - A.x,A.x - P.x);
    vec3 t2 = vec3(C.y - A.y,B.y - A.y,A.y - P.y);

    vec3 u = cross(t1,t2);
    if (std::abs(u.z)>1e-2)
        return vec3(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z);
    return vec3(-1,1,1);
}

void Pipeline::triangle(vec2 v1,vec2 v2,vec2 v3){
    vec2 maxBox = vmax(v1,vmax(v2,v3));
    vec2 minBox = vmin(v1,vmin(v2,v3));

    maxBox = vmin(vec2(colorbuffer.get_width() - 1,colorbuffer.get_height() - 1),maxBox);
    minBox = vmax(vec2(0),minBox);

    vec2 tempPos;
    for (tempPos.y = minBox.y; tempPos.y <= maxBox.y; tempPos.y++) 
    {
        for (tempPos.x = minBox.x; tempPos.x <= maxBox.x; tempPos.x++)
        {
            vec3 bc_screen = barycentric(v1,v2,v3,tempPos);
            if(bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) continue;

            float screenz = zbuffer.get_color(tempPos.x,tempPos.y).r;

            float currentz = 0;
            currentz += bc_screen.x * vertshader.out_vec[0].z;
            currentz += bc_screen.y * vertshader.out_vec[1].z;
            currentz += bc_screen.z * vertshader.out_vec[2].z;

            if(currentz >= screenz) continue;

            vec2 tempuv;
            tempuv.x = bc_screen.x * vertshader.uv[0].x + bc_screen.y * vertshader.uv[1].x + bc_screen.z * vertshader.uv[2].x;
            tempuv.y = bc_screen.x * vertshader.uv[0].y + bc_screen.y * vertshader.uv[1].y + bc_screen.z * vertshader.uv[2].y;

            if(texbuffer.get_width() != 0){
                fragshader.color = texbuffer.get_color(tempuv.x * texbuffer.get_width(),tempuv.y * texbuffer.get_height());
            }

            colorbuffer.set(int(tempPos.x),int(tempPos.y),fragshader.color);
            zbuffer.set(int(tempPos.x),int(tempPos.y),PPMColor(currentz));
        }
    }
}