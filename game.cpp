
#include "precomp.h" // include (only) this in every .cpp file
#include <chrono>

constexpr auto num_tanks_blue = 2048;
constexpr auto num_tanks_red = 2048;

constexpr auto tank_max_health = 1000;
constexpr auto rocket_hit_value = 60;
constexpr auto particle_beam_hit_value = 50;

constexpr auto tank_max_speed = 1.0;

constexpr auto health_bar_width = 70;

constexpr auto max_frames = 2000;

//Global performance timer
//constexpr auto REF_PERFORMANCE = 114757; //UPDATE THIS WITH YOUR REFERENCE PERFORMANCE (see console after 2k frames)
constexpr auto REF_PERFORMANCE = 734968; //UPDATE THIS WITH YOUR REFERENCE PERFORMANCE (see console after 2k frames)
static timer perf_timer;
static float duration;

//Load sprite files and initialize sprites
static Surface* tank_red_img = new Surface("assets/Tank_Proj2.png");
static Surface* tank_blue_img = new Surface("assets/Tank_Blue_Proj2.png");
static Surface* rocket_red_img = new Surface("assets/Rocket_Proj2.png");
static Surface* rocket_blue_img = new Surface("assets/Rocket_Blue_Proj2.png");
static Surface* particle_beam_img = new Surface("assets/Particle_Beam.png");
static Surface* smoke_img = new Surface("assets/Smoke.png");
static Surface* explosion_img = new Surface("assets/Explosion.png");

static Sprite tank_red(tank_red_img, 12);
static Sprite tank_blue(tank_blue_img, 12);
static Sprite rocket_red(rocket_red_img, 12);
static Sprite rocket_blue(rocket_blue_img, 12);
static Sprite smoke(smoke_img, 4);
static Sprite explosion(explosion_img, 9);
static Sprite particle_beam_sprite(particle_beam_img, 3);

const static vec2 tank_size(7, 9);
const static vec2 rocket_size(6, 6);

const static float tank_radius = 3.f;
const static float rocket_radius = 5.f;

const static int  version      = 2; // 1 => Original function, 2 => Optimized function
const static bool show_timings = true;

// -----------------------------------------------------------
// Initialize the simulation state
// This function does not count for the performance multiplier
// (Feel free to optimize anyway though ;) )
// -----------------------------------------------------------
void Game::init()
{
    frame_count_font = new Font("assets/digital_small.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZ:?!=-0123456789.");

    tanks.reserve(num_tanks_blue + num_tanks_red);

    uint max_rows = 24;

    float start_blue_x = tank_size.x + 40.0f;
    float start_blue_y = tank_size.y + 30.0f;

    float start_red_x = 1088.0f;
    float start_red_y = tank_size.y + 30.0f;

    float spacing = 7.5f;

    //Spawn blue tanks
    for (int i = 0; i < num_tanks_blue; i++)
    {
        vec2 position{ start_blue_x + ((i % max_rows) * spacing), start_blue_y + ((i / max_rows) * spacing) };
        tanks.push_back(Tank(position.x, position.y, BLUE, &tank_blue, &smoke, 1100.f, position.y + 16, tank_radius, tank_max_health, tank_max_speed));
    }
    //Spawn red tanks
    for (int i = 0; i < num_tanks_red; i++)
    {
        vec2 position{ start_red_x + ((i % max_rows) * spacing), start_red_y + ((i / max_rows) * spacing) };
        tanks.push_back(Tank(position.x, position.y, RED, &tank_red, &smoke, 100.f, position.y + 16, tank_radius, tank_max_health, tank_max_speed));
    }

    particle_beams.push_back(Particle_beam(vec2(590, 327), vec2(100, 50), &particle_beam_sprite, particle_beam_hit_value));
    particle_beams.push_back(Particle_beam(vec2(64, 64), vec2(100, 50), &particle_beam_sprite, particle_beam_hit_value));
    particle_beams.push_back(Particle_beam(vec2(1200, 600), vec2(100, 50), &particle_beam_sprite, particle_beam_hit_value));

    vec2 terrain_size = Terrain::getInstance().getActualTerrainSize();

    this->gamegrid = new St::Grid(terrain_size.x, terrain_size.y, 16);
    this->gamegridchangemanager = new St::GridChangeManager(this->gamegrid);

    for (Tank& tank : this->tanks) {
        this->gamegridchangemanager->addToQueue(new St::GridAddTankCommand(&tank));
    }
    this->gamegridchangemanager->commitChanges();

    if (false) {
        this->printTanksHierarchyWithCombinedHealth();
    }
}

