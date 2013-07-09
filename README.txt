Hi,

Here you can find my solution of the assignment for the SW Engineer position
at Rightware.

This assignment was a lot of fun to work on. I could go on adding features
forever :) but I have to stop at some point. So, I consider it done for now.
I hope you will like it as much as I liked working on it.

As requested, this is a small demo according to the following description:

[QUOTE]

Create a 3D user interface with the following features:
- Use OpenGL or OpenGL ES 2.0 for rendering
- Per pixel shading
- Dynamic number of 3D objects in a scene
- 3D objects can be simple generated models (e.g. box or sphere)
- 3D picking to recognize if user has clicked a 3D object
- 3D button to add objects: Clicking it adds a new 3D object to the scene
- Clicking any other 3D object deletes it from the scene
- Third party libraries can be used, but picking and rendering should be
own code

[END QUOTE]

All the required features are implemented and functional.
I also added a few extra animations, decorations and controls.
The source code is in C++. I've put the empasis on clarity of code.
It is written and organized in a way that supports maintainability, modularity
and extensibility.

I am looking forward to hearing from you!

Thank you,
Gabor Fekete


Usage
---------------------

Run the executable under "...thecubes\src\thecubes.exe".

In case it does not start up, try one of these:
- Watch the included video (video.mp4)
- Compile it according to the instructions given in the "Compilation" section.
- Install the Visual C++ Redistributable for Visual Studio 2012 from here
  http://www.microsoft.com/en-au/download/details.aspx?id=30679

The scene can be controlled with the mouse and keyboard.

Controls:
- Create marble cube             : Left mouse button on "Try me" cube
- Remove marble cube             : Left mouse button on marble cube
- Move camera up/down/left/right : Hold left mouse button + drag on empty area
- Move camera forward/back       : Hold left control + move mouse up/down
- Pitch/yaw camera               : Hold left shift + move mouse
- Roll camera                    : Hold left alt + move mouse
- Move object                    : Hold left mouse button + drag on marbe cube
- Exit                           : Escape key or close the window.

There is an exit animation (all cubes disappear) and the window closes only when the
animation has finished.

Directory structure
---------------------

- 3rdparty : Third party libraries and components
 - raplavik-cmake-modules : Build system helpers.
 - glfw    : For creating OpenGL context, input and window handling.
 - glm     : For vector and matrix operations.
 - and glew
- src            : All code in this directory was written/created from scratch for this
                   assignment from empty files.
 - data          : Textures and other resources.
 - shaders       : Shader source files.
 - thecubes.exe  : Compiled binary.
 - main.cpp      : Main entry point.
 - thecubes.cpp  : Main program class.
- screenshot.jpg : A screenshot.
- video.mp4      : A video.

The rest of the source files are explained in the "Class hierarchy" section below...


Build environemnt
---------------------

- Windows 7
- CMake 2.8
- Visual Studio 2012 Express

Compilation
---------------------

- Install CMake for Windows.
- Run the CMake GUI.
 - Where is the source code: "...\thecubes" (the top directory with the CMakeLists.txt file)
 - Where to build binaries: "...\thecubes.build" (any empty/non-existent directory)
 - Press "Configure"
  - Select Generator: Visual Studio 11
  - Specify native compilers
 - Keep pressing "Configure" until red lines disappear.
 - Press "Generate"
 - Close CMake GUI
- Run Visual Studio
 - Open the solution file "...\thecubes.build\TheCubes.sln"
 - Build "thecubes"
 - Run "...\thecubes\src\thecubes.exe"

Class hierarchy
---------------------

- TheCubes : Main program class, handles input, runs animation loop.

- RGlfw : Resource class wrapping around glfw in order to provide automatic cleanup
          when going out of scope or when exceptions occur.

- File : Basic utility functions for file handling.

- Geom : Geometry functions used for object picking. E.g. line-sphere intersection.

- Viewport : Represents an OpenGL viewport. Used to draw the ActionCube and the Compass
             in their own viewports.

- Camera : The camera representing the user's point of view.

- PointLight : Class representing a point light.

- Object :       Base class for any kind of visible on-screen object.
 - Compass :     The small orientation indicator in the lower right corner.
                 Shows the direction of the world's X (red) Y (green) Z (blue) coordinates.
 - CompassLabel: Represents the labes of the axes on the compass.
 - Cube :        Base class for cube objects. Represents a textured and lit cube.
  - ActionCube : The pressable action cube at the lower left corner that creates marble cubes.
  - ModelCube :  Represents the marble cubes that can be created/deleted/moved.
 - Grid :        Object representing the modeling grid.

- ObjectData :        Base class for data used by object instances.
 - CompassData :      Data used by Compass objects.
 - CompassLabelData : Data used by the axes labels of the compass.
 - CubeData :         Data used by Cube objects.
 - GridData :         Data used by Grid objects.

- ObjectProgram : Base class for shader programs used by object instances.
 - CompassLabelProgram : Shader program used by CompassLabel objects.
 - CubeProgram :         Shader program used by Cube objects.
 - GridProgram :         Shader program used by Grid objects.

- Shader : Loads and compiles a vertex or fragment shader.

- ShaderProgram : Represents a shader program.


END OF README
####################