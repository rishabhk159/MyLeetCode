#include <algorithm>

class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        // Clamp the circle's center to the rectangle's bounding box
        int nearestX = std::max(x1, std::min(xCenter, x2));
        int nearestY = std::max(y1, std::min(yCenter, y2));
        
        // Calculate the vector from the center to the closest point
        int dx = nearestX - xCenter;
        int dy = nearestY - yCenter;
        
        // Check if the squared distance is within the squared radius
        return (dx * dx + dy * dy) <= (radius * radius);
    }
};