// -----------------------------------------------------------
// Close down application
// -----------------------------------------------------------
void Game::shutdown()
{
}

// -----------------------------------------------------------
// Iterates through all tanks and returns the closest enemy tank for the given tank
// -----------------------------------------------------------
Tank& Game::find_closest_enemy(Tank& current_tank)
{
    float closest_distance = numeric_limits<float>::infinity();
    int closest_index = 0;

    for (int i = 0; i < tanks.size(); i++)
    {
        if (tanks.at(i).allignment != current_tank.allignment && tanks.at(i).active)
        {
            float sqr_dist = fabsf((tanks.at(i).get_position() - current_tank.get_position()).sqr_length());
            if (sqr_dist < closest_distance)
            {
                closest_distance = sqr_dist;
                closest_index = i;
            }
        }
    }

    return tanks.at(closest_index);
}

//Checks if a point lies on the left of an arbitrary angled line
bool Tmpl8::Game::left_of_line(vec2 line_start, vec2 line_end, vec2 point)
{
    return ((line_end.x - line_start.x) * (point.y - line_start.y) - (line_end.y - line_start.y) * (point.x - line_start.x)) < 0;
}

// -----------------------------------------------------------
// Update the game state:
// Move all objects
// Update sprite frames
// Collision detection
// Targeting etc..
// -----------------------------------------------------------
void Game::update(float deltaTime)
{
    //Calculate the route to the destination for each tank using BFS
    //Initializing routes here so it gets counted for performance..
    if (frame_count == 0)
    {
        for (Tank& t : tanks)
        {
            t.set_route(Terrain::getInstance().get_route(t, t.target));
        }
    }

    std::cout << "Set Tanks PushBack: ";
    St::Timer* set_tanks_pushback_timer = new St::Timer();
    if (show_timings) set_tanks_pushback_timer->start();
    (version == 1) ? this->setTanksPushBackOriginal() : this->setTanksPushBack();
    if (show_timings) set_tanks_pushback_timer->stop();
    if (show_timings) set_tanks_pushback_timer->printElapsedTime();

    this->updateTanksPositions();

    std::cout << "Shoot Rockets To Closest Tank: ";
    St::Timer* shoot_rockets_to_closest_tank_timer = new St::Timer();
    if (show_timings) shoot_rockets_to_closest_tank_timer->start();
    (version == 1) ? this->shootRocketsToClosestTanksOriginal() : this->shootRocketsToClosestTanks();
    if (show_timings) shoot_rockets_to_closest_tank_timer->stop();
    if (show_timings) shoot_rockets_to_closest_tank_timer->printElapsedTime();

    this->updateSmokePlumes();
    this->clearForceField();
    this->generateForceField();
    this->checkRocketCollision();
    this->checkRocketCollisionWithForcefield();
    this->clearExplodedRockets();
    this->damageTanksHitByParticleBeam();
    this->updateExplosions();
    this->clearFinishedExplosions();

    if (false) {
        this->printAllGameObjectsPositions();
    }
}

//Check tank collision and nudge tanks away from each other
void Game::setTanksPushBack()
{
    // de getTanksInRadius heeft een Big O van n
    // de eerste for loops zijn loops met constant values
    // de derde loop weet je alleen niet hoe diep die gaat zijn en dus n.
    //
    // In totaal komen we dan uit op een big o van O(n x n) = O(n^2).

    for (Tank& tank : tanks) {
        if (!tank.active) continue;

        std::vector<Tank*> tanks_in_collision_radius = this->gamegrid->getTanksInRadius(&tank, (tank.get_collision_radius()*2));
        for (Tank* other_tank_ptr : tanks_in_collision_radius) {
            Tank other_tank = *other_tank_ptr;

            vec2 dir = tank.get_position() - other_tank.get_position();
            float dir_squared_len = dir.sqr_length();

            float col_squared_len = (tank.get_collision_radius() + other_tank.get_collision_radius());
            col_squared_len *= col_squared_len;

            if (dir_squared_len < col_squared_len) {
                tank.push(dir.normalized(), 1.f);
            }
        }
    }
}

