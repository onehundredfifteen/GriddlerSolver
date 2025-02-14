#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <string>
#include <tuple>
#include "./catch/catch_amalgamated.hpp"
#include "../GriddlersSolver/Rows/GriddlerRow.h"
#include "../GriddlersSolver/Rows/ConstrainedRow.h"
#include "../GriddlersSolver/Rows/MutableRow.h"

#include "../GriddlersSolver/Approach/NoApproach.h"
#include "../GriddlersSolver/Approach/FullSolutionProvider.h"
#include "../GriddlersSolver/Approach/WarpedSolution.h"

#include "../GriddlersSolver/Griddlers/DiagonalGriddler5x5.h"
#include "../GriddlersSolver/Griddlers/ConcreteGriddler7x7.h"
#include "../GriddlersSolver/SolutionCandidate.h"

#include "../GriddlersSolver/Estimators/BasicEstimator.h"

#include "../GriddlersSolver/PopulationGenerator.h"
#include "../GriddlersSolver/Selectors/RouletteSelector.h"
#include "../GriddlersSolver/Selectors/BestOfSelector.h"

#include "../GriddlersSolver/Mutations/BasicMutation.h"

///////////////////////
//Tests for griddler row
//////////////////////
BlockCollection common_blocks = { 2, 2 };
GriddlerRow common_row(common_blocks, 8);
BlockCollection full_blocks = { 8 };
GriddlerRow full_row(full_blocks, 8);
BlockCollection empty_blocks = { 0 };
GriddlerRow empty_row(empty_blocks, 8);
BlockCollection empty_blocks2 = { };
GriddlerRow empty_row2(empty_blocks2, 8);

TEST_CASE("Basic griddler row", "rows") 
{
   SECTION("common row [xx-xx---]") {
        CHECK(common_row.isEmpty() == false);
        CHECK(common_row.getMinimalWidth() == 5);
        CHECK(common_row.getCurrentWidth() == common_row.getMinimalWidth());
        CHECK(common_row.getMaxSpanSize() == 3);
        CHECK(common_row.possibleCombinations() == 10);

        auto [column, expected] = GENERATE(table<int, bool>({
           {0, true},  {1, true},  {2, false},  {3, true},  {4, true}, {5, false}, {6, false}, {7, false}
        }));

        CHECK(common_row.getCellByColumn(column) == expected);
   }
   SECTION("full row [xxxxxxxx]") {
       CHECK(full_row.isEmpty() == false);
       CHECK(full_row.getMinimalWidth() == 8);
       CHECK(full_row.getCurrentWidth() == full_row.getMinimalWidth());
       CHECK(full_row.getMaxSpanSize() == 0);
       CHECK(full_row.possibleCombinations() == 1);

       auto [column, expected] = GENERATE(table<int, bool>({
           {0, true},  {1, true},  {2, true},  {3, true},  {4, true}, {5, true}, {6, true}, {7, true}
       }));

       CHECK(full_row.getCellByColumn(column) == expected);
   }
   SECTION("empty row [--------]") {
       CHECK(empty_row.isEmpty() == true);
       CHECK(empty_row.getMinimalWidth() == 0);
       CHECK(empty_row.getCurrentWidth() != empty_row.getMinimalWidth());
       CHECK(empty_row.getMaxSpanSize() == 8);
       CHECK(empty_row.possibleCombinations() == 1);

       CHECK(empty_row2.isEmpty() == true);
       CHECK(empty_row2.getMinimalWidth() == 0);
       CHECK(empty_row2.getCurrentWidth() != empty_row2.getMinimalWidth());
       CHECK(empty_row2.getMaxSpanSize() == 8);
       CHECK(empty_row2.possibleCombinations() == 1);

       auto [column, expected] = GENERATE(table<int, bool>({
           {0, false},  {1, false},  {2, false},  {3, false},  {4, false}, {5, false}, {6, false}, {7, false}
       }));

       CHECK(empty_row.getCellByColumn(column) == expected);
       CHECK(empty_row2.getCellByColumn(column) == expected);
   }

   SECTION("spanned row [-xx-xx--]") {
       BlockCollection spans = { 1, 1,};
       GriddlerRow spanned_row(common_blocks, spans, 8);

       CHECK(spanned_row.getMinimalWidth() == 5);
       CHECK(spanned_row.getCurrentWidth() == 6);
       CHECK(spanned_row.getMaxSpanSize() == 3);
       CHECK(spanned_row.possibleCombinations() == common_row.possibleCombinations());

       auto [column, expected] = GENERATE(table<int, bool>({
           {0, false},  {1, true},  {2, true},  {3, false},  {4, true}, {5, true}, {6, false}, {7, false}
           }));

       CHECK(spanned_row.getCellByColumn(column) == expected);
   }

  
    /*
     BlockCollection blocks = { 2, 2 };
    GriddlerRow common_row(blocks, 8);

    // Define a table of test cases with tuples
    auto [row, expected] = GENERATE(table<GriddlerRow, int>({
        std::make_tuple(GriddlerRow({2,2}, 8), 1),
        std::make_tuple(GriddlerRow({2,2}, 8), 1),
        std::make_tuple(GriddlerRow({2,2}, 8), 1)
        }));

    auto [row2, expected2] = GENERATE(table<BlockCollection, int>({
       std::make_tuple(BlockCollection({2,2}), 1)
     }));

    // Check if the value matches the expected result
    REQUIRE(GriddlerRow(row).getMinimalWidth() == expected);
    */
}

