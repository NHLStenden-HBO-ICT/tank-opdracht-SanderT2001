#pragma once

namespace St
{
    class KDNode
    {
        public:
            KDNode();
            float getValue() { return this->value; }
            void setValue(float value) { this->value = value; }

            Tank* getTank() { return this->tank; }
            Tank* setTank(Tank* value) { this->tank = value; }

            bool hasParentNode() { return (this->parent != NULL); }
            bool hasLeftNode() { return (this->left != NULL); }
            bool hasRightNode() { return (this->right != NULL); }

            KDNode* getParentNode() { return this->parent; }
            void setParentNode(KDNode* value) { this->parent = value; }

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
            float value = 0;
            Tank* tank = NULL;

            KDNode* parent = NULL;

            KDNode* left = NULL;
            KDNode* right = NULL;
    };
};
