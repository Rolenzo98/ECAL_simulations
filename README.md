# ECAL_simulations

This repository is supposed to analyze the data from ILD detector simulation.

## Requirements

We use [CMake](https://cmake.org) to build the project.
Minimum of requirements are:
|           | Version              |
|-----------|----------------------|
| CMake     | V3.0                 |
| ROOT      | V6.24/00             |

## Build
In order to build this project, use CMake as following:
```
mkdir build
cd build
cmake ..
make
```
If this gives an error, this may be caused by the version incompatibility from the building of ROOT.
Try changing the `CMAKE_CXX_STANDARD` version in the [CMakeLists.txt](https://github.com/yuichiok/ECAL_simulations/blob/main/CMakeLists.txt#L12-L13).

## Execusion

After the build, execution file `main.exe` should be created.
Execute the code as `./main.exe data.root`.