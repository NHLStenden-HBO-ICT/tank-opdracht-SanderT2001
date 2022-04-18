#include "precomp.h" // include (only) this in every .cpp file

// TODO: Multi threaded?
namespace St
{
    KDTree::KDTree(std::vector<Tank*> tanks)
    {
        std::cout << "KD TREE INIT + " << tanks.size() << std::endl;

        std::cout << "=========================== POSITIONS ===========================" << std::endl;
        std::cout << " X\t\t|\tY" << std::endl;
        for (Tank* tank : tanks) {
            std::cout << tank->get_position().x << " | " << tank->get_position().y << std::endl;
        }
        std::cout << "=========================== POSITIONS ===========================" << std::endl;

        this->build(tanks, &this->rootNode, KTypes::X);
        this->print(&this->rootNode, 0, KTypes::X, 0);

        // vector met x/y coordinates
        // eerst voor de x en balenced maken
        // mediaan pakken en dan weet je wie de root is en de left/right tree
        // vervolgens voor beide lijsten de mediaan weer bepalen alleen dan voor y

        // vector van tanks als input
        // kun je een direction aan meegeven dat is de nieuwe direction
        // op basis van de tanks ga je dan de 

        // lijst aanleggen en mediaan vinden
        // vanuit de mediaan gaan we bouwen
        //
        // mediaan pakken - delete - opnieuw mediaan berekenen.
        //
        // per subtree belanced maken (BALENCED NOTEREN)
        // sort eerst op x (balenced)
        // sort dan op y (balenced)
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
        std::cout << root->getValue();
        std::cout << std::endl;

        KTypes next_type = (ktype == KTypes::X) ? KTypes::Y : KTypes::X;
        // TODO: HASLEFTNODE() FUNCTION
        if (root->getLeftNode()->getValue() > 0) {
            this->print(root->getLeftNode(), depth+1, next_type, 1);
        }
        if (root->getRightNode()->getValue() > 0) {
            this->print(root->getRightNode(), depth+1, next_type, 2);
        }
    }

    void KDTree::build(std::vector<Tank*> tanks, KDNode* root, KTypes ktype)
    {
        // TODO: Wellicht kunnen we 1malig een list opbouwen :thinking:
        std::vector<int> coordinates_list;
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
        int median_value = coordinates_list[median_position];
        std::cout << median_value << std::endl;
        root->setValue(median_value);

        std::vector<Tank*> left;
        std::vector<Tank*> right;

        int counter = 0;
        for (Tank* tank : tanks) {
            // No "=="||"<="||"=>" because we don't want the median to be included
            if (counter < median_position) {
                left.push_back(tank);
            } else if (counter > median_position) {
                right.push_back(tank);
            }
            counter += 1;
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
    std::vector<int> KDTree::getSortedList(std::vector<int> input)
    {
        int pivot = input.back();
        input.pop_back();

        std::vector<int> left;
        std::vector<int> right;

        for (int coordinate : input) {
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

        std::vector<int> output;
        output.insert(output.end(), left.begin(), left.end());
        output.push_back(pivot);
        output.insert(output.end(), right.begin(), right.end());
        return output;
    }
}
