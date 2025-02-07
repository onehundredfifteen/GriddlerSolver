#include "../stdafx.h"
#include "ConcreteGriddler7x7.h"

std::vector<BlockCollection> ConcreteGriddler7x7::initRows() const {

	/*//rowy
		pattern_rows = new std::vector<int>[imgRows];
		pattern_rows[0].push_back(4);
		pattern_rows[1].push_back(2);
		pattern_rows[1].push_back(2);
		pattern_rows[2].push_back(1);
		pattern_rows[3].push_back(1);
		pattern_rows[3].push_back(1);
		pattern_rows[4].push_back(1);
		pattern_rows[4].push_back(1);
		pattern_rows[5].push_back(1);
		pattern_rows[5].push_back(1);
		pattern_rows[6].push_back(1);
		pattern_rows[6].push_back(5);*/

	return { {4}, {2, 2}, {1}, {1, 1}, {1, 1}, {1, 1}, {1, 5} };
}

std::vector<ColumnCollection> ConcreteGriddler7x7::initCols() const  {

	/*//kolumny
		pattern_cols = new std::vector<int>[imgCols];
		pattern_cols[0].push_back(1);
		pattern_cols[0].push_back(1);
		pattern_cols[1].push_back(2);
		pattern_cols[1].push_back(1);
		pattern_cols[2].push_back(1);
		pattern_cols[2].push_back(1);
		pattern_cols[2].push_back(1);
		pattern_cols[3].push_back(1);
		pattern_cols[3].push_back(1);
		pattern_cols[3].push_back(1);
		pattern_cols[4].push_back(2);
		pattern_cols[4].push_back(1);
		pattern_cols[4].push_back(1);
		pattern_cols[5].push_back(3);
		pattern_cols[5].push_back(1);
		pattern_cols[6].push_back(2);*/

	return { {1, 1}, {2, 1}, {1, 1, 1}, {1, 1, 1}, {2, 1, 1}, {3, 1}, {2} };
}

std::vector<SpanCollection> ConcreteGriddler7x7::GetSolution() const {

	/*//solution = new std::vector<int>[imgRows];
			solution[0].push_back(1);
			solution[0].push_back(2);
			solution[1].push_back(0);
			solution[1].push_back(2);
			solution[1].push_back(1);
			solution[2].push_back(5);
			solution[2].push_back(1);
			solution[3].push_back(3);
			solution[3].push_back(1);
			solution[3].push_back(1);
			solution[4].push_back(2);
			solution[4].push_back(1);
			solution[4].push_back(2);//1 to test last span
			solution[5].push_back(1);
			solution[5].push_back(4);
			solution[5].push_back(0);
			solution[6].push_back(0);
			solution[6].push_back(1);
			solution[6].push_back(0);*/

	return { {1, 2}, {0, 2, 1}, {5, 1}, {3, 1, 1}, {2, 1, 2}, {1, 4, 0}, {0, 1, 0} };
}


