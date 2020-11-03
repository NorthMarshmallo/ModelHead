#include "tgaimage.h"
#include <math.h>
#include <iostream>
#include "Model.h"
#include <vector>

using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor yellow = TGAColor(255, 255, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor purple = TGAColor(255, 0, 255, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const TGAColor cyan = TGAColor(0, 255, 255, 255);
const TGAColor color1 = TGAColor(0, 50, 100, 255);
const TGAColor color2 = TGAColor(135, 10, 10, 255);
const TGAColor color3 = TGAColor(148, 0, 211, 255);
const TGAColor color4 = TGAColor(255, 228, 196, 255);
const TGAColor color5 = TGAColor(0, 100, 0, 255);
const TGAColor color6 = TGAColor(186, 85, 211, 255);
const TGAColor color7 = TGAColor(221, 160, 221, 255);
const TGAColor color8 = TGAColor(70, 130, 180, 255);
const TGAColor color9 = TGAColor(220, 20, 60, 255);
Model* model = NULL;
const int width = 2000;
const int height = 2000;
vector<vector<double>> y_spis(height+100);


void DrawLineBrez(int x1, int y1, int x2, int y2,int c ) {
	//cout << y_spis.size() << endl;
	double dy, dx, x, y;
	int n;	
	bool flag = false;
	x = x1; y = y1;
	dx = x2 - x1; dy = y2 - y1;
	if (abs(dx) < abs(dy)) {
		swap(x, y);
		swap(x1, y1);
		swap(x2, y2);
		swap(dx, dy);
		flag = true;
	}
	double d = 2 * abs(dy) - abs(dx);
	while ((x!=x2)) {
		if (flag == true) {
			n = round(x);
			if ((c==8) and (n <=600) and (y >= 1400)) {
				cout << "1 " << n << " " << y << endl;
			}
			y_spis[n].push_back(round(y));
		}
		else {
			n = round(y);
			if ((c == 8) and (n<=600) and(x>=1400)) {
				cout << "2 "<< n << " " << x << endl;
			}
			y_spis[n].push_back(round(x));
		}
		if (d < 0) {
			d += 2 * abs(dy);
		}
		else {
			d += 2 * (abs(dy) - abs(dx));
			if ((y2 - y1) != 0)
				y += (y2 - y1) / (abs(y2 - y1));
			else
				y += 0;
		}
		if ((x2 - x1) != 0)
			x += (x2 - x1) / abs(x2 - x1);
		else
			x += 0;
	}
	if (flag == true) {
		swap(x2, y2);
	}
	y_spis[y2].push_back(x2);
}

void DrawFace(int x1, int y1, int x2, int y2, TGAImage& Image, TGAColor color) {
	//cout << "                        Draw" << endl;
	double dy, dx, x, y;
	bool flag = false;
	x = x1; y = y1;
	dx = x2 - x1; dy = y2 - y1;
	if (abs(dx) < abs(dy)) {
		swap(x, y);
		swap(x1, y1);
		swap(x2, y2);
		swap(dx, dy);
		flag = true;
	}
	double d = 2 * dy - dx;
	while ((x != x2)) {
		if (flag == true)
			Image.set(round(y), round(x), color);
		else
			Image.set(round(x), round(y), color);
		if (d < 0) {
			d += 2 * abs(dy);
		}
		else {
			d += 2 * (abs(dy) - abs(dx));
			if ((y2 - y1) != 0)
				y += (y2 - y1) / (abs(y2 - y1));
			else
				y += 0;
		}
		if ((x2 - x1) != 0)
			x += (x2 - x1) / abs(x2 - x1);
		else
			x += 0;
	}
	if (flag == true) {
		swap(x2, y2);
	}
	Image.set(x2, y2, color);
}


int main(int argc, char** argv) {
	if (2 == argc) {
		model = new Model(argv[1]);
	}
	else {
		model = new Model("C:\\african_head.obj");   //� ������� ������������ ������ Model ������� ������, ��������� ��������� �� ���� � �������
	}
	TGAImage image(width, height, TGAImage::RGB);  //������� ������ ������ � ������ ����������� ��� ��������� ������
	int c = 0,p=0; TGAColor color;
	for (int i = 0; i < model->nfaces(); i++) {   //�������� �� ���� ������, �������� �� ������� 
		std::vector<int> face = model->face(i);   //����� ����� ��� ������� i ���������� ������
		if (c == 0) {
			color = white;
		}
		else if (c == 1) {
			color = red;
		}
		else if (c == 2) {
			color = yellow;
		}
		else if (c == 3) {
			color = green;
		}
		else if (c == 4) {
			color = blue;
		}
		else if (c == 5) {
			color = purple;
		}
		else if (c == 6) {
			color = cyan;
		}
		else if (c == 7) {
			color = color1;
		}
		else if (c == 8) {
			color = color2;
		}
		else if (c == 9) {
			color = color3;
		}
		else if (c == 10) {
			color = color4;
		}
		else if (c == 11) {
			color = color5;
		}
		else if (c == 12) {
			color = color6;
		}
		else if (c == 13) {
			color = color7;
		}
		else if (c == 14) {
			color = color8;
		}
		else if (c == 15) {
			color = color9;
		}
		for (int j = 0; j < 3; j++) {  //��������� ��� ��� �������
			vector<float> v0 = model->vert(face[j]);  // 1 � 2, 2 � 3, 3 � 1 ������� ������ �����
			vector<float> v1 = model->vert(face[(j + 1) % 3]);
			int x0 = (v0[0]+1.) * width / 2.;   //����� ������ � � � �������, �� ������ ������� ����������� 
			int y0 = (v0[1]+1.) * height / 2.;  //������ ����������� �������:
			int x1 = (v1[0]+1.) * width / 2.;   //�������� �� 1, ����� ���������� �� ��������������� ��������
			int y1 = (v1[1]+1.) * height / 2.;   //����� �������, ����� �� �������� �� ������� �����������
			if (c==8){
			    cout << "###" << x0 << " " << y0 << "  " << x1 << " " << y1 << endl;
			}
			
			DrawLineBrez(x0, y0, x1, y1, c);  //��������� ������� � ������� ��������� ����������
		}cout << endl;
		for (int m = 0; m < height; m++) {
			if (y_spis[m].size() == 2) {
				if ((y_spis[m][1]) < (y_spis[m][0])) {
					DrawFace(round(y_spis[m][1]+1.), m, round(y_spis[m][0]), m, image, color);
				}
				else {
					DrawFace(round(y_spis[m][0]+1.), m, round(y_spis[m][1]), m, image, color);
				}
			}
			else if (y_spis[m].size() == 1) {
				image.set(round(y_spis[m][0]), m, color);
			}
			else if (y_spis[m].size() > 2) {
				int o = 0,temp;
				for (int i1 = 0; i1 < y_spis[m].size() - 1; i1++) {
					for (int j1 = 0; j1 < y_spis[m].size() - i1 - 1; j1++) {
						if (y_spis[m][j1] > y_spis[m][j1+1]) {
							// ������ �������� �������
							temp = y_spis[m][j1];
							y_spis[m][j1] = y_spis[m][j1+1];
							y_spis[m][j1] = temp;
						}
					}
				}
				while (o < y_spis[m].size()-1) {
					if ((y_spis[m][o+1]) < (y_spis[m][o])) {
						DrawFace(round(y_spis[m][o+1]+1.), m, round(y_spis[m][o]), m, image, color);
					}
					else {
						DrawFace(round(y_spis[m][o]+1.), m, round(y_spis[m][o+1]), m, image, color);
					}
					o += 1;
				}
			}
			y_spis[m] = { };
		}
		p += 1;
		//cout << p << endl;
		//cout << "CCCC" << c << endl;
		if (c == 15) {
			c = 0;
		}
		else {
			c += 1;
		}
	}
	image.flip_vertically();   //����� �������� � ������ ������� ����
	image.write_tga_file("output.tga");
	delete model;
	return 0;
}