//Check tank collision and nudge tanks away from each other
void Game::setTanksPushBackOriginal()
{
    // We hebben hier te maken met een for loop (n) die de inner loop n times uitvoert, dus O(n x n) = O(n^2)

    for (Tank& tank : tanks)
    {
        if (tank.active)
        {
            for (Tank& other_tank : tanks)
            {
                // te maken met dezelfde tank of andere tank niet active, dan skip.
                if (&tank == &other_tank || !other_tank.active) continue;

                // Totale oppervlakte van beide tank posities.
                vec2 dir = tank.get_position() - other_tank.get_position();
                float dir_squared_len = dir.sqr_length();

                // Collision oppervlakte
                float col_squared_len = (tank.get_collision_radius() + other_tank.get_collision_radius());
                col_squared_len *= col_squared_len;

                // Zitten de tanks binnen de collision oppervlakte van elkaar, dan nudgen.
                if (dir_squared_len < col_squared_len)
                {
                    tank.push(dir.normalized(), 1.f);
                }
            }
        }
    }
}

//Move tanks according to speed and nudges (see above) also reload
void Game::updateTanksPositions()
{
    for (Tank& tank : tanks) {
        if (!tank.active) continue;

        tank.tick(Terrain::getInstance());
        this->gamegridchangemanager->addToQueue(new St::GridUpdateTankCommand(&tank));
    }

    this->gamegridchangemanager->commitChanges();
}

void Game::shootRocketsToClosestTanks() // O(n * n) = O(n^2)
{
    bool must_shoot_rockets = false;
    for (Tank& tank : tanks) { // O(n)
        if (!tank.active) continue;

        if (!tank.rocket_reloaded()) continue;

        must_shoot_rockets = true;
        break;
    }

    // Onzin om anders een hele KDTree op te gaan bouwen.
    if (!must_shoot_rockets) {
        return;
    }

    std::vector<Tank*> blue_tanks;
    std::vector<Tank*> red_tanks;
    for (Tank& tank : tanks) { // O(n)
        if (!tank.active) continue;

        (tank.allignment == BLUE) ? blue_tanks.push_back(&tank) : red_tanks.push_back(&tank);
    }

    St::KDTree* blue_tanks_tree = new St::KDTree(blue_tanks); // O(n)
    St::KDTree* red_tanks_tree = new St::KDTree(red_tanks); // O(n)

    // onderstaande O(n x n) is dominanter t.o.v de bovenstaande O(n) dus deze negeren en de O(n x n) gebruiken

    for (Tank& tank : tanks) { // O(n)
        if (!tank.rocket_reloaded()) continue;

        Tank* target = (tank.allignment == RED) ? blue_tanks_tree->getClosestTank(&tank) : red_tanks_tree->getClosestTank(&tank); // O(n)

        rockets.push_back(Rocket(tank.position, (target->get_position() - tank.position).normalized() * 3, rocket_radius, tank.allignment, ((tank.allignment == RED) ? &rocket_red : &rocket_blue)));
        tank.reload_rocket();
    }
}

//Shoot at closest target if reloaded
void Game::shootRocketsToClosestTanksOriginal()
{
    // find_closest enemey heeft O(n) omdat er 1 loop inzit door alle tanks (kan dus groter worden).
    //   verder heeft deze alleen maar wiskunige calculaties in zich.
    //
    // push_back is O(1)
    // reload_rocket is variabele assignment en dus ook O(1)
    //
    // for loop is O(n)
    //
    // Big o = O(n x n) = O(n^2)

    for (Tank& tank : tanks)
    {
        if (tank.active)
        {
            if (tank.rocket_reloaded())
            {
                Tank& target = find_closest_enemy(tank);

                rockets.push_back(Rocket(tank.position, (target.get_position() - tank.position).normalized() * 3, rocket_radius, tank.allignment, ((tank.allignment == RED) ? &rocket_red : &rocket_blue)));

                tank.reload_rocket();
            }
        }
    }
}

