#include <vector>

struct vertex {
  std::vector<float> coord;
  std::vector<float> normal;
  
  vertex() {};
  vertex(float a, float b, float c): coord(std::vector<float>(3)) {
    coord[0] = a;
    coord[1] = b;
    coord[2] = c;
  };
  vertex(float a, float b, float c, float d, float e, float f): coord(std::vector<float>(3)),normal(std::vector<float>(3)) {
    coord[0] = a;
    coord[1] = b;
    coord[2] = c;
	normal[0] = d;
	normal[1] = e;
	normal[2] = f;
  };
};

struct face {
  std::vector<float> normal;
  std::vector<int> vertices;
  
  face() {};
  face(int a, int b, int c): vertices(std::vector<int>(3)) {
    vertices[0] = a;
    vertices[1] = b;
    vertices[2] = c;
  }
  face(int a, int b, int c, float d, float e, float f): vertices(std::vector<int>(3)), normal(std::vector<float>(3)) {
    vertices[0] = a;
    vertices[1] = b;
    vertices[2] = c;
	normal[0] = d;
	normal[0] = e;
	normal[0] = f;
  }
};