#include "Lighting.h"

#include "Defines.h"
#include "ITask.h"

#include <stack>
#include <set>
#include <algorithm>

#include <GL/glew.h>
#include <GL/glfw.h>

std::stack<uint32> LightingManager::lightsIDs;
std::set<Light*> LightingManager::lights;

const Vector<4, float> Light::DEFAULT_AMBIENT        = Vector<4,float>(0.0f,0.0f,0.0f,1.0f);
const Vector<4, float> Light::DEFAULT_DIFFUSE        = Vector<4,float>(0.0f,0.0f,0.0f,0.0f);
const Vector<4, float> Light::DEFAULT_SPECULAR       = Vector<4,float>(0.0f,0.0f,0.0f,0.0f);
const Vector<4, float> Light::DEFAULT_POSITION       = Vector<4,float>(0.0f,0.0f,1.0f,0.0f);
const Vector<3, float> Light::DEFAULT_SPOT_DIRECTION = Vector<3,float>(0.0f,0.0f,-1.0f);                                                                                      
const float Light::DEFAULT_SPOT_CUTOFF               = 180.0f;
const float Light::DEFAULT_SPOT_EXPONENT             = 0.0f;
const float Light::DEFAULT_CONSTANT_ATTENUATION      = 1.0f;
const float Light::DEFAULT_LINEAR_ATTENUATION        = 0.0f;
const float Light::DEFAULT_QUADRATIC_ATTENUATION     = 0.0f;

LightingManager::LightingManager() : ITask("Lighting Manager") 
{
    LightingEnabled(false);
}

bool LightingManager::Start()
{
    for (uint32 id = GL_LIGHT0 + GL_MAX_LIGHTS; id >= GL_LIGHT0; id--)
        lightsIDs.push(id);

    return true;
}

void LightingManager::Update()
{
    for (lightIT l = lights.begin(); l != lights.end(); l++)
    {
        if ((*l) != NULL && (*l)->IsEnabled())
            (*l)->Update();
    }
}

void LightingManager::Stop()
{
    for (lightIT l = lights.begin(); l != lights.end(); l++)
    {
        (*l)->Enabled(false);

        lightsIDs.push((*l)->_lightID);

        delete (*l);
    }

    lights.erase(lights.begin(),lights.end());
}

Light* LightingManager::NewLight()
{
    uint32 newID = lightsIDs.top();
    lightsIDs.pop();

    Light *newLight = new Light(newID);
    lights.insert(newLight);

    return newLight;
}


void LightingManager::DeleteLight(Light* light)
{
    if(light != NULL)
    {
        light->Enabled(false);

        lightsIDs.push(light->_lightID);
        
        lights.erase(light);

        delete light;
    }
}

void LightingManager::LightingEnabled( bool val )
{
    _enabled = val; 
    _enabled ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING);
}

Light::Light( uint32 id ) : _lightID(id)
{
    Enabled              (false);
    Ambient              (DEFAULT_AMBIENT);
    Diffuse              (DEFAULT_DIFFUSE);
    Specular             (DEFAULT_SPECULAR);
    Position             (DEFAULT_POSITION);
    SpotDirection        (DEFAULT_SPOT_DIRECTION);
    SpotCutOff           (DEFAULT_SPOT_CUTOFF);
    SpotExponent         (DEFAULT_SPOT_EXPONENT);
    ConstantAttenuation  (DEFAULT_CONSTANT_ATTENUATION);
    LinearAttenuation    (DEFAULT_LINEAR_ATTENUATION);
    QuadraticAttenuation (DEFAULT_QUADRATIC_ATTENUATION);
}

void Light::Enabled(bool val)
{
    _enabled = val; 
    _enabled ? glEnable(_lightID) : glDisable(_lightID);
}

void Light::Update()
{
    glLightfv(_lightID, GL_POSITION,_position);
}

void Light::Ambient( Vector<4, float> val )
{
    val[0] = Math<float>::Clamp(val[0], -1.0f, 1.0f);
    val[1] = Math<float>::Clamp(val[1], -1.0f, 1.0f);
    val[2] = Math<float>::Clamp(val[2], -1.0f, 1.0f);
    val[3] = Math<float>::Clamp(val[3], -1.0f, 1.0f);
    _ambient = val;
    glLightfv(_lightID, GL_AMBIENT, _ambient);
}

void Light::Diffuse( Vector<4, float> val )
{
    val[0] = Math<float>::Clamp(val[0], -1.0f, 1.0f);
    val[1] = Math<float>::Clamp(val[1], -1.0f, 1.0f);
    val[2] = Math<float>::Clamp(val[2], -1.0f, 1.0f);
    val[3] = Math<float>::Clamp(val[3], -1.0f, 1.0f);
    _diffuse = val;
    glLightfv(_lightID, GL_DIFFUSE, _diffuse);
}

void Light::Specular( Vector<4, float> val )
{
    val[0] = Math<float>::Clamp(val[0], -1.0f, 1.0f);
    val[1] = Math<float>::Clamp(val[1], -1.0f, 1.0f);
    val[2] = Math<float>::Clamp(val[2], -1.0f, 1.0f);
    val[3] = Math<float>::Clamp(val[3], -1.0f, 1.0f);
    _specular = val;
    glLightfv(_lightID, GL_SPECULAR, _specular);
}

void Light::Position( Vector<4, float> val )
{
    val[3] = Math<float>::Clamp(val[3], 0.0f, 1.0f);
    _position = val;
}

void Light::SpotDirection( Vector<3, float> val )
{
    _spotDirection = val;
    glLightfv(_lightID, GL_SPOT_DIRECTION, _spotDirection);
}

void Light::SpotCutOff( float val )
{
    if (Math<float>::IsFuzzyEqual(val, 180.0f))
        _spotCutOff = 180.0f;
    else
    {
        val = Math<float>::Clamp(val, 0.0f, 90.0f);
        _spotCutOff = val;
    }
    glLightf(_lightID, GL_SPOT_CUTOFF, _spotCutOff);
}

void Light::SpotExponent( float val )
{
    val = Math<float>::Clamp(val, 0.0f, 180.0f);
    _spotExponent = val;
    glLightf(_lightID, GL_SPOT_EXPONENT, _spotExponent);
}

void Light::ConstantAttenuation( float val )
{
    if (val < 0.0f)
        val = 0.0f;
    _constantAttenuation = val;
    glLightf(_lightID, GL_CONSTANT_ATTENUATION, _constantAttenuation);
}

void Light::LinearAttenuation( float val )
{
    if (val < 0.0f)
        val = 0.0f;
    _linearAttenuation = val;
    glLightf(_lightID, GL_LINEAR_ATTENUATION, _linearAttenuation);
}

void Light::QuadraticAttenuation( float val )
{
    if (val < 0.0f)
        val = 0.0f;
    _quadraticAttenuation = val;
    glLightf(_lightID, GL_QUADRATIC_ATTENUATION, _quadraticAttenuation);
}



