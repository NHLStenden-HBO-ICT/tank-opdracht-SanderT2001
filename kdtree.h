#pragma once

namespace St
{
    enum St::KTypes;
    class St::KDNode;

    class KDTree
    {
        public:
            KDTree(std::vector<Tank*> tanks);
            Tank* getClosestTank(Tank* tank);

        private:
            KDNode rootNode;

            void build(std::vector<Tank*> tanks, KDNode* root, KTypes ktype);
            float getTankPositionValueFromKType(Tank* tank, KTypes ktype);
            std::vector<Tank*> sortTanksVectorOnKTypePosition(std::vector<Tank*> input, KTypes ktype);

            KDNode* getDeepestNodeByTank(Tank* tank, KDNode* root, KTypes ktype);
            KDNode* getClosestDistanceNodeFromDeepestNode(vec2 target_position, KDNode* deepest_node);
            KDNode* getClosestDistanceInNodeByPosition(vec2 target_position, KDNode* current_closest_node, KDNode* node_to_check);

            float getDistanceBetweenPositions(vec2 position_a, vec2 position_b);
    };
};
