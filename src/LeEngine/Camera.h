#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:
    typedef Vector3<float> Position;
    struct Tracking
    {
        int32 startX,
              startY,
              tracking;
    };
    struct Coordinates
    {
        float alpha,
              beta,
              r;
    };
private:
    Position _position;
    Tracking _mouseTracking;
    Coordinates _sphericalCoordinates;

};

#endif // CAMERA_H