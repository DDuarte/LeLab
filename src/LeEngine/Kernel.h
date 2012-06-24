#ifndef KERNEL_H
#define KERNEL_H

#include "Singleton.h"
#include "MMPointer.h"
#include "ITask.h"

class Kernel : public Singleton<Kernel>
{
public:
    Kernel();
    virtual ~Kernel();

    int Execute();

    bool AddTask(MMPointer<ITask>& t);
    void SuspendTask(MMPointer<ITask>& t);
    void ResumeTask(MMPointer<ITask>& t);
    void RemoveTask(MMPointer<ITask>& t);
    void KillAllTasks();

protected:
    std::list< MMPointer<ITask> > _taskList;
    std::list< MMPointer<ITask> > _pausedTaskList;
};

#endif // KERNEL_H
