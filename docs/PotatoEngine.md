# PotatoEngine
The PotatoEngine is an Game Engine build in C++. It takes lots of inspiration from GameMaker and Unity Engine. There are multiple ways to get the Engine running. In this document we will look at different ways to do this.
 - GLFW is the recommended and easiest way, but does rely on the existance of GLFW in your codebase. (Great for desktop apps)
 - Manual creation is for all other cases.

Support for different ways of initialization will come.

## GLFW initialization
It is recommended to use GLFW for your application or game if your application or game is completely standalone. This is by far the easiest way to create your application. It creates the resource manager and the other EngineContext objects automatically for you.

```C++
#include "platform/glfw/GLFWEngineHelper.h"

void main()
{
	GLFWEngineHelper::init();
	GLFWEngineHelper::create<MyGame>();
	GLFWEngineHelper::destroy();
}

```

## Manual initialization
If you want to have more control over the update rates and everything you can manually create the EngineContext with for everything.

_NOTE: for using certain third party libraries, we will need to initialize those. `glfwInit()` for using GLFW and `FreeImage_Initialise()` for using FreeImage (for textures and fonts (I think, don't quite remember)). Don't forget to call the associated `glfwTerminate()` and `FreeImage_DeInitialise()` at the end of the program. `GLFWEngineHelper::init()` and `GLFWEngineHelper::destroy()` serve this exact purpose._

_NOTE: `std::make_shared` and `std::make_unique`_

You will need to create the ResourceManager. It is not required to be first, but it is the easiest, because it does not need anything else.
```C++
auto resourceManager = std::make_unique<ResourceManager>();
```
Then, you need to create your OpenGL context. You will need to implement the Window class for this, even if your context does not involve a window (Because the context object needs a window).
```C++
auto window = std::make_unique<WindowImplementation>();
```
The `WindowImplementation` is your own implementation. Default implementations currently are:
 - `GLFWWindowWrapper` (Windows, Mac OS, Linux)

After creating those its time to create the EngineConfiguration, and load the default engine configuration file (_"settings/config.ini"_). If you want to use a different configuration file, replace the DEFAULT_GLOBAL_CONFIG_FILE with your `std::string` (filepath).
```C++
EngineConfiguration config;
config.init(DEFAULT_GLOBAL_CONFIG_FILE);
```
And finally we create the context
```C++
auto context = std::make_shared<EngineContext>(
	config, 
	std::move(window), 
	std::move(resourceManager));
```

With our context we can initialize our game
```C++
MyGame game; // No context needed, can be created earlier
game.init(context);
```

Then finally, we can run our game. This code **does not** include all the things found in the `EngineConfiguration`!
```C++
while(!game.isCloseRequested()){
	// Poll window events
	std::vector<Event> events;
	context->getWindow().poll(events);

	// Process events and update everything
	context->getInput().update(events);
	context->getTime().update();

	// Update and draw our game!
	game.update();
	game.render();

	// Swap the back and front buffers
	context->getWindow().swap();
}
```

Lastly, dont forget to clean up things nicely
```C++
game.destroy();
```