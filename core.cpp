#include "core.h"

#include "debug.h"
#include "shaderloader.h"

Core::Core(int width, int height){
    std::vector<GLfloat> data = {
        -1, -1,
        1, -1,
        1, 1,
        1, 1,
        -1, 1,
        -1, -1
    };

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), reinterpret_cast<GLvoid*>(0));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Core::~Core(){

}

int Core::update(float seconds){
    return 0;
}

int Core::draw(double time){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(m_shader);
    if(m_timeUniformLoc != -1){
        glUniform1f(m_timeUniformLoc, static_cast<GLfloat>(time - m_startTime));
    }
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glUseProgram(0);
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
    glViewport(0, 0, width, height);
}

void Core::windowResizeEvent(int width, int height){

}

void Core::compileShader(std::vector<std::string> shaderSources, std::vector<GLenum> shaderTypes, std::string& infoLog){
    GLuint prev = m_shader;
    m_shader = ShaderLoader::createShaderProgram(shaderSources, shaderTypes, infoLog);
    if(m_shader == -1){
        m_shader = prev;
    }
    else{
        glDeleteProgram(prev);
        m_timeUniformLoc = glGetUniformLocation(m_shader, "ss_time");
    }
}

void Core::setStartTime(double time){
    m_startTime = time;
}