#pragma once

namespace St
{
    class St::KDNode;

    class KDTree
    {
        public:
            KDTree(std::vector<Tank*> tanks);
            void getClosestTank(Tank* tank);

        private:
            enum KTypes { X, Y };
            KDNode rootNode;

            void print(KDNode* root, int depth, KTypes ktype, int position);
            KDNode* getDeepestNodeByPosition(vec2 position, KDNode* root, KTypes ktype);
            KDNode* getClosestDistanceNodeByDeepestNode(vec2 target_position, KDNode* root, KDNode* node);
            KDNode* getClosestDistanceNodeInNode(vec2 target_position, KDNode* current_closest_node, KDNode* node);
            std::vector<float> getSortedList(std::vector<float> input);
            void build(std::vector<Tank*> tanks, KDNode* root, KTypes ktype);
            float getDistanceBetweenTanks(Tank* tank_a, Tank* tank_b);
    };
};
