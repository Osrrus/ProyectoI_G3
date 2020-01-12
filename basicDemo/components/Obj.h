#pragma once

#include "../define.h"

class Obj
{
	public:
		Obj(Model model);
		~Obj();
		Model model;
		unsigned int VAO;
		unsigned int VBO[3];

		void Draw();

};
