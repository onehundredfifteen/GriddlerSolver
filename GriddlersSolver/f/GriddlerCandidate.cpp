// GriddlerCandidate.cpp : Defines a new griddler entity
//

#include "stdafx.h"
#include <algorithm>

#include "GriddlerCandidate.h"

GriddlerCandidate::GriddlerCandidate(BlockCollection blocks, int rows_cnt, int cols_cnt)
{
	init(rows_cnt, cols_cnt);

	for(int i = 0; i < img_rows; ++i) {
			rows.push_back(new GriddlerRow(blocks[i], img_cols));
	}
}
GriddlerCandidate::GriddlerCandidate(BlockCollection blocks, SpanCollection solved_spans, int rows_cnt, int cols_cnt)
{
	init(rows_cnt, cols_cnt);

	for(int i = 0; i < img_rows; ++i) {
			rows.push_back(new GriddlerRow(blocks[i], solved_spans[i], img_cols));
	}
}

GriddlerCandidate::GriddlerCandidate(const GriddlerCandidate &griddler)
{
	if(this == &griddler)
		return;
	
	init(griddler.img_rows, griddler.img_cols);

	for(int i = 0; i < img_rows; ++i) {
		rows.push_back(new GriddlerRow(*(griddler.rows[i])));
	}
}

//destructor
GriddlerCandidate::~GriddlerCandidate() {
	for (std::vector<GriddlerRow*>::iterator it = rows.begin(); it != rows.end(); ++it) {
		delete(*it);
	}
}

//init collections
void GriddlerCandidate::init(int r, int c)
{
	img_rows = r;
	img_cols = c;
	rows.reserve(img_rows);
}

//gets column result
void GriddlerCandidate::FillListByColumnResult(std::vector<int> &result, int column) const
{
	int cnt = 0;

	for(int i = 0; i < img_rows; ++i) {
		if(rows[i]->GetCellByColumn(column)) {
			++cnt;
		}
		else if(cnt != 0) {
			result.push_back(cnt);
			cnt = 0;
		}
	}
	
	if(cnt != 0) //if there is no span at the border
		result.push_back(cnt);
}
void GriddlerCandidate::FillListByResult(bool * result) 
{
	for(int r = 0; r < img_rows; ++r) {
		for(int i = 0; i < img_cols; ++i) {
			result[img_cols * r + i] = rows[r]->GetCellByColumn(i);
		}
	}
}
void GriddlerCandidate::FillListByResult(bool * result, int row_no) 
{
	for(int i = 0; i < img_cols; ++i) {
		result[i] = rows[row_no]->GetCellByColumn(i);
	}
}

//Xover
void GriddlerCandidate::DoCrossingOver(GriddlerCandidate * partner, double chance)
{
	if(this == partner)
		return;

	int i = 0;
	for (std::vector<GriddlerRow*>::iterator it = rows.begin(); it != rows.end(); ++it, ++i) {	
		if(false == (*it)->IsFinal() && RandomGenerator::Next()(0.0, 1.0) >= chance) {
			(*it)->CrossingOver(partner->rows[i]);
		}
	}
}
//Operator mutation
void GriddlerCandidate::DoMutate(double chance)
{
	int i = 0;
	for (std::vector<GriddlerRow*>::iterator it = rows.begin(); it != rows.end(); ++it, ++i) {	
		if(false == (*it)->IsFinal() && RandomGenerator::Next()(0.0, 1.0) >= chance) {
			int f = RandomGenerator::Next()(1, 20);
			if(f <= 3) {
				(*it)->NewMutation();
			}
			//else if(f == 4)
				//(*it)->BasicMutation(); 
			//else if(f == 5)// || f==5)
				//(*it)->BasicMutation(); 
		}
	}
}

void GriddlerCandidate::PrintToStream(std::ostream &stream)
{
	for (std::vector<GriddlerRow*>::iterator it = rows.begin(); it != rows.end(); ++it) {	
		for(int col = 0; col < img_cols; ++col) {
			if((*it)->GetCellByColumn(col))
				stream << '#';
			else
				stream << ' ';
		}

		stream << "...";
		for(int i = 0; i < (*it)->spans.size(); ++i) {
			stream << (*it)->spans[i] << ' ';
		}

		stream << '\n';
	}
	stream << std::endl;
	
	int max_line = 0;
	std::vector< std::vector<int>> c;
	for(int col = 0; col < img_cols; ++col) {	
		std::vector<int> v;
		FillListByColumnResult(v, col);
		c.push_back(v);

		if(max_line < v.size())
			max_line = v.size();
	}

	for(int line = 0; line < max_line; ++line) {
		for(int i = 0; i < img_cols; ++i) {
			if(line < c[i].size()) {
				if(c[i][line] > 9) {
					char r = 'A';
					r += (c[i][line] - 10);
					stream << r;
				}
				else
					stream << c[i][line];
			}
			else 
				stream << ' ';
			
		}
		stream << '\n';
	}

	stream << std::endl;
}