/*
Griddler::Griddler(int example)
{
	solution = nullptr;

	if(example == SIMPLE_7x7_GRIDDLER || example == SOLVED_7x7_GRIDDLER) 
	{
		
	}
	else if(example == TEST_20x20_GRIDDLER || example == SOLVED_20x20_GRIDDLER)
	{
		int c = 0;
		imgCols = imgRows = 20;
		
		pattern_rows = new std::vector<int>[imgRows];
		pattern_rows[c++].push_back(7);
		pattern_rows[c].push_back(3);
		pattern_rows[c].push_back(5);
		pattern_rows[c++].push_back(1);
		pattern_rows[c].push_back(5);
		pattern_rows[c].push_back(4);
		pattern_rows[c++].push_back(1);
		pattern_rows[c].push_back(2);
		pattern_rows[c].push_back(2);
		pattern_rows[c].push_back(3);
		pattern_rows[c++].push_back(1);
		pattern_rows[c].push_back(2);
		pattern_rows[c].push_back(1);
		pattern_rows[c++].push_back(6);//5th row
		pattern_rows[c].push_back(3);
		pattern_rows[c].push_back(3);
		pattern_rows[c++].push_back(5);
		pattern_rows[c].push_back(11);
		pattern_rows[c].push_back(2);
		pattern_rows[c++].push_back(1);
		pattern_rows[c++].push_back(17);
		pattern_rows[c].push_back(2);
		pattern_rows[c].push_back(4);
		pattern_rows[c++].push_back(5);
		pattern_rows[c].push_back(7);
		pattern_rows[c].push_back(1);
		pattern_rows[c++].push_back(9); //10th row
		pattern_rows[c].push_back(2);
		pattern_rows[c].push_back(1);
		pattern_rows[c].push_back(1);
		pattern_rows[c].push_back(1);
		pattern_rows[c].push_back(1);
		pattern_rows[c].push_back(3);
		pattern_rows[c++].push_back(3);
		pattern_rows[c].push_back(1);
		pattern_rows[c].push_back(1);
		pattern_rows[c].push_back(1);
		pattern_rows[c].push_back(1);
		pattern_rows[c++].push_back(6);
		pattern_rows[c].push_back(4);
		pattern_rows[c].push_back(1);
		pattern_rows[c++].push_back(2);
		pattern_rows[c].push_back(1);
		pattern_rows[c].push_back(2);
		pattern_rows[c].push_back(1);
		pattern_rows[c++].push_back(3);
		pattern_rows[c].push_back(2);
		pattern_rows[c].push_back(3);
		pattern_rows[c].push_back(2);
		pattern_rows[c++].push_back(2); //15th row
		pattern_rows[c].push_back(2);
		pattern_rows[c].push_back(4);
		pattern_rows[c].push_back(1);
		pattern_rows[c].push_back(3);
		pattern_rows[c++].push_back(1);
		pattern_rows[c].push_back(4);
		pattern_rows[c].push_back(2);
		pattern_rows[c].push_back(1);
		pattern_rows[c++].push_back(4);
		pattern_rows[c].push_back(4);
		pattern_rows[c].push_back(2);
		pattern_rows[c].push_back(1);
		pattern_rows[c++].push_back(2);
		pattern_rows[c].push_back(3);
		pattern_rows[c].push_back(2);
		pattern_rows[c].push_back(1);
		pattern_rows[c++].push_back(2);
		pattern_rows[c].push_back(5); //20th row

		if(example == SOLVED_20x20_GRIDDLER) 
		{
			c = 0;
			solution = new std::vector<int>[imgRows];
			solution[c].push_back(7);
			solution[c++].push_back(6);
			solution[c].push_back(2);
			solution[c].push_back(2);
			solution[c].push_back(1);
			solution[c++].push_back(6);
			solution[c].push_back(1);
			solution[c].push_back(2);
			solution[c].push_back(1);
			solution[c++].push_back(6);
			solution[c].push_back(1);
			solution[c].push_back(1);
			solution[c].push_back(3);
			solution[c].push_back(1);
			solution[c++].push_back(6);
			solution[c].push_back(1);
			solution[c].push_back(2);
			solution[c].push_back(4);
			solution[c++].push_back(4); // 5th row of spans
			solution[c].push_back(1);
			solution[c].push_back(7);
			solution[c].push_back(1);
			solution[c++].push_back(0);
			solution[c].push_back(2);
			solution[c].push_back(1);
			solution[c].push_back(3);
			solution[c++].push_back(0);
			solution[c].push_back(3);
			solution[c++].push_back(0);
			solution[c].push_back(7);
			solution[c].push_back(1);
			solution[c].push_back(1);
			solution[c++].push_back(0);
			solution[c].push_back(1);
			solution[c].push_back(1);
			solution[c].push_back(1);
			solution[c++].push_back(0);// 10th row of spans
			solution[c].push_back(0);
			solution[c].push_back(2);
			solution[c].push_back(1);
			solution[c].push_back(1);
			solution[c].push_back(1);
			solution[c].push_back(1);
			solution[c].push_back(1);
			solution[c++].push_back(1);
			solution[c].push_back(0);
			solution[c].push_back(4);
			solution[c].push_back(1);
			solution[c].push_back(1);
			solution[c].push_back(2);
			solution[c++].push_back(2);
			solution[c].push_back(0);
			solution[c].push_back(8);
			solution[c].push_back(1);
			solution[c++].push_back(4);
			solution[c].push_back(1);
			solution[c].push_back(1);
			solution[c].push_back(7);
			solution[c].push_back(1);
			solution[c++].push_back(3);
			solution[c].push_back(1);
			solution[c].push_back(1);
			solution[c].push_back(5);
			solution[c].push_back(1);
			solution[c++].push_back(3);// 15th row of spans
			solution[c].push_back(2);
			solution[c].push_back(1);
			solution[c].push_back(4);
			solution[c].push_back(1);
			solution[c].push_back(1);
			solution[c++].push_back(0);
			solution[c].push_back(3);
			solution[c].push_back(1);
			solution[c].push_back(3);
			solution[c].push_back(2);
			solution[c++].push_back(3);
			solution[c].push_back(3);
			solution[c].push_back(2);
			solution[c].push_back(2);
			solution[c].push_back(3);
			solution[c++].push_back(1);
			solution[c].push_back(3);
			solution[c].push_back(1);
			solution[c].push_back(1);
			solution[c].push_back(1);
			solution[c++].push_back(6);
			solution[c].push_back(8);
			solution[c++].push_back(7);
		}

		//columns
		c = 0;
		pattern_cols = new std::vector<int>[imgCols];
		pattern_cols[c++].push_back(3);
		pattern_cols[c].push_back(4);
		pattern_cols[c].push_back(2);
		pattern_cols[c++].push_back(3);
		pattern_cols[c].push_back(6);
		pattern_cols[c].push_back(1);
		pattern_cols[c].push_back(1);
		pattern_cols[c++].push_back(2);
		pattern_cols[c].push_back(2);
		pattern_cols[c].push_back(3);
		pattern_cols[c].push_back(1);
		pattern_cols[c].push_back(2);
		pattern_cols[c++].push_back(4);
		pattern_cols[c].push_back(3);
		pattern_cols[c].push_back(2);
		pattern_cols[c].push_back(2);
		pattern_cols[c].push_back(2);
		pattern_cols[c++].push_back(3); // 5th col
		pattern_cols[c].push_back(3);
		pattern_cols[c].push_back(2);
		pattern_cols[c].push_back(1);
		pattern_cols[c].push_back(1);
		pattern_cols[c++].push_back(5);
		pattern_cols[c].push_back(2);
		pattern_cols[c].push_back(2);
		pattern_cols[c++].push_back(4);
		pattern_cols[c].push_back(2);
		pattern_cols[c].push_back(4);
		pattern_cols[c].push_back(1);
		pattern_cols[c].push_back(1);
		pattern_cols[c++].push_back(1);
		pattern_cols[c].push_back(3);
		pattern_cols[c].push_back(3);
		pattern_cols[c].push_back(1);
		pattern_cols[c].push_back(2);
		pattern_cols[c++].push_back(2);
		pattern_cols[c].push_back(4);
		pattern_cols[c].push_back(2);
		pattern_cols[c].push_back(1);
		pattern_cols[c].push_back(1);
		pattern_cols[c].push_back(2);
		pattern_cols[c++].push_back(1); //10th col
		pattern_cols[c].push_back(5);
		pattern_cols[c].push_back(3);
		pattern_cols[c].push_back(1);
		pattern_cols[c++].push_back(3);
		pattern_cols[c].push_back(10);
		pattern_cols[c++].push_back(1);
		pattern_cols[c].push_back(1);
		pattern_cols[c].push_back(11);
		pattern_cols[c++].push_back(2);
		pattern_cols[c].push_back(6);
		pattern_cols[c].push_back(5);
		pattern_cols[c++].push_back(5);
		pattern_cols[c].push_back(1);
		pattern_cols[c].push_back(2);
		pattern_cols[c++].push_back(5); //15th col
		pattern_cols[c].push_back(6);
		pattern_cols[c++].push_back(5);
		pattern_cols[c].push_back(1);
		pattern_cols[c].push_back(5);
		pattern_cols[c++].push_back(4);
		pattern_cols[c].push_back(1);
		pattern_cols[c].push_back(5);
		pattern_cols[c++].push_back(3);
		pattern_cols[c].push_back(1);
		pattern_cols[c].push_back(4);
		pattern_cols[c++].push_back(2);
		pattern_cols[c].push_back(5);
		pattern_cols[c++].push_back(2);//20th col
	}

	approachProvider = new BasicApproach(pattern_rows, pattern_cols,imgRows,imgCols);
}
*/