TEST_CASE("Constrained row", "rows")
{
    SECTION("row [xx-xx---]") {
        ConstrainedRow constrained_row(common_row);
        CellCollection expected_cells = {CellState::Filled,CellState::Filled,CellState::Blank,CellState::Filled,CellState::Filled,CellState::Blank,CellState::Blank,CellState::Blank};
        std::vector<int> expected_image = {1,1,0,2,2,0,0,0};

        REQUIRE(constrained_row.cells == expected_cells);
        REQUIRE(constrained_row.compareAgainst(common_row) == true);
        REQUIRE(constrained_row.compareAgainst(full_row) == false);
        REQUIRE(constrained_row.getRowImage() == expected_image);
    }
    SECTION("full row [xxxxxxxx]") {
        ConstrainedRow constrained_row(full_row);
        CellCollection expected_cells(8, CellState::Filled);
        std::vector<int> expected_image(8, 1);

        REQUIRE(constrained_row.cells == expected_cells);
        REQUIRE(constrained_row.compareAgainst(full_row) == true);
        REQUIRE(constrained_row.compareAgainst(empty_row) == false);
        REQUIRE(constrained_row.getRowImage() == expected_image);
    }
    SECTION("empty row [--------]") {
        ConstrainedRow constrained_row(empty_row);
        ConstrainedRow constrained_row2(empty_row2);  
        CellCollection expected_cells(8, CellState::Blank); 
        std::vector<int> expected_image(8, 0);

        REQUIRE(constrained_row.cells == expected_cells);
        REQUIRE(constrained_row.compareAgainst(empty_row) == true);
        REQUIRE(constrained_row.compareAgainst(common_row) == false);
        REQUIRE(constrained_row.getRowImage() == expected_image);

        REQUIRE(constrained_row2.cells == expected_cells);
        REQUIRE(constrained_row2.compareAgainst(empty_row2) == true);
        REQUIRE(constrained_row2.compareAgainst(common_row) == false);
        REQUIRE(constrained_row2.getRowImage() == expected_image);

        REQUIRE(constrained_row.compareAgainst(empty_row2) == true);
    }
    SECTION("empty row [] by default ctor") {
        ConstrainedRow constrained_row; //def ctr
        CellCollection expected_cells;
        std::vector<int> expected_image;

        REQUIRE(constrained_row.cells == expected_cells);
        //no constraint
        REQUIRE(constrained_row.compareAgainst(empty_row) == true);
        REQUIRE(constrained_row.compareAgainst(common_row) == true);
        REQUIRE(constrained_row.getRowImage() == expected_image);
    }
}

