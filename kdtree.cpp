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
        std::cout << "-- [START] GET CLOSEST TANK -- " << std::endl;
        KDNode* deepest_node = this->getDeepestNodeByPosition(tank->get_position(), &this->rootNode, KTypes::X);
        float current_closest_distance = this->getDistanceBetweenTanks(tank, deepest_node->getTank());
        std::cout << "Base Closest Distance Pos: " << deepest_node->getTank()->get_position().x << ", " << deepest_node->getTank()->get_position().y << std::endl;
        std::cout << "Base Closest Distance: " << current_closest_distance << std::endl;
        this->getClosestDistanceNodeByDeepestNode(tank->get_position(), current_closest_distance, deepest_node->getParentNode());
        std::cout << "-- [END] GET CLOSEST TANK -- " << std::endl;
    }

    KDNode* KDTree::getDeepestNodeByPosition(vec2 position, KDNode* root, KTypes ktype = KTypes::X)
    {
        float compare_value = 0;
        switch (ktype) {
            case KTypes::X:
                compare_value = position.x;
                break;

            case KTypes::Y:
                compare_value = position.y;
                break;
        }

        KTypes next_type = (ktype == KTypes::X) ? KTypes::Y : KTypes::X;

        if (compare_value < root->getValue()) {
            if (root->hasLeftNode()) {
                return this->getDeepestNodeByPosition(position, root->getLeftNode(), next_type);
            }
        } else {
            if (root->hasRightNode()) {
                return this->getDeepestNodeByPosition(position, root->getRightNode(), next_type);
            }
        }

        return root;
    }

    KDNode* KDTree::getClosestDistanceNodeByDeepestNode(vec2 target_position, float current_closest_distance, KDNode* node)
    {
        float new_closest_distance = this->getClosestDistanceInNode(target_position, current_closest_distance, node);

        // TODO: ALS JE OMHOOG GAAT, CHECKEN OF DIT ZIN HEEFT! ALS DIST. GROTER IS DAN WAT WE NU HEBBEN, DAN NIET.

        std::cout << "NEW CLOSEST DISTANCE: " << new_closest_distance << std::endl;
    }

    float KDTree::getClosestDistanceInNode(vec2 target_position, float current_closest_distance, KDNode* node)
    {
        float distance = fabsf((node->getTank()->get_position() - target_position).sqr_length());
        float return_distance = (distance < current_closest_distance) ? distance : current_closest_distance;

        std::cout << node->getTank()->get_position().x << ", " << node->getTank()->get_position().y << std::endl;
        std::cout << distance << std::endl;
        std::cout << "+++++++++++++++++++++++++++" << std::endl;

        if (node->hasLeftNode()) {
            return this->getClosestDistanceInNode(target_position, return_distance, node->getLeftNode());
        }

        if (node->hasRightNode()) {
            return this->getClosestDistanceInNode(target_position, return_distance, node->getRightNode());
        }

        return return_distance;
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
            root->getLeftNode()->setParentNode(root);
            this->build(left, root->getLeftNode(), next_type);
        }

        if (right.size() > 0) {
            root->getRightNode()->setParentNode(root);
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

    float KDTree::getDistanceBetweenTanks(Tank* tank_a, Tank* tank_b)
    {
        return fabsf((tank_a->get_position() - tank_b->get_position()).sqr_length());
    }
}
