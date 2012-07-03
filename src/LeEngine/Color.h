#ifndef COLOR_H
#define COLOR_H

#include <cstring> // memset
#include "DMath.h"

#define COLOR_RGB_SIZE 3
#define COLOR_RGBA_SIZE 4
#define ClampColor(val) Math<float>::Clamp(val, 0.0f, 1.0f);

class ColorRGBA;

//! A triplet of colors with the range [0,1]
class ColorRGB
{
protected:
    float _values[COLOR_RGB_SIZE];

public:
    ColorRGB(); //!> Default constructor, black color
    ColorRGB(float r, float g, float b); //!> Constructor. Values between 0 and 1
    ColorRGB(float vals[COLOR_RGB_SIZE]); //!> Constructor. Values between 0 and 1 in an array
    ColorRGB(const ColorRGB& other); //!> Copy constructor

    ColorRGB& operator =(const ColorRGB& other);

    operator const float *() const; //!> Cast to float*
    operator float *(); //!> Cast to float*
    operator ColorRGBA() const; //!> Cast to ColorRGBA (alpha=1)
    operator ColorRGBA(); //!> Cast to ColorRGBA (alpha=1)

    float operator [](int i) const; //!> Indexer
    float& operator [](int i); //!> Indexer

    float R() const; //!> Red
    float& R(); //!> Red
    float G() const;  //!> Green
    float& G(); //!> Green
    float B() const;  //!> Blue
    float& B(); //!> Blue

    bool operator ==(const ColorRGB& other) const;
    bool operator !=(const ColorRGB& other) const;

    ColorRGB operator +(const ColorRGB& other) const;
    ColorRGB operator -(const ColorRGB& other) const;

    ColorRGB& operator +=(const ColorRGB& other);
    ColorRGB& operator -=(const ColorRGB& other);

    static const ColorRGB BLACK;
    static const ColorRGB NAVY;
    static const ColorRGB GREEN;
    static const ColorRGB TEAL;
    static const ColorRGB MAROON;
    static const ColorRGB PURPLE;
    static const ColorRGB OLIVE;
    static const ColorRGB SILVER;
    static const ColorRGB GRAY;
    static const ColorRGB BLUE;
    static const ColorRGB LIME;
    static const ColorRGB AQUA;
    static const ColorRGB RED;
    static const ColorRGB FUCHSIA;
    static const ColorRGB YELLOW;
    static const ColorRGB WHITE;
};

//! A triplet of colors with the range [0,1] plus alpha channel
class ColorRGBA
{
protected:
    float _values[COLOR_RGBA_SIZE];

public:
    ColorRGBA(); //!> Default constructor, black color
    ColorRGBA(float r, float g, float b, float a = 1.0f); //!> Constructor. Values between 0 and 1
    ColorRGBA(float vals[COLOR_RGBA_SIZE]); //!> Constructor. Values between 0 and 1 in an array
    ColorRGBA(const ColorRGBA& other); //!> Copy constructor

    ColorRGBA& operator =(const ColorRGBA& other);

    operator const float *() const; //!> Cast to float*
    operator float *(); //!> Cast to float*
    operator ColorRGB() const; //!> Cast to ColorRGB (loses alpha info)
    operator ColorRGB(); //!> Cast to ColorRGB (loses alpha info)

    float operator [](int i) const; //!> Indexer
    float& operator [](int i); //!> Indexer

    float R() const; //!> Red
    float& R(); //!> Red
    float G() const;  //!> Green
    float& G(); //!> Green
    float B() const;  //!> Blue
    float& B(); //!> Blue
    float A() const;  //!> Alpha
    float& A(); //!> Alpha

    bool operator ==(const ColorRGBA& other) const;
    bool operator !=(const ColorRGBA& other) const;

    ColorRGBA operator +(const ColorRGBA& other) const;

    ColorRGBA operator -(const ColorRGBA& other) const;

    ColorRGBA& operator +=(const ColorRGBA& other);
    ColorRGBA& operator -=(const ColorRGBA& other);

    //! Blending using alpha channel
    ColorRGBA Blend(const ColorRGBA &other) const;
};

#endif // COLOR_H
