#ifndef RENDERER_H
#define RENDERER_H

#include <string>

class IRenderable
{
public:
    IRenderable() : _name("") {}
    IRenderable(std::string name) : _name(name) {}

    virtual void Render() const = 0;

    const std::string& GetName() const { return _name; }

private:
    std::string _name;
};

// class Rendered...
// class RenderQueue...

#endif // RENDERER_H
