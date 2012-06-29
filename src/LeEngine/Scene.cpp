#include <GL/glew.h>
#include <GL/glfw.h>
#include <algorithm>
#include "Scene.h"
#include "Log.h"
#include "Renderer.h"

void Scene::AddRenderable(IRenderable* r)
{
    _objectList.push_back(r);
}

void Scene::RemoveRenderable(IRenderable* r)
{
    std::list<IRenderable*>::const_iterator itr = std::find(_objectList.begin(), _objectList.end(), r);
    if (itr != _objectList.end())
        _objectList.erase(itr);
    else
        LeLog << LOG_APP << "Tried to remove " << r->GetName() << " but renderable does not exist in rederable list" << NL;
}

void Scene::RenderObjectList() const
{
    for (std::list<IRenderable*>::const_iterator itr = _objectList.begin(); itr != _objectList.end(); ++itr)
        (*itr)->Render();
}