TEST_CASE("Mutable row", "rows")
{
    ConstrainedRow constrained_row_but_empty;
    MutableRow row(common_blocks, 8, constrained_row_but_empty);
    SECTION("New Mutable row is always valid") {       
        
        for (int i = 0; i < 10; ++i) {
            MutableRow _row(common_blocks, 8, constrained_row_but_empty);
            CHECK(_row.isValid() == true);
        }
        REQUIRE(row.isValid() == true);
    }

    SECTION("sanitize / fixMiddleZeroes") {
        SpanCollection spans_zero_middle = { 1, 0 };

        REQUIRE(row.isValid() == true);
        row.getSpans() = spans_zero_middle;
        CHECK(row.isValid() == false);
        row.sanitize();
        REQUIRE(row.isValid() == true);
    }

    SECTION("sanitize / ensureOneMaxSpanAtTime") {
        ConstrainedRow constrained_row_but_empty;
        MutableRow row(common_blocks, 8, constrained_row_but_empty);
        SpanCollection spans_over = { 3, 3 };

        REQUIRE(row.isValid() == true);
        row.getSpans() = spans_over;
        CHECK(row.isValid() == false);
        row.sanitize();
        CHECK(row.isValid() == true);
    }

    SECTION("sanitize / trimSpansToWidth") {
        ConstrainedRow constrained_row_but_empty;
        MutableRow row(common_blocks, 8, constrained_row_but_empty);
        SpanCollection spans_over = {4, 2}; 
        SpanCollection expected = {2, 2};
        SpanCollection expected2 = {3, 1}; //sanitize is random and this is 2nd option

        CHECK(row.isValid() == true);
        row.getSpans() = spans_over;
        CHECK(row.isValid() == false);
        row.sanitize();
        CHECK(row.isValid() == true);
        auto res = row.getSpans();
        CHECK((res == expected || res == expected2));
    }
}


ConcreteGriddler7x7 myGiddler;
DiagonalGriddler5x5 testGiddler;
BlockCollection warp_b = { 1 };
SpanCollection warp_s = { 1 };
GriddlerRow warped(warp_b, warp_s, 5);
ConstrainedRow warped_constraint(warped);

NoApproach no_approach;

TEST_CASE("Random Solution Candidate", "population")
{
    SolutionCandidate candidate(myGiddler, no_approach);
    CHECK(candidate.isSolved(myGiddler) == false);
}

TEST_CASE("Solved Solution Candidate", "population")
{
    FullSolutionProvider fsp(myGiddler);
    SolutionCandidate solved_candidate(myGiddler, fsp);

    ColumnCollection expected_cols = { 1, 1 };
    CellCollection expected_cells = { CellState::Blank,CellState::Filled,CellState::Filled,CellState::Filled,CellState::Filled,CellState::Blank,CellState::Blank };

    REQUIRE(solved_candidate.isSolved(myGiddler) == true);
    CHECK(solved_candidate.GetSolvedColumnPattern(0) == expected_cols);
    CHECK(solved_candidate.GetRowResult(0) == expected_cells);
    CHECK(solved_candidate.GetSolvedColumnPattern() == myGiddler.GetColumnPattern());
}

TEST_CASE("Estimate Candidate of simple griddler", "estimators")
{
    BasicEstimator estimator(testGiddler);
    SolutionCandidate candidate(testGiddler, no_approach);

    FullSolutionProvider fsp(testGiddler);
    SolutionCandidate solved_candidate(testGiddler, fsp);

    //prepare almost perfect solution
    WarpedSolution ws(testGiddler);
    ws.warpRow(0, warped_constraint);

    SolutionCandidate warped_candidate(testGiddler, ws);

    double fitness = estimator.fitness(candidate);
    double fitness_of_solved = estimator.fitness(solved_candidate);
    double fitness_of_warped = estimator.fitness(warped_candidate);

    CHECK(fitness_of_solved == (double)solved_candidate.rowCount);
    CHECK(fitness < fitness_of_solved);
    CHECK(fitness <= fitness_of_warped);
    CHECK(fitness_of_warped < fitness_of_solved);
}

