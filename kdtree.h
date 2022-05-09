#pragma once

namespace St
{
    enum St::KTypes;
    class St::KDNode;

    class KDTree
    {
        public:
            KDTree(std::vector<Tank*> tanks);
            void getClosestTank(Tank* tank);

        private:
            KDNode rootNode;

            std::vector<float> getTanksCoordinatesListForKType(std::vector<Tank*> tanks, KTypes ktype);
            float getTankPositionValueFromKType(Tank* tank, KTypes ktype);
            std::vector<float> getSortedList(std::vector<float> input);

            KDNode* getDeepestNodeByPosition(vec2 position, KDNode* root, KTypes ktype);
            KDNode* getClosestDistanceNodeByDeepestNode(vec2 target_position, KDNode* root, KDNode* node);
            KDNode* getClosestDistanceNodeInNode(vec2 target_position, KDNode* current_closest_node, KDNode* node);
            void build(std::vector<Tank*> tanks, KDNode* root, KTypes ktype);
            float getDistanceBetweenTanks(Tank* tank_a, Tank* tank_b);
    };
};
