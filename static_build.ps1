# Change directory to the build folder
cd static_build

# Run CMake
cmake ..

# Build the project using MSBuild
msbuild /p:Configuration=Release /p:Platform=x64 g4_medical_linac.sln