TEST_CASE("Estimate Candidate of more complicated griddler", "estimators")
{
    BasicEstimator estimator(myGiddler);
    SolutionCandidate candidate(myGiddler, no_approach);

    FullSolutionProvider fsp(myGiddler);
    SolutionCandidate solved_candidate(myGiddler, fsp);

    double fitness = estimator.fitness(candidate);
    double fitness_of_solved = estimator.fitness(solved_candidate);
    CHECK(fitness_of_solved == (double)solved_candidate.rowCount);
    CHECK(fitness < fitness_of_solved);
}

template<typename testedSelector>
std::vector<int> __mock_and_test_selector() {
    BasicEstimator estimator(testGiddler);
    SolutionCandidate candidate(testGiddler, no_approach);
    SolutionCandidate candidate2(testGiddler, no_approach);

    FullSolutionProvider fsp(testGiddler);
    SolutionCandidate solved_candidate(testGiddler, fsp);

    //prepare almost perfect solution
    WarpedSolution ws(testGiddler);
    ws.warpRow(0, warped_constraint);

    SolutionCandidate warped_candidate(testGiddler, ws);

    auto population = PopulationGenerator::createPopulationFromArgs(
        solved_candidate, candidate, warped_candidate, candidate2);

    //test here
    testedSelector selector(population, estimator);

    std::vector<int> selection_histogram(population.size(), 0);
    for (int i = 0; i < 10000; ++i) {
        const auto& next = selector.Next();
        auto it = std::find_if(population.begin(), population.end(),
            [&](const SolutionCandidate& c) { return &c == &next; });
        if (it != population.end()) {
            selection_histogram[it - population.begin()]++;
        }
    }
    return selection_histogram;
}

TEST_CASE("Population selection - roulette", "selection")
{
    std::vector<int> selection_histogram = __mock_and_test_selector<RouletteSelector>();
    //solved should be picked most often
    auto max_element = std::max_element(selection_histogram.begin(), selection_histogram.end());

    CHECK(selection_histogram[0] > selection_histogram[2]);
    CHECK(selection_histogram[1] != selection_histogram[3]);
    CHECK(std::distance(selection_histogram.begin(), max_element) == 0);
}

TEST_CASE("Population selection - best of K=3", "selection")
{
    std::vector<int> selection_histogram = __mock_and_test_selector<BestOfSelector<3>>();
    //solved should be picked most often
    auto max_element = std::max_element(selection_histogram.begin(), selection_histogram.end());

    CHECK(selection_histogram[0] > selection_histogram[2]);
    CHECK(selection_histogram[1] != selection_histogram[3]);
    CHECK(std::distance(selection_histogram.begin(), max_element) == 0);
}

TEST_CASE("Basic Mutation", "mutations")
{
    BasicMutation mutation(0.9);
    BasicEstimator estimator(myGiddler);
    FullSolutionProvider fsp(myGiddler);
    SolutionCandidate solved_candidate(myGiddler, fsp);

    double fitness_of_solved = estimator.fitness(solved_candidate);

    solved_candidate.mutate(mutation);
    
    double fitness_of_mutated = estimator.fitness(solved_candidate);
    CHECK(fitness_of_solved == (double)solved_candidate.rowCount);
    CHECK(fitness_of_mutated < fitness_of_solved);
}

TEST_CASE("Crossing over", "mutations")
{
    BasicEstimator estimator(myGiddler);
    FullSolutionProvider fsp(myGiddler);
    SolutionCandidate candidate(myGiddler, no_approach);
    SolutionCandidate solved_candidate(myGiddler, fsp);

    double fitness_of_solved_before = estimator.fitness(solved_candidate);
    double fitness_before = estimator.fitness(candidate);

    solved_candidate.crossingOver(candidate, 0.95);

    double fitness_of_solved_after = estimator.fitness(solved_candidate);
    double fitness_after = estimator.fitness(candidate);

    CHECK(fitness_of_solved_before == (double)solved_candidate.rowCount);
    CHECK(fitness_of_solved_after < fitness_of_solved_before);
}

