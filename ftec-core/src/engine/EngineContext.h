#pragma once

#include <memory>

//All these things tho
#include "EngineConfiguration.h"
#include "resources/ResourceManager.h"
#include "graphics/Window.h"
#include "Input.h"
#include "Time.h"

namespace ftec {

	/**
	 * The EngineContext class is the main context object given to all things that use the engine. 
	 * The EngineContext is basically a global, but not global :)
	 * @see ResourceManager
	 * @see Window
	 * @see Input
	 * @see Time
	 * @see EngineConfiguration
	*/
	class EngineContext {
	private:
		Input m_Input;
		Time m_Time;
		EngineConfiguration m_Config;
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<ResourceManager> m_Resources;
	public:
		/**
		 * Creates the EngineContext with the given Window pointer and ResourceManager pointer. It automatically creates the Input object and the Time object.
		 * It is possible to create the EngineContext without Window or ResourceManager. However, it is strongly recommended against, because of the getWindow and
		 * getResourceManager functions. Note: at this time the EngineConfiguration is immutable.
		*/
		EngineContext(EngineConfiguration configuration = EngineConfiguration(), std::unique_ptr<Window> window = nullptr, std::unique_ptr<ResourceManager> resources = nullptr);

		const EngineConfiguration &getConfiguration() const;
		EngineConfiguration setConfiguration(EngineConfiguration configuration) { m_Config = configuration; };

		Window& getWindow() {return *m_Window; }
		const Window& getWindow() const { return *m_Window; }

		ResourceManager& getResourceManager() { return *m_Resources; }
		const ResourceManager& getResourceManager() const { return *m_Resources; }

		Input &getInput() { return m_Input; };
		const Input &getInput() const { return m_Input; };

		Time &getTime() { return m_Time; };
		const Time &getTime() const { return m_Time; };

		void setWindow(std::unique_ptr<Window> window) { m_Window = std::move(window); }
		void setResouceManager(std::unique_ptr<ResourceManager> resourcemanager) { m_Resources = std::move(resourcemanager); }
	};
}