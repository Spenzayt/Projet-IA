#include "Node.hpp"

Node::Node(Vector2i pos)
    : position(pos), gCost(0), hCost(0), fCost(0), parent(nullptr) {
}

void Node::calculateCosts(Vector2i endPos, int newG) {
    gCost = newG;
    hCost = calculateHeuristic(endPos);
    fCost = gCost + hCost;
}

// Calculate heuristic using the Manhattan distance with diagonal correction
int Node::calculateHeuristic(Vector2i endPos) {
    int dx = abs(endPos.x - position.x);
    int dy = abs(endPos.y - position.y);

    // Return heuristic with diagonal distance weighting
    return 14 * (dx + dy) - 10 * min(dx, dy);
}