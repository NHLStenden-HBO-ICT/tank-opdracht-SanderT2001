#pragma once

namespace St
{
    class PrintPositionVisitor : public GameObjectsVisitor
    {
        public:
            PrintPositionVisitor();

            virtual void visitTank(Tank* tank);
            virtual void visitRocket(Rocket* rocket);
            virtual void visitExplosion(Explosion* explosion);
            virtual void visitSmoke(Smoke* smoke);

        private:
            void print(std::string object_name, vec2 position);
    };
};
