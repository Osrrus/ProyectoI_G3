#include "Obj.h"

Obj::Obj(Model model){


    this->model = model;
    std::cout<< this->model.vertex.size() <<std::endl;

    glGenVertexArrays(1, &VAO); 
	// Creates on GPU the vertex buffer object
	glGenBuffers(3, VBO);
	// Binds the vertex array to set all the its properties
	glBindVertexArray(VAO);

	// Sets the buffer geometry data
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, model.vertex.size() * sizeof(glm::vec3), &model.vertex[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);

    // text Coord
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, model.uvs.size() * sizeof(glm::vec2), &model.uvs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *)0);

	// normals
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(glm::vec3), &model.normals[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);
}

void Obj::Draw(){

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, model.vertex.size());
    glBindVertexArray(0);
}

Obj:: ~Obj(){

	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, VBO);
}