//Update smoke plumes
void Game::updateSmokePlumes()
{
    for (Smoke& smoke : smokes)
    {
        smoke.tick();
    }
}

void Game::clearForceField()
{
    forcefield_hull.clear();
}

//Calculate "forcefield" around active tanks
void Game::generateForceField()
{
    //Find first active tank (this loop is a bit disgusting, fix?)
    int first_active = 0;
    for (Tank& tank : tanks)
    {
        if (tank.active)
        {
            break;
        }
        first_active++;
    }

    vec2 point_on_hull = tanks.at(first_active).position;
    //Find left most tank position
    for (Tank& tank : tanks)
    {
        if (tank.active)
        {
            if (tank.position.x <= point_on_hull.x)
            {
                point_on_hull = tank.position;
            }
        }
    }

    //Calculate convex hull for 'rocket barrier'
    for (Tank& tank : tanks)
    {
        if (tank.active)
        {
            forcefield_hull.push_back(point_on_hull);
            vec2 endpoint = tanks.at(first_active).position;

            for (Tank& tank : tanks)
            {
                if (tank.active)
                {
                    if ((endpoint == point_on_hull) || left_of_line(point_on_hull, endpoint, tank.position))
                    {
                        endpoint = tank.position;
                    }
                }
            }
            point_on_hull = endpoint;

            if (endpoint == forcefield_hull.at(0))
            {
                break;
            }
        }
    }
}

//Update rockets
void Game::checkRocketCollision()
{
    for (Rocket& rocket : rockets)
    {
        rocket.tick();

        //Check if rocket collides with enemy tank, spawn explosion, and if tank is destroyed spawn a smoke plume
        for (Tank& tank : tanks)
        {
            if (tank.active && (tank.allignment != rocket.allignment) && rocket.intersects(tank.position, tank.collision_radius))
            {
                explosions.push_back(Explosion(&explosion, tank.position));

                if (tank.hit(rocket_hit_value))
                {
                    smokes.push_back(Smoke(smoke, tank.position - vec2(7, 24)));
                    this->gamegridchangemanager->addToQueue(new St::GridRemoveTankCommand(&tank));
                }

                rocket.active = false;
                break;
            }
        }
    }

    this->gamegridchangemanager->commitChanges();
}

//Disable rockets if they collide with the "forcefield"
//Hint: A point to convex hull intersection test might be better here? :) (Disable if outside)
void Game::checkRocketCollisionWithForcefield()
{
    for (Rocket& rocket : rockets)
    {
        if (rocket.active)
        {
            for (size_t i = 0; i < forcefield_hull.size(); i++)
            {
                if (circle_segment_intersect(forcefield_hull.at(i), forcefield_hull.at((i + 1) % forcefield_hull.size()), rocket.position, rocket.collision_radius))
                {
                    explosions.push_back(Explosion(&explosion, rocket.position));
                    rocket.active = false;
                }
            }
        }
    }
}

//Remove exploded rockets with remove erase idiom
void Game::clearExplodedRockets()
{
    rockets.erase(std::remove_if(rockets.begin(), rockets.end(), [](const Rocket& rocket) { return !rocket.active; }), rockets.end());
}

//Update particle beams
void Game::damageTanksHitByParticleBeam()
{
    for (Particle_beam& particle_beam : particle_beams)
    {
        particle_beam.tick(tanks);

        //Damage all tanks within the damage window of the beam (the window is an axis-aligned bounding box)
        for (Tank& tank : tanks)
        {
            if (tank.active && particle_beam.rectangle.intersects_circle(tank.get_position(), tank.get_collision_radius()))
            {
                if (tank.hit(particle_beam.damage))
                {
                    smokes.push_back(Smoke(smoke, tank.position - vec2(0, 48)));
                    this->gamegridchangemanager->addToQueue(new St::GridRemoveTankCommand(&tank));
                }
            }
        }
    }

    this->gamegridchangemanager->commitChanges();
}

