#pragma once

namespace St
{
    class KDNode
    {
        public:
            KDNode();
            int getValue() { return this->value; }
            void setValue(int value) { this->value = value; }

            KDNode* getLeftNode() {
                if (this->left == NULL) {
                    this->left = new KDNode();
                }

                return this->left;
            }

            KDNode* getRightNode() {
                if (this->right == NULL) {
                    this->right = new KDNode();
                }

                return this->right;
            }

        private:
            int value = 0;
            KDNode* left = NULL;
            KDNode* right = NULL;
    };
};
