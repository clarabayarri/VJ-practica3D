#include "cFloor.h"
#include <queue>
#include <cmath>

using namespace std;

/*****  Auxiliar Functions  *****/
void print(const vector<vector<float> >& terrain) {
  for (unsigned int i = 0; i < terrain.size(); ++i) {
    for (unsigned int j = 0; j < terrain[i].size(); ++j) {
      cout << (int) terrain[i][j] << " ";
    }
    cout << endl;
  }
}

void RandomInit(vector<vector<float> >& terrain) {
    for (unsigned int i = 0; i < terrain.size(); ++i)
        for (unsigned int j = 0; j < terrain.size(); ++j)
            terrain[i][j] = rand()%(TERRAIN_SIZE)-TERRAIN_SIZE/2;
}

float getBilinearFilteredPixelColor(const vector<vector<float> >& tex, double i, double j) {
   int x = i/2;
   int y = j/2;
   int xx = (x+1)%tex.size();
   int yy = (y+1)%tex.size();
   return (tex[x][y]+tex[x][yy]+tex[xx][y]+tex[xx][yy])/4;
}

void add(vector<vector<float> >& terrain, const vector<vector<float> >& surface, int addsubstract) {
    for(unsigned int i = 0; i < terrain.size(); ++i)
        for(unsigned int j = 0; j < terrain.size(); ++j)
            terrain[i][j] += surface[i][j] * addsubstract;
}

void GenerateSurface(vector<vector<float> >& terrain) {
    RandomInit(terrain);

    float normalize = 1.0;
    float reduction = 2;
    for (unsigned int i = 0; i < LODS; ++i) {
        vector<vector<float> > lod(TERRAIN_SIZE/reduction,vector<float>(TERRAIN_SIZE/reduction));
        RandomInit(lod);

        vector<vector<float> > aux;
        float augmentation = reduction/2;
        for (unsigned int j = 0; j < i+1; ++j) {
            aux = vector<vector<float> >(TERRAIN_SIZE/augmentation,vector<float>(TERRAIN_SIZE/augmentation));
            for (unsigned int i = 0; i < aux.size(); ++i)
                for (unsigned int j = 0; j < aux.size(); ++j)
                    aux[i][j] = getBilinearFilteredPixelColor(lod,i,j);
            lod = aux;
            augmentation = augmentation/2;
        }

        add(terrain,lod,reduction);
        normalize+=reduction;
        reduction*=2;
    }

    for (unsigned int i = 0; i < terrain.size(); ++i)
        for (unsigned int j = 0; j < terrain.size(); ++j)
            terrain[i][j] /= normalize;
}

void normalize(vector<float> &v) {
    float totalValue = 0.0;
    for (unsigned int i = 0; i < v.size(); ++i) totalValue += v[i]*v[i];
    totalValue = sqrt(totalValue);
    for (unsigned int i = 0; i < v.size(); ++i) v[i] = v[i]/totalValue;
}


/*****  Public Functions  *****/
cFloor::cFloor():ready(false) {}

cFloor::~cFloor(){}

void cFloor::Init() {
	srand(time(NULL));

    vector<vector<float> > surface(TERRAIN_SIZE,vector<float>(TERRAIN_SIZE,0));
    vector<vector<float> > terrain(TERRAIN_SIZE,vector<float>(TERRAIN_SIZE,0));

    for (int i = 0; i < OVERLAPPED_SURFACES; ++i) {
        GenerateSurface(surface);
        add(terrain,surface,(i%2 == 1 ? -1 : 1));
    }

	heights = vector<vector<float> >(terrain);

    vertices = vector<vertex>(TERRAIN_SIZE*TERRAIN_SIZE);
    for (unsigned int i = 0; i < TERRAIN_SIZE; ++i)
        for (unsigned int j = 0; j < TERRAIN_SIZE; ++j)
            vertices[i*TERRAIN_SIZE+j]=(vertex(i*DILATATION,terrain[i][j],j*DILATATION));

    faces = vector<face>((TERRAIN_SIZE-1)*(TERRAIN_SIZE-1)*2);
    unsigned int f = 0;
    for (unsigned int i = 0; i < (TERRAIN_SIZE-1); ++i)
        for (unsigned int j = 0; j < (TERRAIN_SIZE-1); ++j) {
            faces[f++] = (face((i+1)*TERRAIN_SIZE+j,i*TERRAIN_SIZE+j,i*TERRAIN_SIZE+j+1));
            faces[f++] = (face((i+1)*TERRAIN_SIZE+j,i*TERRAIN_SIZE+j+1,(i+1)*TERRAIN_SIZE+j+1));
        }

    UpdateSmoothedNormals();
	GenerateArrays();
}

float cFloor::GetSize() {
	return TERRAIN_SIZE;
}

float cFloor::GetDilatation() {
	return DILATATION;
}

float cFloor::GetY(int x, int y) {
	return heights[x][y];
}

/***** Private Functions  *****/
void cFloor::UpdateNormal(int f) {
    int j;
    faces[f].normal = vector<float>(3);
    faces[f].normal[0] = faces[f].normal[1] = faces[f].normal[2] = 0.0f;
    
    int n = faces[f].vertices.size();
    for (int i=0; i<n; i++) {
        j = (i+1)%n;
		int current = faces[f].vertices[i];
		int next = faces[f].vertices[j];
		
        faces[f].normal[0] = (faces[f].normal[0] + ((vertices[current].coord[2] + vertices[next].coord[2]) * (vertices[current].coord[1] - vertices[next].coord[1])));
        faces[f].normal[1] = (faces[f].normal[1] + ((vertices[current].coord[0] + vertices[next].coord[0]) * (vertices[current].coord[2] - vertices[next].coord[2])));
        faces[f].normal[2] = (faces[f].normal[2] + ((vertices[current].coord[1] + vertices[next].coord[1]) * (vertices[current].coord[0] - vertices[next].coord[0])));
    }
    normalize(faces[f].normal);
}

void cFloor::UpdateSmoothedNormals() {
    vector<vector<float> > normals(vertices.size(),vector<float>(3));

    for(unsigned int i=0; i< faces.size(); ++i) {
        UpdateNormal(i);
        for (unsigned int j = 0; j < faces[i].vertices.size(); ++j) {
            normals[faces[i].vertices[j]][0] += faces[i].normal[0];
			normals[faces[i].vertices[j]][1] += faces[i].normal[1];
			normals[faces[i].vertices[j]][2] += faces[i].normal[2];
		}
    }

    for(unsigned int i = 0; i < vertices.size(); ++i) {
        normalize(normals[i]);
        vertices[i].normal = normals[i];
    }
}