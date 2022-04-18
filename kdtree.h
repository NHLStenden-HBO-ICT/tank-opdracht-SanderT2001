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

            std::vector<int> getSortedList(std::vector<int> input);
            void print(KDNode* root, int depth, KTypes ktype, int position);
            void build(std::vector<Tank*> tanks, KDNode* root, KTypes ktype);
    };
};
