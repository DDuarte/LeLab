#ifndef KERNEL_H
#define KERNEL_H

#include "Singleton.h"
#include "ITask.h"

#include <list>
#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class Kernel : public Singleton<Kernel>
{
public:
    Kernel();
    virtual ~Kernel();

    int Execute();

    bool AddTask(const shared_ptr<ITask>& t);
    void SuspendTask(const shared_ptr<ITask>& t);
    void ResumeTask(const shared_ptr<ITask>& t);
    void RemoveTask(const shared_ptr<ITask>& t);
    void KillAllTasks();

protected:
    std::list< shared_ptr<ITask> > _taskList;
    std::list< shared_ptr<ITask> > _pausedTaskList;
};

#endif // KERNEL_H
