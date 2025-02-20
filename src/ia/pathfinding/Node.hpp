#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <algorithm>

using namespace std;
using namespace sf;

class Node {
public:
    Vector2i position;
    int gCost, hCost, fCost;
    Node* parent;

    Node(Vector2i pos);
    void calculateCosts(Vector2i endPos, int newG);

private:
    int calculateHeuristic(Vector2i endPos);
};

#endif