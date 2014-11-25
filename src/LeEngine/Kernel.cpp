#include "Kernel.h"
#include "Log.h"

#include <algorithm>
#include <list>
#include <memory>

Kernel::Kernel() {}

Kernel::~Kernel() {}

int Kernel::Execute()
{
    std::list<std::shared_ptr<ITask>>::iterator it, thisIt;
    while (_taskList.size())
    {
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

bool Kernel::AddTask(const std::shared_ptr<ITask>& t)
{
    if (!t->Start())
    {
        LeLog.WriteP("Task %s failed to start.", t->GetName().c_str());
        return false;
    }

    std::list<std::shared_ptr<ITask>>::iterator itr;
    for (itr = _taskList.begin(); itr != _taskList.end(); ++itr)
        if ((*itr)->Priority > t->Priority)
            break;

    _taskList.insert(itr, t);
    return true;
}

void Kernel::ResumeTask(const std::shared_ptr<ITask>& t)
{
    std::list<std::shared_ptr<ITask>>::iterator itr = std::find(_pausedTaskList.begin(), _pausedTaskList.end(), t);

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
        LeLog.WriteP("Tried to resume %s but task does not exist in paused task list", t->GetName().c_str());
}


void Kernel::RemoveTask(const std::shared_ptr<ITask>& t)
{
    if (std::find(_taskList.begin(), _taskList.end(), t) != _taskList.end())
        t->CanKill = true;
    else
        LeLog.WriteP("Tried to remove but task does not exist in task list", t->GetName().c_str());
}

void Kernel::KillAllTasks()
{
    for (auto itr = _taskList.begin(); itr != _taskList.end(); ++itr)
        (*itr)->CanKill = true;
}
