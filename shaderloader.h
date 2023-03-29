#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class ShaderLoader{
public:
    static GLuint createShaderProgram(std::vector<std::string> shaderSources, std::vector<GLenum> shaderTypes, std::string& infoLog){
        // Create and compile the shaders.
        if(shaderSources.size() != shaderTypes.size()){
            infoLog = "Must be the same number of shader files as shader types!";
            return -1;
        }

        std::vector<GLuint> shaderIDs = std::vector<GLuint>(shaderSources.size());
        for(int i = 0; i<shaderIDs.size(); i++){
            shaderIDs[i] = createShader(shaderTypes[i], shaderSources[i].c_str(), infoLog);
            // If failed to compile shader, fail to compile program
            if(shaderIDs[i] == -1){
                return -1;
            }
        }

        // Link the shader program.
        GLuint programID = glCreateProgram();
        for(GLenum& shaderID : shaderIDs){
            glAttachShader(programID, shaderID);
        }
        glLinkProgram(programID);

        // Print the info log if error
        GLint status;
        glGetProgramiv(programID, GL_LINK_STATUS, &status);

        if (status == GL_FALSE) {
            GLint length;
            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);

            std::string log(length, '\0');
            glGetProgramInfoLog(programID, length, nullptr, &log[0]);

            glDeleteProgram(programID);
            //std::cout<<log<<std::endl;
            std::string programLog = "Error Linking Program!\n";
            infoLog = programLog + log;
            return -1;
        }

        // Shaders no longer necessary, stored in program
        for(GLenum& shaderID : shaderIDs){
            glDeleteShader(shaderID);
        }

        infoLog = "Success!";

        return programID;
    }

private:
    static GLuint createShader(GLenum shaderType, const char *shaderSource, std::string& infoLog){
        GLuint shaderID = glCreateShader(shaderType);

        glShaderSource(shaderID, 1, &shaderSource, nullptr); // Assumes code is null terminated
        glCompileShader(shaderID);

        // Print info log if shader fails to compile.
        GLint status;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

        if (status == GL_FALSE) {
            GLint length;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

            std::string log(length, '\0');
            glGetShaderInfoLog(shaderID, length, nullptr, &log[0]);

            glDeleteShader(shaderID);
            //std::cout<<log<<std::endl;
            std::string shaderTypeStr;
            if(shaderType == GL_VERTEX_SHADER){
                shaderTypeStr = "Vertex Shader Errors!\n";
            }
            else{
                shaderTypeStr = "Fragment Shader Errors!\n";
            }

            infoLog = shaderTypeStr + log;
            return -1;
        }

        return shaderID;
    }
};
