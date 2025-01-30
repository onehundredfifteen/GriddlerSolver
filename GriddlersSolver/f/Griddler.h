#pragma once

#include <string>

#include "GriddlerCandidate.h"

#define SIMPLE_7x7_GRIDDLER 0
#define SOLVED_7x7_GRIDDLER 1
#define TEST_20x20_GRIDDLER 2
#define SOLVED_20x20_GRIDDLER 3

class Griddler
{
public:
	Griddler(std::string path_to_griddler_file);
	Griddler(int example);
	~Griddler();

protected:
	ColumnCollection pattern_cols;
	BlockCollection pattern_rows;
	SpanCollection solution;

	int imgCols;
	int imgRows;

protected:
	bool isSolved();

public:
	GriddlerCandidate * GetNewCandidate();
	ColumnCollection GetColumnPattern();
	int GetColumnPatternSize();
};