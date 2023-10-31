# build script to make our development faster

cd build
cmake ..
msbuild g4-medical-linac.sln
cd release
.\g4-medical-linac
cd ..
cd ..