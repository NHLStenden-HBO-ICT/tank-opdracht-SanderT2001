#include "precomp.h" // include (only) this in every .cpp file

namespace St
{
    KDTree::KDTree(std::vector<Tank*> tanks)
    {
        this->build(tanks, &this->rootNode, KTypes::X);
    }

    Tank* KDTree::getClosestTank(Tank* tank)
    {
        // Stap 1. Diepste Node zoeken binnen de Tree op basis van een positie van een Tank.
        KDNode* deepest_node = this->getDeepestNodeByTank(tank, &this->rootNode, KTypes::X);

        // Stap 2. Vanuit deze diepste node de minimum distance berekenen en vervolgens omhoog gaan in de Tree om te kijken of er nog een node dichterbij de tank zit.
        KDNode* n = this->getClosestDistanceNodeFromDeepestNode(tank->get_position(), deepest_node);

        return n->getTank();
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

    /**
     * Diepste node zoeken op basis van een Tank positie.
     */
    KDNode* KDTree::getDeepestNodeByTank(Tank* tank, KDNode* root, KTypes ktype = KTypes::X)
    {
        float compare_value = this->getTankPositionValueFromKType(tank, ktype);

        KTypes next_type = (ktype == KTypes::X) ? KTypes::Y : KTypes::X;

        if (compare_value < root->getValue()) {
            if (root->hasLeftNode()) {
                return this->getDeepestNodeByTank(tank, root->getLeftNode(), next_type);
            }
        } else {
            if (root->hasRightNode()) {
                return this->getDeepestNodeByTank(tank, root->getRightNode(), next_type);
            }
        }

        return root;
    }

    KDNode* KDTree::getClosestDistanceNodeFromDeepestNode(vec2 target_position, KDNode* deepest_node)
    {
        float deepest_node_distance = this->getDistanceBetweenPositions(deepest_node->getTank()->get_position(), target_position);

        KDNode* new_closest_node = this->getClosestDistanceInNodeByPosition(target_position, deepest_node, deepest_node->getParentNode());
        float new_closest_distance = this->getDistanceBetweenPositions(new_closest_node->getTank()->get_position(), target_position);

        if (new_closest_node == deepest_node) {
            return deepest_node;
        }

        if (new_closest_distance > deepest_node_distance) {
            return deepest_node;
        }

        if (new_closest_node->hasParentNode()) {
            return this->getClosestDistanceNodeFromDeepestNode(target_position, new_closest_node);
        }

        return new_closest_node;
    }

    KDNode* KDTree::getClosestDistanceInNodeByPosition(vec2 target_position, KDNode* current_closest_node, KDNode* node_to_check)
    {
        float current_closest_distance = this->getDistanceBetweenPositions(current_closest_node->getTank()->get_position(), target_position);
        float distance = this->getDistanceBetweenPositions(node_to_check->getTank()->get_position(), target_position);
        KDNode* return_node = (distance < current_closest_distance) ? node_to_check : current_closest_node;

        if (distance > current_closest_distance) {
            return current_closest_node;
        }

        if (node_to_check->hasLeftNode()) {
            return this->getClosestDistanceInNodeByPosition(target_position, return_node, node_to_check->getLeftNode());
        }

        if (node_to_check->hasRightNode()) {
            return this->getClosestDistanceInNodeByPosition(target_position, return_node, node_to_check->getRightNode());
        }

        return return_node;
    }

    float KDTree::getDistanceBetweenPositions(vec2 position_a, vec2 position_b)
    {
        return fabsf((position_a - position_b).sqr_length());
    }
}
