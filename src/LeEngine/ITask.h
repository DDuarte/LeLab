#ifndef ITASK_H
#define ITASK_H

#include <string>

class ITask
{
public:
    ITask(std::string name) : CanKill(false), Priority(5000), _name(name) {}
    ITask() : CanKill(false), Priority(5000), _name("") {}
    virtual bool Start() = 0;
    virtual void OnSuspend() {}
    virtual void Update() = 0;
    virtual void OnResume() {}
    virtual void Stop() = 0;

    bool CanKill;
    int Priority;

    std::string GetName() const { return _name; }

protected:
    std::string _name;
};

#endif // ITASK_H
