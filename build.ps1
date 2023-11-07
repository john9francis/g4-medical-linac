# Change directory to the build folder
cd build

# Run CMake
cmake ..

# Build the project using MSBuild
msbuild g4_medical_linac.sln

# Change directory to the release folder
cd release

# Run the executable
.\g4_medical_linac

# Go back to the root directory
cd ..
cd ..