#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "../../map/Grid.hpp"
#include "Node.hpp"
#include <vector>

using namespace std;
using namespace sf;

class Pathfinding {
public:
    static vector<Vector2i> findPath(Grid& grid, Vector2i start, Vector2i end);
    static vector<Vector2i> findOppositePath(Grid& grid, Vector2i start, Vector2i end);
};

#endif // PATHFINDING_H