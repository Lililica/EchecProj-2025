#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class ShaderLoader {
public:
    static GLuint LoadShader(const char* vertexPath, const char* fragmentPath)
    {
        std::string   vertexCode, fragmentCode;
        std::ifstream vShaderFile, fShaderFile;

        // Ouvre les fichiers
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        if (!vShaderFile || !fShaderFile)
        {
            std::cerr << "Erreur: Impossible d'ouvrir les fichiers shader!" << std::endl;
            return 0;
        }

        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // Compilation des shaders
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vShaderCode, NULL);
        glCompileShader(vertexShader);
        CheckCompileErrors(vertexShader, "VERTEX");

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
        glCompileShader(fragmentShader);
        CheckCompileErrors(fragmentShader, "FRAGMENT");

        // Création du programme shader
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        CheckCompileErrors(shaderProgram, "PROGRAM");

        // Nettoyage
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;
    }

private:
    static void CheckCompileErrors(GLuint shader, std::string type)
    {
        GLint  success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "Erreur de compilation du shader " << type << ":\n"
                          << infoLog << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "Erreur de linkage du programme:\n"
                          << infoLog << std::endl;
            }
        }
    }
};

#endif
