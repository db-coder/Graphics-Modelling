#include "shampoo.hpp"
#include <math.h>



double areaTriangle(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3){
	double e1x=p1.x - p2.x;
	double e1y=p1.y - p2.y;
	double e1z=p1.z - p2.z;

	double e2x=p2.x - p3.x;
	double e2y=p2.y - p3.y;
	double e2z=p2.z - p3.z;


	double e3x = e1y*e2z - e1z*e2y;
	double e3y = e1z*e2x - e1x*e2z;
	double e3z = e1x*e2y - e1y*e2x;

	return sqrt(e3x*e3x + e3y*e3y + e3z*e3z);
}

glm::vec4 centroid(std::vector<glm::vec4> v_triangle_positions){
	double currentX=0,currentY=0,currentZ=0;
	double currentWeight=0;
	for (int i = 0; i+2 <= (int)v_triangle_positions.size(); i+=3)
	{
		
		glm::vec4 p1=v_triangle_positions[i], p2 = v_triangle_positions[i+1], p3 =v_triangle_positions[i+2];
		double weight= areaTriangle(p1, p2, p3);
		double x = (p1.x + p2.x + p3.x) /3;
		double y = (p1.y + p2.y + p3.y) /3;
		double z = (p1.z + p2.z + p3.z) /3;

		currentX = (currentX*currentWeight + x*weight) / (currentWeight+weight);
		currentY = (currentY*currentWeight + y*weight) / (currentWeight+weight);
		currentZ = (currentZ*currentWeight + z*weight) / (currentWeight+weight);
		currentWeight = currentWeight + weight;
	}

	glm::vec4 p(currentX,currentY,currentZ,1.0);

	return p;
}