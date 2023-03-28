#pragma once

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include <iostream>
#include <memory>

#include "shaderloader.h"

class Core
{
public:
    Core(int width, int height);
    ~Core();
    int update(float seconds);
    int draw();
    void keyEvent(int key, int action);
    void mousePosEvent(double xpos, double ypos);
    void mouseButtonEvent(int button, int action);
    void scrollEvent(double distance);
    void windowResizeEvent(int width, int height);
    void framebufferResizeEvent(int width, int height);

private:

};