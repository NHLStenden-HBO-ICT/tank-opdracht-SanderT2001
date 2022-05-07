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
            KDNode* getClosestDistanceNodeByDeepestNode(vec2 target_position, float current_closest_distance, KDNode* node);
            float getClosestDistanceInNode(vec2 target_position, float current_closest_distance, KDNode* node);
            std::vector<float> getSortedList(std::vector<float> input);
            void build(std::vector<Tank*> tanks, KDNode* root, KTypes ktype);
            float getDistanceBetweenTanks(Tank* tank_a, Tank* tank_b);
    };
};
