#include "Color.h"

// ColorRGB

ColorRGB::ColorRGB()
{
    memset(_values, 0, COLOR_RGB_SIZE*sizeof(float));
}

ColorRGB::ColorRGB(float r, float g, float b)
{
    _values[0] = ClampColor(r);
    _values[1] = ClampColor(g);
    _values[2] = ClampColor(b);
}

ColorRGB::ColorRGB(float vals[COLOR_RGB_SIZE])
{
    for (int i = 0; i < COLOR_RGB_SIZE; ++i)
        _values[i] = ClampColor(vals[i]);
}

ColorRGB::ColorRGB(const ColorRGB& other)
{
    memcpy(_values, other._values, COLOR_RGB_SIZE*sizeof(float));
}

ColorRGB& ColorRGB::operator=(const ColorRGB& other)
{
    memcpy(_values, other._values, COLOR_RGB_SIZE*sizeof(float));
    return *this;
}

ColorRGB::operator const float *() const
{
    return _values;
}

ColorRGB::operator float *()
{
    return _values;
}

ColorRGB::operator ColorRGBA() const
{
    return ColorRGBA(R(), G(), B(), 1.0f);
}

ColorRGB::operator ColorRGBA()
{
    return ColorRGBA(R(), G(), B(), 1.0f);
}

float ColorRGB::operator[](int i) const
{
    assert(i < COLOR_RGB_SIZE);
    return _values[i % COLOR_RGB_SIZE];
}

float& ColorRGB::operator[](int i)
{
    assert(i < COLOR_RGB_SIZE);
    return _values[i % COLOR_RGB_SIZE];
}

float ColorRGB::R() const
{
    return _values[0];
}

float& ColorRGB::R()
{
    return _values[0];
}

float ColorRGB::G() const
{
    return _values[1];
}

float& ColorRGB::G()
{
    return _values[1];
}

float ColorRGB::B() const
{
    return _values[2];
}

float& ColorRGB::B()
{
    return _values[2];
}

bool ColorRGB::operator==(const ColorRGB& other) const
{
    for (int i = 0; i < COLOR_RGB_SIZE; ++i)
        if (!Math<float>::IsFuzzyEqual(_values[i], other._values[i]))
            return false;
    return true;
}

bool ColorRGB::operator!=(const ColorRGB& other) const
{
    return !operator ==(other);
}

ColorRGB ColorRGB::operator+(const ColorRGB& other) const
{
    return ColorRGB((R() + other.R()) / 2.0f,
        (G() + other.G()) / 2.0f,
        (B() + other.B()) / 2.0f);
}

ColorRGB ColorRGB::operator-(const ColorRGB& other) const
{
    return ColorRGB((R() - other.R()) / 2.0f,
        (G() - other.G()) / 2.0f,
        (B() - other.B()) / 2.0f);
}

ColorRGB& ColorRGB::operator+=(const ColorRGB& other)
{
    R() = (R() + other.R()) / 2.0f;
    G() = (G() + other.G()) / 2.0f;
    B() = (B() + other.B()) / 2.0f;
    return *this;
}

ColorRGB& ColorRGB::operator-=(const ColorRGB& other)
{
    R() = (R() - other.R()) / 2.0f;
    G() = (G() - other.G()) / 2.0f;
    B() = (B() - other.B()) / 2.0f;
    return *this;
}

// ColorRGBA

ColorRGBA::ColorRGBA()
{
    memset(_values, 0, COLOR_RGBA_SIZE*sizeof(float));
}

ColorRGBA::ColorRGBA(float r, float g, float b, float a/*= 1.0f*/)
{
    _values[0] = ClampColor(r);
    _values[1] = ClampColor(g);
    _values[2] = ClampColor(b);
    _values[3] = ClampColor(a);
}

ColorRGBA::ColorRGBA(float vals[COLOR_RGBA_SIZE])
{
    for (int i = 0; i < COLOR_RGBA_SIZE; ++i)
        _values[i] = ClampColor(vals[i]);
}

ColorRGBA::ColorRGBA(const ColorRGBA& other)
{
    memcpy(_values, other._values, COLOR_RGBA_SIZE*sizeof(float));
}

ColorRGBA& ColorRGBA::operator=(const ColorRGBA& other)
{
    memcpy(_values, other._values, COLOR_RGBA_SIZE*sizeof(float));
    return *this;
}

ColorRGBA::operator const float *() const
{
    return _values;
}

ColorRGBA::operator float *()
{
    return _values;
}

ColorRGBA::operator ColorRGB() const
{
    return ColorRGB(R(), G(), B());
}

ColorRGBA::operator ColorRGB()
{
    return ColorRGB(R(), G(), B());
}


float ColorRGBA::operator[](int i) const
{
    assert(i < COLOR_RGBA_SIZE);
    return _values[i % COLOR_RGBA_SIZE];
}

float& ColorRGBA::operator[](int i)
{
    assert(i < COLOR_RGBA_SIZE);
    return _values[i % COLOR_RGBA_SIZE];
}

float ColorRGBA::R() const
{
    return _values[0];
}

float& ColorRGBA::R()
{
    return _values[0];
}

float ColorRGBA::G() const
{
    return _values[1];
}

float& ColorRGBA::G()
{
    return _values[1];
}

float ColorRGBA::B() const
{
    return _values[2];
}

float& ColorRGBA::B()
{
    return _values[2];
}

float ColorRGBA::A() const
{
    return _values[3];
}

float& ColorRGBA::A()
{
    return _values[3];
}

bool ColorRGBA::operator==(const ColorRGBA& other) const
{
    for (int i = 0; i < COLOR_RGBA_SIZE; ++i)
        if (!Math<float>::IsFuzzyEqual(_values[i], other._values[i]))
            return false;
    return true;
}

bool ColorRGBA::operator!=(const ColorRGBA& other) const
{
    return !operator ==(other);
}

ColorRGBA ColorRGBA::operator+(const ColorRGBA& other) const
{
    return ColorRGBA((R() + other.R()) / 2.0f,
        (G() + other.G()) / 2.0f,
        (B() + other.B()) / 2.0f,
        (A() + other.A()) / 2.0f);
}

ColorRGBA ColorRGBA::operator-(const ColorRGBA& other) const
{
    return ColorRGBA((R() + other.R()) / 2.0f,
        (G() - other.G()) / 2.0f,
        (B() - other.B()) / 2.0f,
        (A() - other.A()) / 2.0f);
}

ColorRGBA& ColorRGBA::operator+=(const ColorRGBA& other)
{
    R() = (R() + other.R()) / 2.0f;
    G() = (G() + other.G()) / 2.0f;
    B() = (B() + other.B()) / 2.0f;
    A() = (A() + other.A()) / 2.0f; // TODO: verify
    return *this;
}

ColorRGBA& ColorRGBA::operator-=(const ColorRGBA& other)
{
    R() = (R() - other.R()) / 2.0f;
    G() = (G() - other.G()) / 2.0f;
    B() = (B() - other.B()) / 2.0f;
    A() = (A() - other.A()) / 2.0f; // TODO: verify
    return *this;
}

ColorRGBA ColorRGBA::Blend(const ColorRGBA &other) const
{
    float ax = 1 - (1 - A()) * (1 - other.A());
    float rx = R() * A() / ax + other.R() * other.A() * (1 - A()) / ax;
    float gx = G() * A() / ax + other.G() * other.A() * (1 - A()) / ax;
    float bx = B() * A() / ax + other.B() * other.A() * (1 - A()) / ax;

    return ColorRGBA(rx, gx, bx, ax);
}
