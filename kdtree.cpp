#include "precomp.h" // include (only) this in every .cpp file

// TODO: Multi threaded?
namespace St
{
    KDTree::KDTree(std::vector<Tank*> tanks)
    {
        this->build(tanks, &this->rootNode, KTypes::X);

        std::cout << this->rootNode.getValue() << std::endl;
        std::cout << this->rootNode.getLeftNode()->getValue() << std::endl;
        std::cout << this->rootNode.getRightNode()->getValue() << std::endl;
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
