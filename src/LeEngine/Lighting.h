#ifndef LIGHTING_H
#define LIGHTING_H

#include "Defines.h"
#include "Singleton.h"
#include "ITask.h"
#include "Vector.h"

#include <stack>
#include <set>

class Light; // Forward Declaration

class LightingManager : public ITask, public Singleton<LightingManager>
{
public:
    LightingManager();

    bool Start();
    void Update();
    void Stop();

    static Light* NewLight();
    static void   DeleteLight(Light* light);

    bool IsLightingEnabled() const { return _enabled; }
    void LightingEnabled(bool val);

private:
    //! Unused OpenGL lightsIDs
    static std::stack<uint32> lightsIDs;

    //! Pointers to created lights
    static std::set<Light*> lights;
    typedef std::set<Light*>::iterator lightIT;

    //! Enable or disable lighting
    bool _enabled;
};

class Light
{
protected:
    Light(uint32 id);

public:
    
    bool IsEnabled() const { return _enabled; }
    void Enabled(bool val);

    void Update();

    static const Vector<4, float> DEFAULT_AMBIENT;
    Vector<4, float> Ambient() const { return _ambient; }
    void Ambient(Vector<4, float> val);

    static const Vector<4, float> DEFAULT_DIFFUSE; 
    Vector<4, float> Diffuse() const { return _diffuse; }
    void Diffuse(Vector<4, float> val);

    static const Vector<4, float> DEFAULT_SPECULAR;
    Vector<4, float> Specular() const { return _specular; }
    void Specular(Vector<4, float> val);

    static const Vector<4, float> DEFAULT_POSITION;
    Vector<4, float> Position() const { return _position; }
    void Position(Vector<4, float> val);

    static const Vector<3, float> DEFAULT_SPOT_DIRECTION;
    Vector<3, float> SpotDirection() const { return _spotDirection; }
    void SpotDirection(Vector<3, float> val);

    static const float DEFAULT_SPOT_CUTOFF;
    float SpotCutOff() const { return _spotCutOff; }
    void SpotCutOff(float val);

    static const float DEFAULT_SPOT_EXPONENT;
    float SpotExponent() const { return _spotExponent; }
    void SpotExponent(float val);

    static const float DEFAULT_CONSTANT_ATTENUATION;
    float ConstantAttenuation() const { return _constantAttenuation; }
    void ConstantAttenuation(float val);

    static const float DEFAULT_LINEAR_ATTENUATION;
    float LinearAttenuation() const { return _linearAttenuation; }
    void LinearAttenuation(float val);

    static const float DEFAULT_QUADRATIC_ATTENUATION;
    float QuadraticAttenuation() const { return _quadraticAttenuation; }
    void QuadraticAttenuation(float val);

private:
    uint32 _lightID;
    bool _enabled;

    Vector<4, float> _ambient,    
                     _diffuse,
                     _specular,
                     _position;

    Vector<3, float> _spotDirection;

    float _spotCutOff,
          _spotExponent,
          _constantAttenuation,
          _linearAttenuation,
          _quadraticAttenuation;
    
    friend class LightingManager;
};



#endif // LIGHTING_H
