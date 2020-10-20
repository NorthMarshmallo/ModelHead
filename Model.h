#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>

using namespace std;

class Model {
private:
	vector<vector<float>> verts_;
	vector<vector<int>> faces_;
public:
	Model(const char* filename);
	~Model();
	int nverts();
	int nfaces();
	vector<float> vert(int idx);
	vector<int> face(int i);
};

#endif 