
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include"mat.h"

const float YAW = -90;
const float PITCH = 0;
const float ZOOM = 45;

class Camera{
public:
    vec3 Position;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;
    float Yaw;
    float Pitch;
    float Zoom;

    Camera(){};
    
    Camera(vec3 position = vec3(),vec3 front = vec3(0,0,-1),vec3 up = vec3(0,1,0),float yaw = YAW,float pitch = PITCH,float zoom = ZOOM)
    : WorldUp()
    {
        Position = position;
        Front = front;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        Zoom = zoom;

        updateCameraVectors();
    };

    mat4 get_viewMatrix(){
        return lookAt(Position,Position + Front,Up);
    };
protected:
    void updateCameraVectors()
    {
        vec3 front;
        front.x = cos(Math::radians(Yaw)) * cos(Math::radians(Pitch));
        front.y = sin(Math::radians(Pitch));
        front.z = sin(Math::radians(Yaw)) * cos(Math::radians(Pitch));
        front.normalize();

        Front = front;
        Right = cross(Front, WorldUp);  
        Right.normalize();
        Up = cross(Right, Front);
        Up.normalize();
    }
};

#endif 