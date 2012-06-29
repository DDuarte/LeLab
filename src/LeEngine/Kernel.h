#ifndef KERNEL_H
#define KERNEL_H

#include "Singleton.h"
#include "ITask.h"
#include "Shapes.h"

#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
using boost::shared_ptr;

class Kernel : public Singleton<Kernel>, private boost::noncopyable
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
