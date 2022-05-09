#include "precomp.h" // include (only) this in every .cpp file

// TODO: Multi threaded?
namespace St
{
    KDTree::KDTree(std::vector<Tank*> tanks)
    {
        this->build(tanks, &this->rootNode, KTypes::X);
    }

    void KDTree::getClosestTank(Tank* tank)
    {
        std::cout << "-- [START] GET CLOSEST TANK -- " << std::endl;
        KDNode* deepest_node = this->getDeepestNodeByPosition(tank->get_position(), &this->rootNode, KTypes::X);
        float current_closest_distance = this->getDistanceBetweenTanks(tank, deepest_node->getTank());
        std::cout << "Base Closest Distance Pos: " << deepest_node->getTank()->get_position().x << ", " << deepest_node->getTank()->get_position().y << std::endl;
        std::cout << "Base Closest Distance: " << current_closest_distance << std::endl;
        KDNode* n = this->getClosestDistanceNodeByDeepestNode(tank->get_position(), deepest_node, deepest_node->getParentNode());
        std::cout << "UITEINDELIJK:" << std::endl;
        n->getTank()->print_position();
        std::cout << "-- [END] GET CLOSEST TANK -- " << std::endl;
    }

    void KDTree::build(std::vector<Tank*> tanks, KDNode* root, KTypes ktype)
    {
        // Stap 1. Tanks sorteren o.b.v. KType positie (x of y) van klein-groot.
        std::vector<Tank*> sorted_tanks = this->sortTanksVectorOnKTypePosition(tanks, ktype);

        // Stap 2. Middelste tank pakken (mediaan).
        int vector_median_position = sorted_tanks.size() / 2;
        Tank* median_tank = sorted_tanks[vector_median_position];
        // Stap 3. Middelste value (x/y) bepalen.
        float median_value = this->getTankPositionValueFromKType(median_tank, ktype);

        // Stap 4. Waardes in de KDNode zetten.
        root->setValue(median_value);
        root->setKType(ktype);
        root->setTank(median_tank);

        // Stap 5. Bepalen of er nog sub-nodes zijn, zo ja, deze tanks dan verzamelen per kant (links/rechts) en nodes maken door build opnieuw aan te roepen.
        std::vector<Tank*> left;
        std::vector<Tank*> right;

        for (Tank* tank : tanks) {
            if (tank == median_tank) continue;

            float compare_value = this->getTankPositionValueFromKType(tank, ktype);

            // No "=="||"<="||"=>" because we don't want the median to be included
            if (compare_value < median_value) {
                left.push_back(tank);
            } else {
                right.push_back(tank);
            }
        }

        KTypes next_type = (ktype == KTypes::X) ? KTypes::Y : KTypes::X;

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
     * Verkrijg de juiste positie waarde (x of y) op basis van de meegegeven KType.
     */
    float KDTree::getTankPositionValueFromKType(Tank* tank, KTypes ktype)
    {
        switch (ktype) {
            case KTypes::X:
                return tank->get_position().x;
                break;

            case KTypes::Y:
                return tank->get_position().y;
                break;
        }
    }

    /**
     * Sorteert een vector met Tanks (methode: QuickSort) o.b.v. KType positie (x of y) van klein-groot.
     */
    std::vector<Tank*> KDTree::sortTanksVectorOnKTypePosition(std::vector<Tank*> input, KTypes ktype)
    {
        Tank* pivot = input.back();
        float pivot_position = this->getTankPositionValueFromKType(pivot, ktype);
        input.pop_back();

        std::vector<Tank*> left;
        std::vector<Tank*> right;

        for (Tank* tank : input) {
            float coordinate = this->getTankPositionValueFromKType(tank, ktype);
            if (coordinate <= pivot_position) {
                left.push_back(tank);
            } else {
                right.push_back(tank);
            }
        }

        if (left.size() > 1) {
            left = this->sortTanksVectorOnKTypePosition(left, ktype);
        }
        if (right.size() > 1) {
            right = this->sortTanksVectorOnKTypePosition(right, ktype);
        }

        std::vector<Tank*> output;
        output.insert(output.end(), left.begin(), left.end());
        output.push_back(pivot);
        output.insert(output.end(), right.begin(), right.end());
        return output;
    }

    /* TODO: HIER GEBLEVEN! */

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

    KDNode* KDTree::getClosestDistanceNodeByDeepestNode(vec2 target_position, KDNode* root, KDNode* node)
    {
        KDNode* new_closest_node = this->getClosestDistanceNodeInNode(target_position, root, node);

        float new_closest_distance = fabsf((new_closest_node->getTank()->get_position() - target_position).sqr_length());
        if (new_closest_node->hasParentNode()) {
            KDNode* new_closest_node_from_parent_node = this->getClosestDistanceNodeInNode(target_position, new_closest_node, new_closest_node->getParentNode());
            float distance_from_new_closest_node_to_parent = fabsf((new_closest_node_from_parent_node->getTank()->get_position() - target_position).sqr_length());
            if (distance_from_new_closest_node_to_parent < new_closest_distance) {
                return this->getClosestDistanceNodeByDeepestNode(target_position, new_closest_node, new_closest_node->getParentNode());
            }
        }
        return new_closest_node;
    }

    KDNode* KDTree::getClosestDistanceNodeInNode(vec2 target_position, KDNode* current_closest_node, KDNode* node)
    {
        float current_closest_distance = fabsf((current_closest_node->getTank()->get_position() - target_position).sqr_length());
        float distance = fabsf((node->getTank()->get_position() - target_position).sqr_length());
        KDNode* return_node = (distance < current_closest_distance) ? node : current_closest_node;

        if (distance > current_closest_distance) {
            return current_closest_node;
        }

        if (node->hasLeftNode()) {
            return this->getClosestDistanceNodeInNode(target_position, return_node, node->getLeftNode());
        }

        if (node->hasRightNode()) {
            return this->getClosestDistanceNodeInNode(target_position, return_node, node->getRightNode());
        }

        return return_node;
    }

    float KDTree::getDistanceBetweenTanks(Tank* tank_a, Tank* tank_b)
    {
        return fabsf((tank_a->get_position() - tank_b->get_position()).sqr_length());
    }
}
