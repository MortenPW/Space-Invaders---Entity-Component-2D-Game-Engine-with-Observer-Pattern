#include "ResourceManager.h"
#include "EntityManager.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "PlayerInputComponent.h"
#include "BombInputComponent.h"
#include "BulletInputComponent.h"
#include "BulletPhysicsComponent.h"
#include "BombPhysicsComponent.h"
#include "AlienInputComponent.h"
#include "AlienPhysicsComponent.h"
#include "ExplosionsPhysicsComponent.h"


game::ResourceManager& game::ResourceManager::instance()
{
	static ResourceManager instance;
	return instance;
}

game::ResourceManager::ResourceManager()
{
	update_screen_dimensions();
}

std::string game::ResourceManager::window_title() const
{
	return "Space Invaders";
}

void game::ResourceManager::update_screen_dimensions()
{
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
}

void game::ResourceManager::screen_dimensions(int& width, int& height) const
{
	width = screen_width_;
	height = screen_height_;
}

void game::ResourceManager::load_scene() const
{
	// TODO: Lag eksplosjoner som entities i en simpel lokal vektor uten id-er.
	// State / scene objects
	human_player(); // id 1
	bullet(); // id 2, etc
	bomb();
	bomb();
	bomb();
	shields(); // 6, 7, 8, 9
	aliens(); // TODO: Må være sist
}

void game::ResourceManager::scene_background(int& r, int& g, int& b, int& a) const
{
	// Black background
	r = 0;
	g = 0;
	b = 0;
	a = 255;
}

int game::ResourceManager::screen_width() const
{
	return screen_width_;
}

int game::ResourceManager::screen_height() const
{
	return screen_height_;
}

void game::ResourceManager::add_explosion(const int x, const int y)
{
	if (y > screen_height() - 180)
	{
		auto entity = std::make_unique<Entity>();

		entity->position.set_x(x);
		entity->position.set_y(y+17);
		entity->dimension.set_x(8 * size_multiplier_);
		entity->dimension.set_y(8 * size_multiplier_);

		entity->set_base_speed(0);
		entity->set_texture("images/explosion.png");

		// TODO: Skulle hatt tid til å fikse colliders slik at underliggende 
		// TODO: colliders ble ignorert dersom explosion collider lå over.

		entity->add(new GraphicsComponent(entity.get()));
		entity->add(new ExplosionsPhysicsComponent(entity.get()));

		explosions_.push_back(std::move(entity));
	}
}

void game::ResourceManager::human_player() const
{
	auto entity = std::make_unique<Entity>();

	entity->position.set_x(screen_width_ / 2);
	entity->position.set_y(screen_height_ - 100);
	entity->dimension.set_x(13 * size_multiplier_);
	entity->dimension.set_y(9 * size_multiplier_);

	entity->set_base_speed(10);
	entity->set_texture("images/iplayer.png");

	entity->add(new PlayerInputComponent(entity.get()));
	entity->add(new GraphicsComponent(entity.get()));
	entity->add(new PhysicsComponent(entity.get()));
	
	EntityManager::instance().register_entity(entity);
}

void game::ResourceManager::bullet() const
{
	auto entity = std::make_unique<Entity>();

	entity->position.set_x(-100);
	entity->position.set_y(400);
	entity->set_base_speed(10);
	entity->set_texture("images/ilaser.png");

	entity->add(new BulletInputComponent(entity.get()));
	entity->add(new GraphicsComponent(entity.get()));
	entity->add(new BulletPhysicsComponent(entity.get()));

	EntityManager::instance().register_entity(entity);
}

void game::ResourceManager::bomb() const
{
	auto entity = std::make_unique<Entity>();

	entity->position.set_x(-100);
	entity->position.set_y(0);
	entity->dimension.set_x(7 * size_multiplier_);
	entity->dimension.set_y(11 * size_multiplier_);
	entity->set_base_speed(5);
	entity->set_texture("images/lightning.png");

	entity->add(new BombInputComponent(entity.get()));
	entity->add(new GraphicsComponent(entity.get(), 2));
	entity->add(new BombPhysicsComponent(entity.get()));

	EntityManager::instance().register_entity(entity);
}

