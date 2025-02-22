#include "Pathfinding.hpp"
#include <queue>
#include <unordered_map>
#include <memory>

class CompareNodePtr {
public:
    bool operator()(const Node* a, const Node* b) const {
        return a->fCost > b->fCost;  // Compare based on F cost
    }
};

struct Vector2iHash {
    size_t operator()(const Vector2i& v) const {
        return hash<int>()(v.x) ^ (hash<int>()(v.y) << 1);  // Hash function for Vector2i
    }
};

vector<Vector2i> Pathfinding::findPath(Grid& grid, Vector2i start, Vector2i end) {
    priority_queue<Node*, vector<Node*>, CompareNodePtr> openQueue;
    unordered_map<Vector2i, Node*, Vector2iHash> allNodes;
    vector<Vector2i> directions = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {-1, -1}, {1, -1}, {1, 1}, {-1, 1}  // All possible directions (8 directions)
    };

    // Initialize start node
    Node* startNode = new Node(start);
    startNode->calculateCosts(end, 0);
    openQueue.push(startNode);
    allNodes[start] = startNode;

    while (!openQueue.empty()) {
        Node* current = openQueue.top();
        openQueue.pop();

        if (current->position == end) {
            vector<Vector2i> path;
            while (current) {
                path.push_back(current->position);
                current = current->parent;
            }
            reverse(path.begin(), path.end());  // Reverse the path to get it from start to end

            for (auto& pair : allNodes) delete pair.second;  // Clean up dynamically allocated nodes
            return path;
        }

        // Explore neighbors
        for (auto& dir : directions) {
            Vector2i neighborPos = current->position + dir;

            if (neighborPos.x < 0 || neighborPos.x >= Config::GRID_WIDTH ||
                neighborPos.y < 0 || neighborPos.y >= Config::GRID_HEIGHT)
                continue;  // Skip out-of-bound positions

            if (!grid.getCell(neighborPos.x, neighborPos.y).walkable)
                continue;  // Skip if cell is not walkable

            // Check diagonal movement for obstacles
            if (dir.x != 0 && dir.y != 0) {
                if (!grid.getCell(current->position.x, neighborPos.y).walkable ||
                    !grid.getCell(neighborPos.x, current->position.y).walkable)
                    continue;
            }

            int newGCost = current->gCost + ((dir.x != 0 && dir.y != 0) ? 14 : 10);  // Cost for diagonal or straight movement

            Node* neighbor;
            if (allNodes.find(neighborPos) != allNodes.end()) {  // If neighbor already exists
                neighbor = allNodes[neighborPos];
                if (newGCost < neighbor->gCost) {  // Update if we found a better path
                    neighbor->gCost = newGCost;
                    neighbor->fCost = newGCost + neighbor->hCost;
                    neighbor->parent = current;
                    openQueue.push(neighbor);  // Reinsert into the queue
                }
            }
            else {
                neighbor = new Node(neighborPos);
                neighbor->calculateCosts(end, newGCost);  // Calculate costs for new neighbor
                neighbor->parent = current;
                openQueue.push(neighbor);
                allNodes[neighborPos] = neighbor;  // Add new neighbor to all nodes
            }
        }
    }

    for (auto& pair : allNodes) delete pair.second;  // Clean up if no path is found
    return {};  // Return empty path if no valid path exists
}

vector<Vector2i> Pathfinding::findOppositePath(Grid& grid, Vector2i start, Vector2i playerPos) {
    // Find the direction opposite to the player and calculate a target position
    Vector2i direction = start - playerPos;
    direction = { -direction.x, -direction.y };

    int distance = 5;  // Fleeing distance
    Vector2i targetPos = start + direction * distance;

    // Ensure target is within grid bounds
    targetPos.x = clamp(targetPos.x, 0, Config::GRID_WIDTH - 1);
    targetPos.y = clamp(targetPos.y, 0, Config::GRID_HEIGHT - 1);

    return findPath(grid, start, targetPos);  // Find path to the opposite direction
}