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
            KDNode* getClosestNodeByPosition(vec2 position, KDNode* root, KTypes ktype);
            std::vector<float> getSortedList(std::vector<float> input);
            void build(std::vector<Tank*> tanks, KDNode* root, KTypes ktype);
    };
};
