#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>

class ObjLoader {
private:
    std::vector<std::string> listPath;

public:
    ObjLoader()  = default;
    ~ObjLoader() = default;

    void add_path(std::string& p) { listPath.push_back(p); }

    std::vector<GLfloat> loaderObj();
};