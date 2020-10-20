#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char* filename) : verts_(), faces_() {
    std::ifstream in;    
    in.open(filename, std::ifstream::in);   //открываем файл по указателю,переданному в конструктор модели
    std::string line;
    while (!in.eof()) {   //пока не дойдем до конца файла обрабатываем все строки
        std::getline(in, line);
        std::istringstream iss(line.c_str());     //берем указатель на строку
        char trash;   
        float p;
        if (line.compare(0, 2, "v ") == 0) {    //проверяем строку на то, вершину ли она задает
            iss >> trash;   //выкидываем первый элемент строки(v)
            vector<float> v;
            for (int i = 0; i < 3; i++) {
                iss >> p;     //забираем следующий элемент строки, на который сместились указателем, это х вершины
                v.push_back(p);   //добавляем этот элемент к подготовленному вектору для вершины, итого выйдет вектор из x,y,z
            }
            verts_.push_back(v);  //добавляем полученный вектор к общему вектору для всех вершин модели
        }
        else if (line.compare(0, 2, "f ")==0) {
            std::vector<int> f;
            int idx,itrash;  //нам нужна переменная для номера вершины и еще одна типа int для того, чтобы выкидывать вершины
            iss >> trash;   //выкидываем f и устанавливем указатель на следующий элемент строки
            while (iss>>idx) {  //пока в строке есть элементы, у которых мы можем взять индекс строки и перейти на следующий элемент
                idx--;  //отсчет строк начинается с 1, а в векторе первый эхлемент с индексом 0
                f.push_back(idx);  //добавляем номер вершины к вектору для данной грани
                iss >> trash;   //выкидываем все, кроме индекса из формы(v/vt/vn), т.е. знаки слэша, текстурную вершину и вершину нормали
                iss >> itrash;
                iss >> trash;
                iss >> itrash;  //переходим к следующей вершине
            }
            faces_.push_back(f);  //добавляем грань к вектору с гранями
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << std::endl;  // выводим количество вершин и граней
    in.close();
}

Model::~Model() {   //деструктор класса
}

int Model::nverts() {     
    return (int)verts_.size();   //возвращаем количество вершины
}

int Model::nfaces() {
    return (int)faces_.size();    //возвращаем количество граней
}

std::vector<int> Model::face(int idx) {
    return faces_[idx];     //возвращаем грань под номером, переданным в метод
}

vector<float> Model::vert(int i) {
    return verts_[i];     //возвращаем вершину под номером, переданным в метод
}