//Update explosion sprites and remove when done with remove erase idiom
void Game::updateExplosions()
{
    for (Explosion& explosion : explosions)
    {
        explosion.tick();
    }
}

void Game::clearFinishedExplosions()
{
    explosions.erase(std::remove_if(explosions.begin(), explosions.end(), [](const Explosion& explosion) { return explosion.done(); }), explosions.end());
}

/**
 * Visitor Pattern
 */
void Game::printAllGameObjectsPositions()
{
    St::PrintPositionVisitor* print_position_visitor = new St::PrintPositionVisitor();

    for (Tank& tank : tanks) {
        tank.accept(print_position_visitor);
    }

    for (Rocket& rocket : rockets) {
        rocket.accept(print_position_visitor);
    }

    for (Smoke& smoke : smokes) {
        smoke.accept(print_position_visitor);
    }

    for (Explosion& explosion : explosions) {
        explosion.accept(print_position_visitor);
    }
}

/**
 * Composite Pattern
 */
void Game::printTanksHierarchyWithCombinedHealth()
{
    std::vector<St::LeaderTank*> leader_tanks;
    std::string leader_names[10] = { "Mercurius", "Venus", "Aarde", "Mars", "Jupiter", "Saturnus", "Uranus", "Neptunus", "Eris", "Ceres" };
    for (int i = 0; i < 10; i++) {
        St::LeaderTank* leader = new St::LeaderTank(&tanks[i]);
        leader->setName(leader_names[i]);

        for (int j = 10; j < 50; j++) {
            St::SoldierTank* soldier = new St::SoldierTank(&tanks[i+j]);

            for (int n = 50; n < 250; n++) {
                St::TraineeTank* trainee = new St::TraineeTank(&tanks[i+j+n]);
                soldier->addTankUnderCommand(trainee);
            }

            leader->addTankUnderCommand(soldier);
        }

        leader_tanks.push_back(leader);
    }

    for (St::LeaderTank* leader : leader_tanks) {
        std::cout << "Leader '" << leader->getName() <<  "' and other Tanks under his command - Total Health Left: " << leader->getCombinedHealth() << std::endl;
    }
}

//Draw sorted health bars
void Game::drawHealthBarsOriginal() // O(1 + n^2 + n + n) = O(n^2)
{
    for (int t = 0; t < 2; t++) // O(1)
    {
        const int NUM_TANKS = ((t < 1) ? num_tanks_blue : num_tanks_red);

        const int begin = ((t < 1) ? 0 : num_tanks_blue);
        std::vector<const Tank*> sorted_tanks;
        insertion_sort_tanks_health(tanks, sorted_tanks, begin, begin + NUM_TANKS); // O(n^2)
        sorted_tanks.erase(std::remove_if(sorted_tanks.begin(), sorted_tanks.end(), [](const Tank* tank) { return !tank->active; }), sorted_tanks.end()); // O(n)

        draw_health_bars(sorted_tanks, t); // O(n)
    }
}

// Zowel voor de blauwe als rode kant van de tanks
void Game::drawHealthBars() // O(n + n + n) = O(3n) = O(n)
{
    std::vector<Tank*> blue_tanks;
    std::vector<Tank*> red_tanks;
    for (Tank& tank : tanks) { // O(n)
        if (!tank.active) continue;

        (tank.allignment == BLUE) ? blue_tanks.push_back(&tank) : red_tanks.push_back(&tank);
    }

    //St::SortTanksHealth* tanks_sorter = new St::SortTanksHealth(new St::InsertionSortTanksHealthStrategy());
    St::SortTanksHealth* tanks_sorter = new St::SortTanksHealth(new St::CountSortTanksHealthStrategy());

    //std::vector<const Tank*> sorted_blue_tanks = this->getSortedTanksByHealth(blue_tanks);
    std::vector<const Tank*> sorted_blue_tanks = tanks_sorter->getSortedTanks(blue_tanks);
    draw_health_bars(sorted_blue_tanks, 0);

    //std::vector<const Tank*> sorted_red_tanks = this->getSortedTanksByHealth(red_tanks);
    std::vector<const Tank*> sorted_red_tanks = tanks_sorter->getSortedTanks(red_tanks);
    draw_health_bars(sorted_blue_tanks, 1);
}