void game::ResourceManager::shields() const
{
	for (auto i = 0; i <= 4; ++i)
	{
		auto entity = std::make_unique<Entity>();

		entity->position.set_x(100 * i + 50);
		entity->position.set_y(screen_height_ - 155);
		entity->dimension.set_x(22 * size_multiplier_);
		entity->dimension.set_y(17 * size_multiplier_);
		entity->set_base_speed(0);
		entity->set_texture("images/ishield.png");

		entity->add(new GraphicsComponent(entity.get()));
		entity->add(new PhysicsComponent(entity.get()));

		EntityManager::instance().register_entity(entity);
	}
}

void game::ResourceManager::aliens() const
{
	for (auto i = 0; i <= 10; ++i)
	{
		auto entity = std::make_unique<Entity>();

		entity->position.set_x(35 * i + 30);
		entity->position.set_y(screen_height_ - 300);
		entity->dimension.set_x(24 * size_multiplier_);
		entity->dimension.set_y(16 * size_multiplier_);
		entity->set_base_speed(1);
		entity->set_texture("images/alien1.png");

		entity->add(new AlienInputComponent(entity.get()));
		entity->add(new GraphicsComponent(entity.get(), 2));
		entity->add(new AlienPhysicsComponent(entity.get()));

		EntityManager::instance().register_entity(entity);
	}

	for (auto i = 0; i <= 10; ++i)
	{
		auto entity = std::make_unique<Entity>();

		entity->position.set_x(35 * i + 30);
		entity->position.set_y(screen_height_ - 340);
		entity->dimension.set_x(24 * size_multiplier_);
		entity->dimension.set_y(16 * size_multiplier_);
		entity->set_base_speed(1);
		entity->set_texture("images/alien1.png");

		entity->add(new AlienInputComponent(entity.get()));
		entity->add(new GraphicsComponent(entity.get(), 2));
		entity->add(new AlienPhysicsComponent(entity.get()));

		EntityManager::instance().register_entity(entity);
	}

	for (auto i = 0; i <= 10; ++i)
	{
		auto entity = std::make_unique<Entity>();

		entity->position.set_x(35 * i + 30);
		entity->position.set_y(screen_height_ - 380);
		entity->dimension.set_x(22 * size_multiplier_);
		entity->dimension.set_y(16 * size_multiplier_);
		entity->set_base_speed(1);
		entity->set_texture("images/alien2.png");

		entity->add(new AlienInputComponent(entity.get()));
		entity->add(new GraphicsComponent(entity.get(), 2));
		entity->add(new AlienPhysicsComponent(entity.get()));

		EntityManager::instance().register_entity(entity);
	}

	for (auto i = 0; i <= 10; ++i)
	{
		auto entity = std::make_unique<Entity>();

		entity->position.set_x(35 * i + 30);
		entity->position.set_y(screen_height_ - 420);
		entity->dimension.set_x(16 * size_multiplier_);
		entity->dimension.set_y(16 * size_multiplier_);
		entity->set_base_speed(1);
		entity->set_texture("images/alien3.png");

		entity->add(new AlienInputComponent(entity.get()));
		entity->add(new GraphicsComponent(entity.get(), 2));
		entity->add(new AlienPhysicsComponent(entity.get()));

		EntityManager::instance().register_entity(entity);
	}

	for (auto i = 0; i <= 10; ++i)
	{
		auto entity = std::make_unique<Entity>();

		entity->position.set_x(35 * i + 30);
		entity->position.set_y(screen_height_ - 460);
		entity->dimension.set_x(16 * size_multiplier_);
		entity->dimension.set_y(16 * size_multiplier_);
		entity->set_base_speed(1);
		entity->set_texture("images/alien3.png");

		entity->add(new AlienInputComponent(entity.get()));
		entity->add(new GraphicsComponent(entity.get(), 2));
		entity->add(new AlienPhysicsComponent(entity.get()));

		EntityManager::instance().register_entity(entity);
	}
}

const std::vector<std::unique_ptr<game::Entity>>& game::ResourceManager::explosions() const
{
	return explosions_;
}
