#ifndef SCENE_H
#define SCENE_H

#include <list>

class IRenderable;

class Scene
{
public:
    void AddRenderable(IRenderable* r);
    void RemoveRenderable(IRenderable* r);

    void RenderObjectList() const;

private:
    std::list<IRenderable*> _objectList;
};

#endif // SCENE
