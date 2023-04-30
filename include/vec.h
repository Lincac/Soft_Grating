
#ifndef _VEC_H_
#define _VEC_H_

#include<cmath>
#include<iostream>
#include"Math.h"

struct vec2{
    union 
    {
        float data[2] = {};
        struct{
            float x,y;
        };
    };

    vec2(){x = y = 0;}
    vec2(float v0,float v1){x = v0;y = v1;}
    vec2(float v) {x = y = v;}
    vec2(const vec2& v){x = v.x;y = v.y;}

    inline vec2& operator =(const vec2& v){
        if(this != &v){
            x = v.x;
            y = v.y;
            return *this;
        }
        return *this;
    }

    inline vec2 operator +(const vec2 &v) const {return vec2(x + v.x,y + v.y);}
    inline vec2 operator -(const vec2 &v) const {return vec2(x - v.x,y - v.y);}
    inline vec2 operator *(float f) const {return vec2(x * f,y * f);}
    inline vec2 operator /(float f) const {return vec2(x / f,y / f);}

    inline float& operator [](int i) {return data[i];}

	friend std::ostream& operator <<(std::ostream& out , vec2& v) {
        out << v.x << ' ' << v.y << '\n';
        return out;
    }
};

struct vec3{
    union 
    {
        float data[3] = {};  
        struct 
        {
            float x,y,z;
        };
    };

    vec3(){x = y = z = 0;}
    vec3(float v0,float v1,float v2){x = v0;y = v1;z = v2;}
    vec3(float v) {x = y = z = v;}
    vec3(const vec3& v){
        if(this != &v){
            x = v.x;
            y = v.y;
            z = v.z;
        }
    }

    inline vec3& operator =(const vec3 &v){
        if(this != &v){
            x = v.x;
            y = v.y;
            z = v.z;
            return *this;
        }
        return *this;
    }

    inline vec3 operator +(const vec3 &v) const {return vec3(x + v.x,y + v.y,z + v.z);}
    inline vec3 operator -(const vec3 &v) const {return vec3(x - v.x,y - v.y,z - v.z);}
    inline vec3 operator- () {return vec3(-x,-y,-z);}
    inline vec3 operator *(float f) const {return vec3(x * f,y * f,z * f);}
    inline vec3 operator /(float f) const {return vec3(x / f,y / f,z / f);}
    inline float& operator [](int i) {return data[i];}

	friend std::ostream& operator <<(std::ostream& out , vec3& v) {
        out << v.x << ' ' << v.y << ' ' << v.z << '\n';
        return out;
    }

    inline void normalize(){
        float len = sqrt(x * x + y * y + z * z);
        x = x / len;
        y = y / len;
        z = z / len;
    }

    inline float length(){
        return sqrt(x * x + y * y + z * z);
    }
};

struct vec4{
    union 
    {
        struct{
            float x,y,z,w;
        };
        float data[4] = {};
    };
    
    vec4(){x = y = z = w = 0;}
    vec4(float v0,float v1,float v2,float v3){x = v0;y = v1;z = v2;w = v3;}
    vec4(float v) {x = y = z = w = v;}
    vec4(const vec3 &v,float v0){
        x = v.x;
        y = v.y;
        z = v.z;
        w = v0;
    }
    vec4(const vec4& v){
        if(this != &v){
            x = v.x;
            y = v.y;
            z = v.z;
            w = v.w;
        }
    }

    inline vec4& operator =(const vec4 &v){
        if(this != &v){
            x = v.x;
            y = v.y;
            z = v.z;
            w = v.w;
            return *this;
        }
        return *this;
    }

    inline vec4 operator +(const vec4 &v) const {return vec4(x + v.x,y + v.y,z + v.z,w + v.w);}
    inline vec4 operator -(const vec4 &v) const {return vec4(x - v.x,y - v.y,z - v.z,w - v.w);}
    inline vec4 operator *(float f) const {return vec4(x * f,y * f,z * f,w * f);}
    inline vec4 operator /(float f) const {return vec4(x / f,y / f,z / f,w / f);}
    inline float& operator [](int i) {return data[i];}
	friend std::ostream& operator <<(std::ostream& out , vec4& v) {
        out << v.x << ' ' << v.y << ' ' << v.z << ' ' <<  v.w << '\n';
        return out;
    }
};

inline float dot(const vec3 &v1,const vec3 &v2){
    float num = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return num;
}

inline vec3 cross(const vec3 &v1,const vec3 &v2){
    float n1 = v1.y * v2.z - v1.z * v2.y;
    float n2 = v1.z * v2.x - v1.x * v2.z;
    float n3 = v1.x * v2.y - v1.y * v2.x;

    return vec3(n1,n2,n3);
}

inline float mmin(const float x,const float y){
    return x < y ? x : y;
}

inline float mmax(const float x,const float y){
    return x > y ? x : y;
}

inline vec2 vmax(const vec2 &a,const vec2 &b){
    return vec2(mmax(a.x,b.x),mmax(a.y,b.y));
}

inline vec2 vmin(const vec2 &a,const vec2 &b){
    return vec2(mmin(a.x,b.x),mmin(a.y,b.y));
}

inline float clamp(float min,float max,float x){
    if( x < min) return min;
    if( x > max) return max;
    return x;
}

#endif