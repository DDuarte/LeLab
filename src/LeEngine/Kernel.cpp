#include "Kernel.h"
#include "ProfileSample.h"
#include "Log.h"

#include <algorithm>
#include <list>

#include <GL/glfw.h>

Kernel::Kernel()
{
    /*if ( glfwInit() )
    LeLog << LOG_APP << "GLFW version " <<*/
    if (!glfwInit())
    {
        LeLog << LOG_APP << "Failed to initialize GLFW" << NL;
        exit(EXIT_FAILURE);
    }
}

Kernel::~Kernel()
{
    // SDLNet_Quit();
    // SDL_Quit();
}

int Kernel::Execute()
{
    while (_taskList.size())
    {
        {
            PROFILE("Kernel task loop");

            std::list< MMPointer<ITask> >::iterator it;
            for (it = _taskList.begin(); it != _taskList.end();)
            {
                ITask* t = *it;
                ++it;
                if (!t->CanKill)
                    t->Update();
            }

            for (it = _taskList.begin(); it != _taskList.end();)
            {
                ITask* t = *it;
                ++it;
                if (t->CanKill)
                {
                    t->Stop();
                    _taskList.remove(t);
                    t = NULL;
                }
            }
            MMObject::CollectGarbage();
        }
#ifdef DEBUG
        ProfileSample::Output();
#endif
    }

    return 0;
}

bool Kernel::AddTask(MMPointer<ITask>& t)
{
    if (!t->Start())
    {
        LeLog << LOG_APP << "Task " << t->GetName() << " failed to start." << NL;
        return false;
    }

    std::list< MMPointer<ITask> >::iterator itr;
    for (itr = _taskList.begin(); itr != _taskList.end(); ++itr)
        if ((*itr)->Priority > t->Priority)
            break;

    _taskList.insert(itr, t);
    return true;
}

void Kernel::ResumeTask(MMPointer<ITask>& t)
{
    std::list< MMPointer<ITask> >::iterator itr = std::find(_pausedTaskList.begin(), _pausedTaskList.end(), t);

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


void Kernel::RemoveTask(MMPointer<ITask>& t)
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
