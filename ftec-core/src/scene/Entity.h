#pragma once

/*
The Entity class.

functions that can be overwritten are:

onStart		-> gets called when the entity is added to a scene. m_Scene has been set at this point
onEnd		-> gets called when the entity leaves the scene. **After** this call is complete, m_Scene is set to nullptr
update		-> gets called every frame when the entity is in a scene
render2D	-> gets called every time the scene gets rendered in 2D (See Scene::SceneMode)
render3D	-> gets called every time the scene gets rendered in 3D (See Scene::SceneMode)

*/
namespace ftec {

	class Graphics;
	class Graphics2D;
	class Scene;

	class Entity {
	protected:
		Scene *m_Scene;
	public:
		Entity() = default;
		virtual ~Entity() = default;

		virtual void onStart() {};
		virtual void onEnd() {};

		virtual void update() {};
		
		virtual void render3D() {};
		virtual void render2D(Graphics2D &graphics) {};

		void setScene(Scene *scene) { m_Scene = scene; }
		Scene *getScene() { return m_Scene; }
	
		friend Scene;
	};
}