// Uses Count Sort
std::vector<const Tank*> Game::getSortedTanksByHealth(std::vector<Tank*> tanks_to_sort)
{
    std::vector<int> tanks_health_list(tanks_to_sort.size());
    for (Tank* tank : tanks_to_sort) {
        tanks_health_list.push_back(tank->health);
    }

    std::vector<int> tanks_health_count_list(tank_max_health);
    for (int i = 0; i <= tanks_health_count_list.size(); i++) {
        tanks_health_count_list[i] = 0;
    }
    for (int tank_health : tanks_health_list) {
        tanks_health_count_list[tank_health] = tanks_health_count_list[tank_health]+1;
    }

    std::vector<int> tanks_health_index(tank_max_health);
    for (int i = 0; i <= tanks_health_index.size(); i++) {
        tanks_health_index[i] = 0;
    }

    for (int i = 0; i <= tanks_health_count_list.size(); i++) {
        int value = tanks_health_count_list[i];

        if (i == 0) {
            tanks_health_index[i] = value;
        } else {
            int previous_value = tanks_health_index[i-1];
            tanks_health_index[i] = previous_value + value;
        }
    }

    std::vector<const Tank*> sorted_tanks(tanks_health_index[tanks_health_index.size()]);
    for (Tank* tank : tanks_to_sort) {
        int health = tank->health;
        int position_in_sorted_tanks = tanks_health_index[health];

        sorted_tanks[position_in_sorted_tanks] = tank;

        tanks_health_index[health] = tanks_health_index[health]-1;
    }

    // Remove NULL Pointers
    sorted_tanks.erase(std::remove(sorted_tanks.begin(), sorted_tanks.end(), nullptr), sorted_tanks.end());

    return sorted_tanks;
}

// -----------------------------------------------------------
// Draw all sprites to the screen
// (It is not recommended to multi-thread this function)
// -----------------------------------------------------------
void Game::draw()
{
    // clear the graphics window
    screen->clear(0);

    //Draw background
    Terrain::getInstance().draw(screen);

    //Draw sprites
    for (int i = 0; i < num_tanks_blue + num_tanks_red; i++)
    {
        tanks.at(i).draw(screen);

        vec2 tank_pos = tanks.at(i).get_position();
    }

    for (Rocket& rocket : rockets)
    {
        rocket.draw(screen);
    }

    for (Smoke& smoke : smokes)
    {
        smoke.draw(screen);
    }

    for (Particle_beam& particle_beam : particle_beams)
    {
        particle_beam.draw(screen);
    }

    for (Explosion& explosion : explosions)
    {
        explosion.draw(screen);
    }

    //Draw forcefield (mostly for debugging, its kinda ugly..)
    for (size_t i = 0; i < forcefield_hull.size(); i++)
    {
        vec2 line_start = forcefield_hull.at(i);
        vec2 line_end = forcefield_hull.at((i + 1) % forcefield_hull.size());
        line_start.x += HEALTHBAR_OFFSET;
        line_end.x += HEALTHBAR_OFFSET;
        screen->line(line_start, line_end, 0x0000ff);
    }

    std::cout << "Draw Health Bars: ";
    St::Timer* draw_healthbars_timer = new St::Timer();
    if (show_timings) draw_healthbars_timer->start();
    (version == 1) ? this->drawHealthBarsOriginal() : this->drawHealthBars();
    if (show_timings) draw_healthbars_timer->stop();
    if (show_timings) draw_healthbars_timer->printElapsedTime();

}

