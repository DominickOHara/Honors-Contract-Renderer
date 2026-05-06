Install the model from the "model_attribution" file
Place all textures and images into the app/resources/textures directory.
place the obj file into the app/resources/models directory

To compile, install gcc and cmake. Install python3. Install the Ninja build tools 
(On windows, add an environment path variable to the executable as Ninja has no installer)

On linux, open the terminal and change your working directory to the rpoject.
On windows, open the file-explorerer, click the file path, and type in "cmd" to open the command line
  with the working directory to the project.

On linux run:
cmake -B ./build -S ./
cmake --build ./build

On windows run:
cmake -B .\build -s .\
cmake --build .\build

On linux, install each dependency util all error messages go away.
Search up the specific dependencies as they may differ in name than the missing packages.

make sure working directory is the exact same as the executable.
(can change with cd on both linux and windows)

run in command line with ./app or .\app.exe 
