Compiling in Linux (Ubuntu)
-----------------------------

We assume that you extracted the code into $HOME/thecubes directory.
So, you have $HOME/thecubes/README-linux.txt.

Make sure you have the default gcc C++ development tools available.
You need gcc 4.8 or newer.

Install the following additional packages:

> sudo apt-get install libxrandr-dev libgl1-mesa-dev cmake

Hopefully, these will pull down also all that's necessary.

Next, we generate the make files

> cd $HOME\thecubes
> cmake CMakeLists.txt

If it complains about missing libraries or programs, try to resolve
it. Usually it is obvious. If you don't know what Ubuntu package
contains a missing file or program, you can use this tool to figure it
out:

http://packages.ubuntu.com/

After the cmake successfully ran, we compile with:

> make

This will compile the code and also the 3rdparty tools.
The final executable will be placed in $HOME\thecubes\thecubes.
Now we can run it:

> cd $HOME\thecubes\src
> ../thecubes

We have to run it from the src directory because it looks for resource files
there.

Enjoy!

