Compilation:

Download the repository.

Install the model from the "model_attribution" file
Make sure to install the textures as well (the download gives 4 links, install the object model and textures)

Place all textures and images into the app/resources/textures directory.
place the obj file into the app/resources/models directory

To compile, install gcc and cmake. Install python3. If on windows, install Visual Studio 2026

Using pip, run in the terminal (command prompt on windows)
pip install glad

On linux, open the terminal and change your working directory to the poject.
On windows, open the file-explorerer, click the file path, and type in "cmd" to open the command line
  with the working directory to the project.

On linux run:
cmake -B ./build -S ./
cmake --build ./build

On windows run:
cmake -B .\build -s .\
cmake --build .\build --config Release

On linux, install each dependency util all error messages go away.
Search up the specific dependencies as they may differ in name than the missing packages.

make sure working directory is the exact same as the executable.
(can change with cd on both linux and windows)
The executible can be found by searching for it in windows (app.exe)

If it does not appear (app on linux, app.exe on windows) compilation failed.

run in command line with ./app or .\app.exe once your working directory is the same as the executable