/*
GriddlerCandidate::GriddlerCandidate(int example)
{
	std::vector<int> * s = nullptr, *g;
	
	if(example == SIMPLE_7x7_GRIDDLER || example == SOLVED_7x7_GRIDDLER) {
		img_cols = img_rows = 7;

		g = new std::vector<int>[img_rows];
		g[0].push_back(4);
		g[1].push_back(2);
		g[1].push_back(2);
		g[2].push_back(1);
		g[3].push_back(1);
		g[3].push_back(1);
		g[4].push_back(1);
		g[4].push_back(1);
		g[5].push_back(1);
		g[5].push_back(1);
		g[6].push_back(1);
		g[6].push_back(5);

		if(example == SOLVED_7x7_GRIDDLER) {
			//spany
			s = new std::vector<int>[img_rows];
			s[0].push_back(1);
			s[0].push_back(2);
			s[1].push_back(0);
			s[1].push_back(2);
			s[1].push_back(1);
			s[2].push_back(5);
			s[2].push_back(1);
			s[3].push_back(3);
			s[3].push_back(1);
			s[3].push_back(1);
			s[4].push_back(2);
			s[4].push_back(1);
			s[4].push_back(2);//1 to test las span
			s[5].push_back(1);
			s[5].push_back(4);
			s[5].push_back(0);
			s[6].push_back(0);
			s[6].push_back(1);
			s[6].push_back(0);
		}
	}

	for(int i = 0; i < img_rows; ++i) {
		if(example == SOLVED_7x7_GRIDDLER)
			rows.push_back(new GriddlerRow2(g[i],s[i], img_cols));
		else //if(example == 2)
			rows.push_back(new GriddlerRow2(g[i], img_cols));
	}

	delete [] g;

	if(s)
		delete [] s;
}*/