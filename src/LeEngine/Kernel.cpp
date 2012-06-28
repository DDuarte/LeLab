#include "Kernel.h"
#include "Log.h"
#include "Shapes.h"

#include <GL/glfw.h>

#include <algorithm>
#include <list>
#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

Kernel::Kernel() {}

Kernel::~Kernel() {}

int Kernel::Execute()
{
    while (_taskList.size())
    {
        std::list< shared_ptr<ITask> >::iterator it, thisIt;
        for (it = _taskList.begin(); it != _taskList.end();)
        {
            ITask* t = (*it).get();
            ++it;
            if (!t->CanKill)
                t->Update();
        }

        for (it = _taskList.begin(); it != _taskList.end();)
        {
            ITask* t = (*it).get();
            thisIt = it;
            ++it;
            if (t->CanKill)
            {
                t->Stop();
                _taskList.erase(thisIt);
                t = NULL;
            }
        }
    }

    return 0;
}

bool Kernel::AddTask(const shared_ptr<ITask>& t)
{
    if (!t->Start())
    {
        LeLog << LOG_APP << "Task " << t->GetName() << " failed to start." << NL;
        return false;
    }

    std::list< shared_ptr<ITask> >::iterator itr;
    for (itr = _taskList.begin(); itr != _taskList.end(); ++itr)
        if ((*itr)->Priority > t->Priority)
            break;

    _taskList.insert(itr, t);
    return true;
}

void Kernel::ResumeTask(const shared_ptr<ITask>& t)
{
    std::list< shared_ptr<ITask> >::iterator itr = std::find(_pausedTaskList.begin(), _pausedTaskList.end(), t);

    if (itr != _pausedTaskList.end())
    {
        t->OnResume();
        _pausedTaskList.erase(itr);

        for (itr = _taskList.begin(); itr != _taskList.end(); ++itr)
        if ((*itr)->Priority > t->Priority)
            break;

        _taskList.insert(itr, t);
    }
    else
        LeLog << LOG_APP << "Tried to resume " << t->GetName() << " but task does not exist in paused task list" << NL;
}


void Kernel::RemoveTask(const shared_ptr<ITask>& t)
{
    if (std::find(_taskList.begin(), _taskList.end(), t) != _taskList.end())
        t->CanKill = true;
    else
        LeLog << LOG_APP << "Tried to remove " << t->GetName() << " but task does not exist in task list" << NL;
}

void Kernel::KillAllTasks()
{
    for (auto itr = _taskList.begin(); itr != _taskList.end(); ++itr)
        (*itr)->CanKill = true;
}

bool Kernel::AddRenderable( const shared_ptr<IRenderable>& r )
{
    _objectList.push_back(r);
    return true;
}

void Kernel::RemoveRenderable( const shared_ptr<IRenderable>& r )
{
    std::list< shared_ptr<IRenderable>>::iterator it = std::find(_objectList.begin(), _objectList.end(), r);
    if ( it != _objectList.end())
        _objectList.erase(it);
    else
         LeLog << LOG_APP << "Tried to remove " << r->GetName() << " but renderable does not exist in rederable list" << NL;
        
}

void Kernel::RenderObjectList()
{
    std::list< shared_ptr<IRenderable> >::iterator itr;
    for (itr = _objectList.begin(); itr != _objectList.end();)
    {
        IRenderable* r = (*itr).get();
        ++itr;
        r->Render();
    }
}
