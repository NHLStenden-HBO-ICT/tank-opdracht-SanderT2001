#pragma once

namespace St
{
    class St::KDNode;

    class KDTree
    {
        public:
            KDTree(std::vector<Tank*> tanks);

        private:
            enum KTypes { X, Y };
            KDNode rootNode;

            std::vector<float> getSortedList(std::vector<float> input);
            void build(std::vector<Tank*> tanks, KDNode* root, KTypes ktype);
    };
};
