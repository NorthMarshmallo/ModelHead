#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char* filename) : verts_(), faces_() {
    std::ifstream in;    
    in.open(filename, std::ifstream::in);   //��������� ���� �� ���������,����������� � ����������� ������
    std::string line;
    while (!in.eof()) {   //���� �� ������ �� ����� ����� ������������ ��� ������
        std::getline(in, line);
        std::istringstream iss(line.c_str());     //����� ��������� �� ������
        char trash;   
        float p;
        if (line.compare(0, 2, "v ") == 0) {    //��������� ������ �� ��, ������� �� ��� ������
            iss >> trash;   //���������� ������ ������� ������(v)
            vector<float> v;
            for (int i = 0; i < 3; i++) {
                iss >> p;     //�������� ��������� ������� ������, �� ������� ���������� ����������, ��� � �������
                v.push_back(p);   //��������� ���� ������� � ��������������� ������� ��� �������, ����� ������ ������ �� x,y,z
            }
            verts_.push_back(v);  //��������� ���������� ������ � ������ ������� ��� ���� ������ ������
        }
        else if (line.compare(0, 2, "f ")==0) {
            std::vector<int> f;
            int idx,itrash;  //��� ����� ���������� ��� ������ ������� � ��� ���� ���� int ��� ����, ����� ���������� �������
            iss >> trash;   //���������� f � ������������ ��������� �� ��������� ������� ������
            while (iss>>idx) {  //���� � ������ ���� ��������, � ������� �� ����� ����� ������ ������ � ������� �� ��������� �������
                idx--;  //������ ����� ���������� � 1, � � ������� ������ �������� � �������� 0
                f.push_back(idx);  //��������� ����� ������� � ������� ��� ������ �����
                iss >> trash;   //���������� ���, ����� ������� �� �����(v/vt/vn), �.�. ����� �����, ���������� ������� � ������� �������
                iss >> itrash;
                iss >> trash;
                iss >> itrash;  //��������� � ��������� �������
            }
            faces_.push_back(f);  //��������� ����� � ������� � �������
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << std::endl;  // ������� ���������� ������ � ������
    in.close();
}

Model::~Model() {   //���������� ������
}

int Model::nverts() {     
    return (int)verts_.size();   //���������� ���������� �������
}

int Model::nfaces() {
    return (int)faces_.size();    //���������� ���������� ������
}

std::vector<int> Model::face(int idx) {
    return faces_[idx];     //���������� ����� ��� �������, ���������� � �����
}

vector<float> Model::vert(int i) {
    return verts_[i];     //���������� ������� ��� �������, ���������� � �����
}
