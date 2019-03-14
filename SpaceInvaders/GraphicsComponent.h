#ifndef GRAPHICSCOMPONENT
#define GRAPHICSCOMPONENT
#include "Component.h"

namespace game
{
	class GraphicsComponent : public Component
	{
	public:
		explicit GraphicsComponent(Entity* entity, int frames = 0);
		~GraphicsComponent();

		void update_texture() const;
		void set_dimensions_to_image() const;
		void update() override;

		int frames() const;
		void set_frames(int frames);
		int frame() const;
		void set_frame(int frame);

	private:
		int counter_;
		int frames_;
		int frame_;
	};
}

#endif