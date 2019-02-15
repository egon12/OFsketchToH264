//
//  Points.hpp
//  firstSketch
//
//  Created by Egon Firman on 14/02/19.
//

#ifndef Points_hpp
#define Points_hpp

#include <iostream>
#include <glm/glm.hpp>

class Points {
public:
    Points();
    ~Points();
    void add(glm::vec2 p);
    std::vector<glm::vec2> get();
    void print();
private:
    std::vector<glm::vec2>* points;
};


class PointsGroup {
public:
    PointsGroup();
    ~PointsGroup();
    void add(Points *points);
    std::vector<Points*> get();
    void print();
private:
    std::vector<Points*> *points;
};


#endif /* Points_hpp */
