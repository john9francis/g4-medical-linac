# Change directory to the build folder
cd build

# Run CMake
cmake ..

# Build the project using MSBuild
msbuild g4_medical_linac.sln

# Change directory to the release folder
cd release

# Run the executable with all the outputs
#.\g4_medical_linac basicGraphs.mac
#.\g4_medical_linac FFFgraphs.mac
#.\g4_medical_linac heatMap.mac
.\g4_medical_linac purePhotonGraph.mac

# Go back to the root directory
cd ..
cd ..