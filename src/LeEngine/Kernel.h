#ifndef KERNEL_H
#define KERNEL_H

#include "Singleton.h"
#include "ITask.h"
#include "Shapes.h"

#include <list>
#include <memory>
#include <boost/noncopyable.hpp>

class Kernel : public Singleton<Kernel>, private boost::noncopyable
{
public:
    Kernel();
    virtual ~Kernel();

    int Execute();

    bool AddTask(const std::shared_ptr<ITask>& t);
    void SuspendTask(const std::shared_ptr<ITask>& t);
    void ResumeTask(const std::shared_ptr<ITask>& t);
    void RemoveTask(const std::shared_ptr<ITask>& t);
    void KillAllTasks();

protected:
    std::list<std::shared_ptr<ITask>> _taskList;
    std::list<std::shared_ptr<ITask>> _pausedTaskList;
};

#endif // KERNEL_H
