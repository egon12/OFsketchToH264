//
//  Points.cpp
//  firstSketch
//
//  Created by Egon Firman on 14/02/19.
//

#include "Points.hpp"
#include <vector>
#include <glm/glm.hpp>

Points::Points() {
    points = new std::vector<glm::vec2>();
}

Points::~Points() {
    points->clear();
    delete(points);
}

void Points::add(glm::vec2 vec) {
    points->push_back(vec);
}

std::vector<glm::vec2> Points::get() {
    return *points;
}

void Points::print() {
    printf("points with size %d", (int) points->size());
}


PointsGroup::PointsGroup() {
    points = new std::vector<Points*>();
}

PointsGroup::~PointsGroup() {
    for (auto const &p: *points) {
        delete p;
    }
    points->clear();
    delete(points);
}

void PointsGroup::add(Points *p) {
    points->push_back(p);
}

std::vector<Points*> PointsGroup::get() {
    return *points;
}

void PointsGroup::print() {
    printf("points with size %d", (int) points->size());
}


