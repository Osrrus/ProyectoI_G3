#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <chrono>
#include <time.h>
#include <vector>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

#include "include/AntTweakBar.h"
#include "Shader.h"

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define GLM_ENABLE_EXPERIMENTAL

struct Model{

    std::vector<glm::vec3> vertex;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
};