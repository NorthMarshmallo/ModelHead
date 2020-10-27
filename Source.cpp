#include "tgaimage.h"
#include <math.h>
#include <iostream>
#include "Model.h"
#include <vector>

using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
Model* model = NULL;
const int width = 800;
const int height = 800;

void DrawLineBrez(int x1, int y1, int x2, int y2, TGAImage& Image, TGAColor color) {
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
	while (x != x2) {
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
		model = new Model("C:\\african_head.obj");   //с помощью конструктора класса Model создаем модель, передавая указатель на файл с головой
	}
	TGAImage image(width, height, TGAImage::RGB);  //создаем нужной ширины и высоты изображение для рисования головы
	for (int i = 0; i < model->nfaces(); i++) {   //проходим по всем граням, соединяя их вершины 
		std::vector<int> face = model->face(i);   //берем грань под номером i переданной модели
		for (int j = 0; j < 3; j++) {  //соединяем все три вершины
			vector<float> v0 = model->vert(face[j]);  // 1 и 2, 2 и 3, 3 и 1 вершины данной грани
			vector<float> v1 = model->vert(face[(j + 1) % 3]);
			int x0 = (v0[0] + 1.) * width /2.;   //берем только х и у вершины, тк рисуем плоское изображение 
			int y0 = (v0[1] + 1.) * height / 2.;  //задаем соединяемые пиксели:
			int x1 = (v1[0] + 1.) * width / 2.;   //сдвигаем на 1, чтобы избавиться от отрицательности значений
			int y1 = (v1[1] + 1.) * height / 2.;   //делим пополам, чтобы не выходить за границы изображения
			DrawLineBrez(x0, y0, x1, y1, image, white);  //соединяем вершины с помощью алгоритма брезенхема
		}
	}
	image.flip_vertically();   //чтобы начинать с левого нижнего угла
	image.write_tga_file("output.tga");
	delete model;
	return 0;
}
