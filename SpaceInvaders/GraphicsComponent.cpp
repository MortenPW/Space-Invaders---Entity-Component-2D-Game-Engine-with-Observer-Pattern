#include "GraphicsComponent.h"
#include "TextureManager.h"
#include "Entity.h"
#include "RenderManager.h"


game::GraphicsComponent::GraphicsComponent(Entity* entity, const int frames) : Component(entity), frames_(frames)
{
	update_texture();
}

game::GraphicsComponent::~GraphicsComponent()
{
	TextureManager::instance().clear_from_texture_map(entity_->id());
}

void game::GraphicsComponent::update_texture() const
{
	// Load texture
	TextureManager::instance().load(entity_->texture(), entity_->id(), RenderManager::instance().renderer());

	// Set dimenstions to image size unless already set
	if (entity_->dimension.x() == 0 && entity_->dimension.y() == 0)
	{
		set_dimensions_to_image();
	}
}

void game::GraphicsComponent::set_dimensions_to_image() const
{
	entity_->dimension.set_x(TextureManager::instance().image_height(entity_->id()));
	entity_->dimension.set_y(TextureManager::instance().image_width(entity_->id()));
}

void game::GraphicsComponent::update()
{
	if (frames_ > 0)
	{
		if (counter_ > 8)
		{
			++frame_;
			counter_ = 0;
		}

		// Cycle animation
		if (frame_ >= frames_)
		{
			frame_ = 0;
		}

		TextureManager::instance().draw_frame(entity_->id(), entity_->position.x(), entity_->position.y(),
			entity_->dimension.x() / frames_, entity_->dimension.y(), 1, frame_,
			RenderManager::instance().renderer());
	
		++counter_;
	}
	else
	{
		TextureManager::instance().draw_frame(entity_->id(), entity_->position.x(), entity_->position.y(),
											  entity_->dimension.x(), entity_->dimension.y(), 1, 0,
											  RenderManager::instance().renderer());
	}
}

int game::GraphicsComponent::frames() const
{
	return frames_;
}

void game::GraphicsComponent::set_frames(const int frames)
{
	frames_ = frames;
}

int game::GraphicsComponent::frame() const
{
	return frame_;
}

void game::GraphicsComponent::set_frame(const int frame)
{
	frame_ = frame;
}
