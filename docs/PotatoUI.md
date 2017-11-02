# PotatoUI

PotatoUI is de main UI library for the PotatoEngine (FTec Engine). First, we will go into the essentials and the basic structure of the PotatoUI code. Afterwards, we will add some documentation on all of the available components.

## Essentials
The PotatoUI revolves around two main classes:
 - `PotatoUI`
 - `Panel`

 The `Panel` is the overarching class for all components (Maybe it should be called Component instead). This is the base class for classes like `Button` and `LinearLayout`. 

 The `PotatoUI` class is the class that handles the whole UI situation. It has one 'root' panel and _can have multiple higher layers_*. It handles all the inputs and passes them to the right `Panel`'s.

 *_Not currently supported_

 ## PotatoUI
To create a `PotatoUI` you can just create one (`std::make_shared` recommended). To use the UI, you must call `ui->update()` every update, and `ui->render()` every time you render. The PotatoUI itself will figure out whether or not a redraw is needed at this time. 

_At the moment of writing, the `ui->update()` also does the event handling and passing. However, this is probably going to change with a new update. It is quite possible that you need to call `ui->processEvents()` or something simular later on._


 ## XML
There is a class `UILoader` that can load UI's from XML. This is the easiest way to create larger UI's. You can load your UI file by calling `UILoader::load(std::string filename)` after including `potato_ui\UILoader.h`. The XML looks like this: 

```XML
<LinearLayout
    width="match_parent"
    height="match_parent"
    orientation="vertical">

    <TextField
        width="match_parent"
        height="wrap_content"
        hint="User name" />

    <Button
        width="match_parent"
        height="wrap_content"
        text="Press me!" />

</LinearLayout>
```

There is always one root element. Usually this will be a layout type, but this is not strictly required. Most things like `Button` and `TextField` will ignore child elements. Default properties include things like `weight`, `width` and `height`. The possible values are:
 - `width = ["match_parent", "wrap_content", "128", "48"]` (or any other number,in pixels)
 - `height = ["match_parent", "wrap_content", "128", "48"]` (or any other number,in pixels)

 To add your custom loader for your own component you can call:
 ```C++
 UILoader::registerLoader(
     "MyComponent", 
     [](ftec::xml::XMLNode &node) -> std::shared_ptr<Panel>
    {
        auto component = std::make_shared<MyComponent>();
        // Do things with the XMLNode
        return component;
    }
 ]);
 ```


## UI Styles
Currently there is an implementation but it is only editable via code with the `PotatoStyle` class.