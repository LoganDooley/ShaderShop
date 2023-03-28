#include "core.h"

#include "debug.h"

Core::Core(int width, int height){

}

Core::~Core(){

}

int Core::update(float seconds){
    return 0;
}

int Core::draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return 0;
}

void Core::keyEvent(int key, int action){

}

void Core::mousePosEvent(double xpos, double ypos){

}

void Core::mouseButtonEvent(int button, int action){

}

void Core::scrollEvent(double distance){
    
}

void Core::framebufferResizeEvent(int width, int height){

}

void Core::windowResizeEvent(int width, int height){

}
