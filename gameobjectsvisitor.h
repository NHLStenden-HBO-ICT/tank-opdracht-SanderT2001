#pragma once

// Circulair Dependency workaround, see precomp.h
namespace Tmpl8
{
    class Tank;
    class Rocket;
    class Explosion;
    class Smoke;
}

namespace St
{
    class GameObjectsVisitor
    {
        public:
            // Use `~` (virtual destructor), has to do with moving the pointer to the implementing class.
            virtual ~GameObjectsVisitor() {}

            // Interface method must be assigned to 0
            virtual void visitTank(Tank* tank) = 0;
            virtual void visitRocket(Rocket* rocket) = 0;
            virtual void visitExplosion(Explosion* explosion) = 0;
            virtual void visitSmoke(Smoke* smoke) = 0;

        private:
    };
};
