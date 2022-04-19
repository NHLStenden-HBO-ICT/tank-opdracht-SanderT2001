#include "precomp.h" // include (only) this in every .cpp file

// TODO: Multi threaded?
namespace St
{
    KDTree::KDTree(std::vector<Tank*> tanks)
    {
        this->build(tanks, &this->rootNode, KTypes::X);

        this->print(&this->rootNode, 0, KTypes::X, 0);
    }

    void KDTree::print(KDNode* root, int depth = 0, KTypes ktype = KTypes::X, int position = 0)
    {
        if (position == 0) {
            std::cout << "[ROOT]\t";
        } else if (position == 1) {
            std::cout << "[LEFT]\t";
        } else if (position == 2) {
            std::cout << "[RIGHT]\t";
        }

        std::cout << ((ktype == KTypes::X) ? "[X]\t" : "[Y]\t");
        std::cout << "[DEPTH " << depth << "]\t";
        std::cout << root->getTank()->get_position().x << ", " << root->getTank()->get_position().y;
        std::cout << std::endl;

        KTypes next_type = (ktype == KTypes::X) ? KTypes::Y : KTypes::X;
        if (root->hasLeftNode()) {
            this->print(root->getLeftNode(), depth+1, next_type, 1);
        }
        if (root->hasRightNode()) {
            this->print(root->getRightNode(), depth+1, next_type, 2);
        }
    }

    void KDTree::getClosestTank(Tank* tank)
    {
        std::cout << "get closest tank" << std::endl;
    }

    void KDTree::build(std::vector<Tank*> tanks, KDNode* root, KTypes ktype)
    {
        // TODO: Wellicht kunnen we 1malig een list opbouwen :thinking:
        std::vector<float> coordinates_list;
        KTypes next_type;
        for (Tank* tank : tanks) {
            switch (ktype) {
                case KTypes::X:
                    coordinates_list.push_back(tank->get_position().x);
                    next_type = KTypes::Y;
                    break;

                case KTypes::Y:
                    coordinates_list.push_back(tank->get_position().y);
                    next_type = KTypes::X;
                    break;
            }
        }
        coordinates_list = this->getSortedList(coordinates_list);

        int median_position = coordinates_list.size() / 2;
        float median_value = coordinates_list[median_position];
        root->setValue(median_value);

        std::vector<Tank*> left;
        std::vector<Tank*> right;

        for (Tank* tank : tanks) {
            float compare_value = 0;
            switch (ktype) {
                case KTypes::X:
                    compare_value = tank->get_position().x;
                    break;

                case KTypes::Y:
                    compare_value = tank->get_position().y;
                    break;
            }

            // No "=="||"<="||"=>" because we don't want the median to be included
            if (compare_value < median_value) {
                left.push_back(tank);
            } else if (compare_value == median_value) {
                // TODO: DIT MOET ECHT ANDERS, IS HEEL LAME EN KAN NIET ALTIJD KLOPPEN
                root->setTank(tank);
            } else if (compare_value > median_value) {
                right.push_back(tank);
            }
        }

        if (left.size() > 0) {
            this->build(left, root->getLeftNode(), next_type);
        }

        if (right.size() > 0) {
            this->build(right, root->getRightNode(), next_type);
        }
    }

    /**
     * TODO: (netjes neerzetten) "Uses QuickSort"
     */
    std::vector<float> KDTree::getSortedList(std::vector<float> input)
    {
        float pivot = input.back();
        input.pop_back();

        std::vector<float> left;
        std::vector<float> right;

        for (float coordinate : input) {
            if (coordinate <= pivot) {
                left.push_back(coordinate);
            } else {
                right.push_back(coordinate);
            }
        }

        if (left.size() > 1) {
            left = this->getSortedList(left);
        }
        if (right.size() > 1) {
            right = this->getSortedList(right);
        }

        std::vector<float> output;
        output.insert(output.end(), left.begin(), left.end());
        output.push_back(pivot);
        output.insert(output.end(), right.begin(), right.end());
        return output;
    }
}
