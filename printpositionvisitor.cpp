#include "precomp.h" // include (only) this in every .cpp file

namespace St
{
    PrintPositionVisitor::PrintPositionVisitor()
    {
    }

    void PrintPositionVisitor::visitTank(Tank* tank)
    {
//        this->print("TANK", tank->get_position());
    }

    void PrintPositionVisitor::visitRocket(Rocket* rocket)
    {
        this->print("ROCKET", rocket->position);
    }

    void PrintPositionVisitor::visitExplosion(Explosion* explosion)
    {
        this->print("EXPLOSION", explosion->position);
    }

    void PrintPositionVisitor::visitSmoke(Smoke* smoke)
    {
        this->print("SMOKE", smoke->position);
    }

    void PrintPositionVisitor::print(std::string object_name, vec2 position)
    {
        std::string output;
        output.append("[" + object_name + "] X: ");
        output.append(std::to_string(position.x));
        output.append(", Y: ");
        output.append(std::to_string(position.y));

        std::cout << output << std::endl;
    }
}
