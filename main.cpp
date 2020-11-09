#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>

#include "accessory.h"

/*
Разработать классы согласно варианту задания, классы должны наследоваться от базового класса Figure.
Фигуры являются фигурами вращения. Все классы должны поддерживать набор общих методов:
1.   	Вычисление геометрического центра фигуры;
2.   	Вывод в стандартный поток вывода buffer координат вершин фигуры;
3.      Вычисление площади фигуры.

Создать программу, которая позволяет:
•       Вводить из стандартного ввода std::cin фигуры, согласно варианту задания.
•       Сохранять созданные фигуры в динамический массив std::vector<Figure*>.
•   	Вызывать для всего массива общие функции (1-3 см. выше).Т.е. распечатывать для каждой фигуры в массиве
            геометрический центр, координаты вершин и площадь.
•       Необходимо уметь вычислять общую площадь фигур в массиве.
•       Удалять из массива фигуру по индексу.

var 6

5-угольник
6-угольник
8-угольник

*/


class Pair{
public:
    double x;
    double y;

    Pair() = default;

    Pair(double x, double y){
        this->x = x;
        this->y = y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pair& pair){
        os << "x = " + std::to_string(pair.x) + " y = " + std::to_string(pair.y) << std::endl;
        return os;
    }

    Pair operator+(const Pair& rhs) const{
        return {x + rhs.x,y + rhs.y};
    }

    Pair operator-(const Pair& rhs) const{
        return {x - rhs.x,y - rhs.y};
    }

    Pair operator/(double d) const{
        return {x / d,y / d};
    }

    Pair& operator+=(const Pair& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
};

double get_det(const double x1, const double y1,
               const double x2, const double y2){
    return x1 * y2 - x2 * y1;
}

double gauss_area(const std::vector<Pair>& nodes){
    double out = 0.0;
    auto count = nodes.size();
    for(size_t i = 0; i < (count - 1); i++){
        out += get_det(nodes[i].x,nodes[i].y,nodes[i+1].x,nodes[i+1].y);
    }
    out += get_det(nodes[count-1].x,nodes[count-1].y,nodes[0].x,nodes[0].y);
    return fabs(0.5 * out);
}

Pair get_centroid(const std::vector<Pair>& nodes){
    Pair centroid = {0, 0};
    double signedArea = 0.0;
    double x0 = 0.0;
    double y0 = 0.0;
    double x1 = 0.0;
    double y1 = 0.0;
    double a = 0.0;

    int i = 0;
    for (i = 0; i < nodes.size() - 1; ++i) {
        x0 = nodes[i].x;
        y0 = nodes[i].y;
        x1 = nodes[i+1].x;
        y1 = nodes[i+1].y;
        a = get_det(x0,y0,x1,y1);
        signedArea += a;
        centroid.x += (x0 + x1)*a;
        centroid.y += (y0 + y1)*a;
    }

    x0 = nodes[i].x;
    y0 = nodes[i].y;
    x1 = nodes[0].x;
    y1 = nodes[0].y;
    a = get_det(x0,y0,x1,y1);
    signedArea += a;
    centroid.x += (x0 + x1)*a;
    centroid.y += (y0 + y1)*a;

    signedArea *= 0.5;
    centroid.x /= (6.0*signedArea);
    centroid.y /= (6.0*signedArea);

    return centroid;
}

class Figure{
public:
    std::vector<Pair> nodes;
    virtual Pair get_center() = 0;
    virtual double get_area() = 0;
    std::string name;
    friend std::ostream& operator<<(std::ostream& os, const Figure& figure){
        os << figure.name << std::endl;
        for(auto node : figure.nodes){
            os << node;
        }
        return os;
    }
};

class Pentagon : public Figure{
public:
    explicit Pentagon(std::vector<Pair>&& nodes_){
        nodes = nodes_;
        name = "Pentagon";
        if (nodes.size() != 5){
            std::string error = std::string("size error in Pentagon") + "size is " + int_to_string(nodes_.size());
            perror(error.c_str());
        }
    }

    Pair get_center() override{
        return ::get_centroid(nodes);
    }

    double get_area() override{
        return gauss_area(nodes);
    }
};

class Hexagon : public Figure{
public:
    explicit Hexagon(std::vector<Pair>&& nodes_){
        nodes = nodes_;
        name = "Hexagon";
        if (nodes.size() != 6){
            std::string error = std::string("size error in Hexagon") + "size is " + int_to_string(nodes_.size());
            perror(error.c_str());
        }
    }

    Pair get_center() override{
        return ::get_centroid(nodes);
    }

    double get_area() override{
        return gauss_area(nodes);
    }
};

class Octagon : public Figure{
public:
    explicit Octagon(std::vector<Pair>&& nodes_){
        nodes = nodes_;
        name = "Octagon";
        if (nodes.size() != 8){
            std::string error = std::string("size error in Octagon") + "size is " + int_to_string(nodes_.size());
            perror(error.c_str());
        }
    }

    Pair get_center() override{
        return ::get_centroid(nodes);
    }

    double get_area() override{
        return gauss_area(nodes);
    }
};

int main() {
    std::vector<Figure*> figures;

    std::string cmd;
    std::vector<std::string> out;
    std::stringstream buffer;
    int count = 0;
    help();
    while (true){
        getline(std::cin, cmd);
        std::string prefix = std::string("query ") + int_to_string(count) + ": ";
        if (cmd == "exit"){
            break;
        }
        else if (cmd == "help"){
            help();
        }
        else if (cmd == "area"){
            if (figures.empty()){
                buffer << prefix << "no figures in array" << std::endl;
            }
            else {
                double sum = 0.0;
                for(auto el : figures){
                    sum += el->get_area();
                }
                buffer << prefix << "total area of all figures is " << sum << std::endl;
            }
        }
        else if (cmd.find("delete") != std::string::npos) {
            int index = string_to_int(split(cmd,' ')[1]);
            if (index >= figures.size()){
                buffer << prefix << "index > figures size" << std::endl;
            }
            else {
                buffer << prefix << std::endl;
                figures.erase(figures.begin() + index);
                buffer << "figure " + int_to_string(index) + " was delete" << std::endl;
            }
        }
        else if (cmd == "go"){
            buffer << prefix << std::endl;
            for(auto figure : figures){
                buffer << *figure;
                buffer << "center: " << figure->get_center();
                buffer << "area: " << figure->get_area() <<std::endl;
            }
        }
        else {
            std::vector<std::string> array = split(cmd,' ');
            std::vector<Pair> numbers;
            numbers.resize((array.size() - 1) / 2);

            int j = 0;
            for(size_t i = 0;i < numbers.size() * 2 ; i += 2){
                numbers[j] = {string_to_double(array[i]),string_to_double(array[i+1])};
                j++;
            }

            if (array.back() == "pentagon"){
                figures.emplace_back(new Pentagon(std::move(numbers)));
            }
            else if (array.back() == "hexagon"){
                figures.emplace_back(new Hexagon(std::move(numbers)));
            }
            else if (array.back() == "octagon"){
                figures.emplace_back(new Octagon(std::move(numbers)));
            }
        }
        count++;
    }
    std::cout << buffer.str() << std::endl;

    return 0;
}
