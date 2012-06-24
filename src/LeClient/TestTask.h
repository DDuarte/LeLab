#ifndef TESTTASK_H
#define TESTTASK_H

#include "ITask.h"
#include "GL/glfw.h"
#include "InputTask.h"
#include "Kernel.h"

class TestTask : public ITask
{
public:
    bool Start() { return true; }
    void Update()
    {
       glClear(GL_COLOR_BUFFER_BIT);
       if (InputTask::KeyDown(GLFW_KEY_ESC))
           Kernel::Get().KillAllTasks();
    }

    void Stop() {}
    AUTO_SIZE;
};

#endif // TESTTASK_H
