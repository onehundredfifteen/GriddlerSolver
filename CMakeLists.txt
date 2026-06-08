cmake_minimum_required(VERSION 3.10.0)
project(GriddlerSolver VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(griddlersolver
    /home/saap/Repos/GriddlerSolver/GriddlersSolver/Approach/BasicApproach.cpp
    /home/saap/Repos/GriddlerSolver/GriddlersSolver/Approach/NoApproach.cpp
    /home/saap/Repos/GriddlerSolver/GriddlersSolver/Estimators/BasicEstimator.cpp
    /home/saap/Repos/GriddlerSolver/GriddlersSolver/GeneticAlgorithm.cpp
    /home/saap/Repos/GriddlerSolver/GriddlersSolver/GriddlersSolver.cpp
    /home/saap/Repos/GriddlerSolver/GriddlersSolver/Mutations/Mutation.cpp
    /home/saap/Repos/GriddlerSolver/GriddlersSolver/PopulationAnalyser.cpp
    /home/saap/Repos/GriddlerSolver/GriddlersSolver/Rows/ConstrainedRow.cpp
    /home/saap/Repos/GriddlerSolver/GriddlersSolver/Rows/GriddlerRow.cpp
    /home/saap/Repos/GriddlerSolver/GriddlersSolver/Rows/MutableRow.cpp
    /home/saap/Repos/GriddlerSolver/GriddlersSolver/Selectors/BestOfSelector.cpp
    /home/saap/Repos/GriddlerSolver/GriddlersSolver/Selectors/RouletteSelector.cpp
    /home/saap/Repos/GriddlerSolver/GriddlersSolver/SolutionCandidate.cpp
    /home/saap/Repos/GriddlerSolver/GriddlersSolver/SolutionTable.cpp
)