// -----------------------------------------------------------
// Sort tanks by health value using insertion sort
// -----------------------------------------------------------
void Tmpl8::Game::insertion_sort_tanks_health(const std::vector<Tank>& original, std::vector<const Tank*>& sorted_tanks, int begin, int end)
{
    const int NUM_TANKS = end - begin;
    sorted_tanks.reserve(NUM_TANKS);
    sorted_tanks.emplace_back(&original.at(begin));

    for (int i = begin + 1; i < (begin + NUM_TANKS); i++) // O(n)
    {
        const Tank& current_tank = original.at(i);

        for (int s = (int)sorted_tanks.size() - 1; s >= 0; s--) // O(n)
        {
            const Tank* current_checking_tank = sorted_tanks.at(s);

            if ((current_checking_tank->compare_health(current_tank) <= 0))
            {
                sorted_tanks.insert(1 + sorted_tanks.begin() + s, &current_tank);
                break;
            }

            if (s == 0)
            {
                sorted_tanks.insert(sorted_tanks.begin(), &current_tank);
                break;
            }
        }
    }
}

// -----------------------------------------------------------
// Draw the health bars based on the given tanks health values
// -----------------------------------------------------------
void Tmpl8::Game::draw_health_bars(const std::vector<const Tank*>& sorted_tanks, const int team)
{
    int health_bar_start_x = (team < 1) ? 0 : (SCRWIDTH - HEALTHBAR_OFFSET) - 1;
    int health_bar_end_x = (team < 1) ? health_bar_width : health_bar_start_x + health_bar_width - 1;

    for (int i = 0; i < SCRHEIGHT - 1; i++)
    {
        //Health bars are 1 pixel each
        int health_bar_start_y = i * 1;
        int health_bar_end_y = health_bar_start_y + 1;

        screen->bar(health_bar_start_x, health_bar_start_y, health_bar_end_x, health_bar_end_y, REDMASK);
    }

    //Draw the <SCRHEIGHT> least healthy tank health bars
    int draw_count = std::min(SCRHEIGHT, (int)sorted_tanks.size());
    for (int i = 0; i < draw_count - 1; i++)
    {
        //Health bars are 1 pixel each
        int health_bar_start_y = i * 1;
        int health_bar_end_y = health_bar_start_y + 1;

        float health_fraction = (1 - ((double)sorted_tanks.at(i)->health / (double)tank_max_health));

        if (team == 0) { screen->bar(health_bar_start_x + (int)((double)health_bar_width * health_fraction), health_bar_start_y, health_bar_end_x, health_bar_end_y, GREENMASK); }
        else { screen->bar(health_bar_start_x, health_bar_start_y, health_bar_end_x - (int)((double)health_bar_width * health_fraction), health_bar_end_y, GREENMASK); }
    }
}

// -----------------------------------------------------------
// When we reach max_frames print the duration and speedup multiplier
// Updating REF_PERFORMANCE at the top of this file with the value
// on your machine gives you an idea of the speedup your optimizations give
// -----------------------------------------------------------
void Tmpl8::Game::measure_performance()
{
    char buffer[128];
    if (frame_count >= max_frames)
    {
        if (!lock_update)
        {
            duration = perf_timer.elapsed();
            cout << "Duration was: " << duration << " (Replace REF_PERFORMANCE with this value)" << endl;
            lock_update = true;
        }

        frame_count--;
    }

    if (lock_update)
    {
        screen->bar(420 + HEALTHBAR_OFFSET, 170, 870 + HEALTHBAR_OFFSET, 430, 0x030000);
        int ms = (int)duration % 1000, sec = ((int)duration / 1000) % 60, min = ((int)duration / 60000);
        sprintf(buffer, "%02i:%02i:%03i", min, sec, ms);
        frame_count_font->centre(screen, buffer, 200);
        sprintf(buffer, "SPEEDUP: %4.1f", REF_PERFORMANCE / duration);
        frame_count_font->centre(screen, buffer, 340);
    }
}

// -----------------------------------------------------------
// Main application tick function
// -----------------------------------------------------------
void Game::tick(float deltaTime)
{
    if (!lock_update)
    {
        update(deltaTime);
    }
    draw();

    measure_performance();

    // print something in the graphics window
    //screen->Print("hello world", 2, 2, 0xffffff);

    // print something to the text window
    //cout << "This goes to the console window." << std::endl;

    //Print frame count
    frame_count++;
    string frame_count_string = "FRAME: " + std::to_string(frame_count);
    frame_count_font->print(screen, frame_count_string.c_str(), 350, 580);
}
