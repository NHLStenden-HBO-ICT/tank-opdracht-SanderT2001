#pragma once

namespace Tmpl8
{

class Explosion
{
  public:
    Explosion(Sprite* explosion_sprite, vec2 position) : current_frame(0), explosion_sprite(explosion_sprite), position(position) {}

    bool done() const;
    void tick();
    void draw(Surface* screen);

    void accept(St::GameObjectsVisitor* visitor) { visitor->visitExplosion(this); };

    vec2 position;

    int current_frame;
    Sprite* explosion_sprite;
};

}
