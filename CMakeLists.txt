cmake_minimum_required(VERSION 3.10.0)
project(GriddlerSolver VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-fpermissive)

set(GRIDDLE_SOLVER_SOURCES
    GriddlersSolver/Approach/BasicApproach.cpp
    GriddlersSolver/Approach/NoApproach.cpp
    GriddlersSolver/Estimators/Estimator.cpp
    GriddlersSolver/GeneticAlgorithm.cpp
    GriddlersSolver/Mutations/Mutation.cpp
    GriddlersSolver/PopulationAnalyser.cpp
    GriddlersSolver/Rows/ConstrainedRow.cpp
    GriddlersSolver/Rows/GriddlerRow.cpp
    GriddlersSolver/Rows/MutableRow.cpp
    GriddlersSolver/Selectors/RouletteSelector.cpp
    GriddlersSolver/SolutionCandidate.cpp
    GriddlersSolver/SolutionTable.cpp
)

add_library(griddlersolver_lib STATIC ${GRIDDLE_SOLVER_SOURCES})
add_executable(griddlersolver GriddlersSolver/GriddlersSolver.cpp)
target_link_libraries(griddlersolver PRIVATE griddlersolver_lib)

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests tests/tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain griddlersolver_lib)
include(CTest)
include(Catch)
catch_discover_tests(tests)

