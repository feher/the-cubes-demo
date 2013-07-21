NOTE: Bitbucket may display the wrong "Size" for the repository (next to the "(download)" link)!
      Just start the download and hopefully your web browser will show the correct
      size (should be less than 5 MiB).

What's this?
---------------------
This application demonstrates a user interface for manipulating 3D objects.
The master branch is kept stable and compilable. New features may be added
any time so, don’t forget to check back here for updates! ;)

Usage
---------------------

Run the executable under "...thecubes\src\thecubes.exe".

In case it does not start up, try one of these:
- Watch the included video and the screenshot. You can get them
  from https://bitbucket.org/feheren-fekete/the-cubes-demo/downloads
- Compile it according to the instructions given in the "Compilation" section.
- Install the Visual C++ Redistributable for Visual Studio 2012 from here
  http://www.microsoft.com/en-au/download/details.aspx?id=30679

The scene can be controlled with the mouse and keyboard.

Controls:
- Create model cube              : Left mouse button on "Try me" cube
- Create model sphere            : Left mouse button on "Try me" sphere
- Remove model object            : Left mouse button on model object
- Move camera up/down/left/right : Hold left mouse button + drag on empty area
- Move camera forward/back       : Hold left control + move mouse up/down
- Pitch/yaw camera               : Hold left shift + move mouse
- Roll camera                    : Hold left alt + move mouse
- Move object                    : Hold left mouse button + drag on model object
- Move object in/out             : Hold left Control + left mouse button + move mouse up/down
                                   on model object. :)
- Enable/disable shadow mapping  : Press the S key.
- Enable/disable shadow map view : Press the D key.
- Show/hide system mouse cursor  : Press the M key.
- Exit                           : Escape key or close the window.

There is an exit animation (all models disappear) and the window closes only when the
animation has finished.

Directory structure
---------------------

- 3rdparty : Third party libraries and components
 - raplavik-cmake-modules : Build system helpers.
 - glfw :    For creating OpenGL context, input and window handling.
 - glm :     For vector and matrix operations.
 - and glew

- src : All code in this directory was written/created from scratch for this
        assignment from empty files.
 - data :          Textures and other resources.
 - shaders :       Shader source files.
 - thecubes.exe :  Compiled binary.
 - main.cpp :      Main entry point.
 - thecubes.cpp :  Main program class.

The rest of the source files are explained in the "Class hierarchy" section below.

Screenshots and videos are available separately at
https://bitbucket.org/feheren-fekete/the-cubes-demo/downloads.

Build environment
---------------------

- Windows 7
- CMake 2.8.*
- Visual Studio 2012 Express

For building in Linux, see the README-linux.txt file
at https://bitbucket.org/feheren-fekete/the-cubes-demo/src

Compilation
---------------------

- Install CMake for Windows.
- Run the CMake GUI.
 - Where is the source code: "...\thecubes" (the top directory with the CMakeLists.txt file)
 - Where to build binaries: "...\thecubes.build" (any empty/non-existent directory)
 - Press "Configure"
  - Select Generator: Visual Studio 11
  - Specify native compilers
 - Keep pressing "Configure" until the red lines disappear from the "Name/Value" list.
 - Press "Generate"
 - Close CMake GUI
- Run Visual Studio
 - Open the solution file "...\thecubes.build\TheCubes.sln"
 - Build the "thecubes" project
 - Run "...\thecubes\src\thecubes.exe"

Class hierarchy
---------------------

- TheCubes : Main program class, handles input, runs animation loop.

- RGlfw : Resource class wrapping around glfw in order to provide automatic cleanup
          when going out of scope or when exceptions occur.

- GlBuffer : Resource class wrapping around OpenGL buffer objects.

- File : Basic utility functions for file handling.

- FrameTimer : A simple FPS counter.

- Geom : Geometry functions used for object picking. E.g. line-sphere intersection.

- Viewport : Represents an OpenGL viewport.

- Camera : The camera representing the user's point of view.

- PointLight : Class representing a point light.

- ShadowMap : Manages the generation of the shadow map texture.

- Object :              Base class for any kind of visible on-screen object.
 - Compass :            The small orientation indicator in the lower right corner.
 - CompassLabel:        Represents the labes (Y, Y and Z) of the axes on the compass.
 - Cursor :             The mouse cursor on the screen.
 - Grid :               Object representing the modeling grid.
 - ShadowMapView :      Displays the generated shadow map texture.
 - TriangleMeshObject : Base class for triangle mesh objects.
  - ActionObject :      The pressable action objects at the lower/upper left corner that create models.
  - ModelObject :       Represents the marble objects that can be created/deleted/moved.

- ObjectData :        Base class for data used by object instances.
 - CompassData :      Data used by Compass objects.
 - GridData :         Data used by Grid objects.
 - LabelData :        Data used by 2D "labels" (e.g. on the compass, the cursor).
 - TriangleMeshData : Data that describes triangle based meshes.
   - CubeData :       Data used by cube objects.
   - SphereData :     Data used by sphere objects.

- Program : Base class for shader programs used by object instances.
- ObjectProgram : Template base class for shader programs used by object instances.
                  Tells whether a program can be used with a specific Object.
 - CompassProgram :            Shader program used by Compass objects.
 - GridProgram :               Shader program used by Grid objects.
 - LabelProgram :              Shader program used by CompassLabel objects.
 - LightTextureProgram :       Shader program that does texturing and lighting.
 - LightTextureShadowProgram : Shader program that does texturing, lighting and shadow mapping.
 - ShadowMapProgram :          Shader program for generating the shadow map texture.
 - ShadowMapViewProgram :      Shader program used by the ShadowMapView.

- Shader : Loads and compiles a vertex or fragment shader.

- ShaderProgram : Represents a shader program.

END OF README
####################
