#pragma once
#include <vector>

class Ground
{
public:
	void InitializeGround();
	void Draw();
    void current_height(int LINES, int base_height_divisor);
    

	std::vector<int> ground;
};
