#pragma once

#include <iostream>
#include <iterator>
#include <algorithm>
#include "ApproachProvider.h"
#include "../Rows/AbstractRow.h"

#define cFILLED 2
#define cBLANK 1
#define cUNKOWN 0

class BasicApproach : public ApproachProvider
{
public:
	BasicApproach(BlockCollection _blocks, ColumnCollection _col_blocks, int height, int width) 
		: ApproachProvider(height, width), blocks(_blocks), col_blocks(_col_blocks) {
		/*cells[0][0]=1;
		cells[0][6]=1;
		cells[0][2]=2;
		cells[0][2]=2;
		cells[1][2]=1;
		cells[1][2]=1;

		cells[4][2]=2;
		cells[4][3]=1;
		cells[4][4]=2;
		*/
		cells[5][6]=2;

		int a = 0;

		for(int r = 0; r < height; ++r)  /// std::cbegin(_blocks); it < std::cend(_blocks); ++it)
			rows.push_back(new AbstractRow(blocks[r], width));

		for(int c = 0; c < width; ++c)  /// std::cbegin(_blocks); it < std::cend(_blocks); ++it)
			cols.push_back(new AbstractRow(col_blocks[c], height));


		covers(blocks, rows);
		turn(Orientation::esColumn);
		covers(col_blocks, cols);

		turn(Orientation::esNormal);
		multiegdes();
		turn(Orientation::esColumn);
		multiegdes();
		turn(Orientation::esRevNormal);
		multiegdes();
		turn(Orientation::esRevColumn);
		multiegdes();

		turn(Orientation::esNormal);
		develop_blocks(blocks, rows);
		turn(Orientation::esColumn);
		develop_blocks(col_blocks, cols);

		PrintToStream(std::cout);
		a=1;
		//AbstractRow * colc = new AbstractRow(cols[5], height);

		/*int aaa[30];
		int x=0;
		aaa[x++] = row->getMinimalWidth();
		aaa[x++] = row->getCandidateWidth();
		aaa[x++] = row->getMaxSpanSize();

		aaa[x++] = 0;*/
	}
private:
	BlockCollection blocks;
	ColumnCollection col_blocks;
	std::vector<AbstractRow *> rows;
	std::vector<AbstractRow *> cols;

protected:
	void PrintToStream(std::ostream &stream)
	{
		for (int i = 0; i < height; ++i) {	
			for(int c = 0; c < width; ++c) {
				switch(cells[i][c])
				{
				case 0: stream << '.'; break;
				case 1: stream << '/'; break;
				case 2: stream << 'O'; break;
				default: stream << '?';
				}
			}
			stream << std::endl;
		}
	}

	virtual int edgewiseBlock(int idx, int block) const {
		switch(orientation) {
			case Orientation::esColumn: return col_blocks[idx][block];
			case Orientation::esRevNormal: {
				std::reverse_iterator< std::vector<int>::iterator > rev = blocks[idx].rbegin();
				return *(rev+block);
			}
			case Orientation::esRevColumn: {
				std::reverse_iterator< std::vector<int>::iterator > rev = col_blocks[idx].rbegin();
				return *(rev+block);
			}
			case Orientation::esNormal: 
			default:
				return blocks[idx][block];
		}
	}

	virtual std::vector<AbstractRow *>& edgewiseRows() {
		switch(orientation) {
			case Orientation::esColumn: ;
			case Orientation::esRevColumn: 
				return cols;
			case Orientation::esRevNormal:
			case Orientation::esNormal: 
			default:
				return rows;
		}
	}

	void applyToAllDirections(void * fun()) {
		turn(Orientation::esNormal);
		fun();
		turn(Orientation::esColumn);
		fun();
		turn(Orientation::esRevNormal);
		fun();
		turn(Orientation::esRevColumn);
		fun();
	}

private:
	/**
	* Basic counter cover 
	**/
	void covers(BlockCollection pattern, std::vector<AbstractRow *> &_arr) {
		int dim = edgewiseDimension();
		for(int i = 0; i < dim; ++i) {
			AbstractRow * my_row = edgewiseRows()[i];
			std::vector<int> my_spans = my_row->getSpans();

			if(my_spans.empty() == false) {//do reverse by increasing 1st span
				my_spans.front() = width - my_row->getMinimalWidth();
			}

			AbstractRow reversed(pattern[i], my_spans, dim);
			std::vector<int> my_row_img = my_row->getRowImage();
			std::vector<int> rv_row_img = reversed.getRowImage();

			if(reversed == *my_row)
				for(int c = 0; c < dim; ++c)
					edgewiseCell(i,c) = cBLANK;

			for(int c = 0; c < edgewiseInvDimension(); ++c) {
				if(my_row_img[c] && my_row_img[c] == rv_row_img[c]) 
					edgewiseCell(i,c) = cFILLED;
			}
		}
	}

	/**
	* Populate blocks over edges
	**/
	void egdes(int depth = 0) {
		int dim = edgewiseDimension();
		for(int i = 0; i < dim; ++i) {
			if(edgewiseCell(i, depth) == cFILLED) {
				int front = edgewiseBlock(i, 0);
				if(depth == 0) //seal edge block
					edgewiseCell(i, front) = cBLANK;
				/*else if(depth-1 == front) {
					edgewiseCell(i, 0) = cBLANK;
					//save blank
					AbstractRow * my_row = edgewiseRows()[i];
					std::vector<int> my_spans = my_row->getSpans();
					my_spans.front() = 1;
					edgewiseRows()[i] = new AbstractRow(*my_row, my_spans);
					delete my_row;
				}*/

				for(int p = depth+1; p < front; ++p)
					edgewiseCell(i, p) = cFILLED; 
			}
		}
	}

	void multiegdes() {
		int dim2 = edgewiseInvDimension();
		for(int i = 0; i < dim2; ++i) {
			egdes(i);
		}
	}

	void develop_blocks(BlockCollection pattern, std::vector<AbstractRow *> &_arr) {
		int dim = edgewiseDimension();
		int inv_dim = edgewiseInvDimension();

		for(int i = 0; i < dim; ++i) {
			int last_blank_idx = -10;
			int min = *std::min_element(pattern[i].begin(), pattern[i].end()); //get widest block
			AbstractRow * my_row = _arr[i];
			std::vector<int> my_row_img = my_row->getRowImage();

			for(int c = 0; c < inv_dim; ++c) {
				if(edgewiseCell(i,c) == cFILLED) {// my_row_img[c] && my_row_img[c] == rv_row_img[c]) 
					if(last_blank_idx == c-1) { //behind us are / - fill the block
						for(int b = 1; b < min; ++b)
							edgewiseCell(i, c + b) = cFILLED;

						//edgewiseCell(i, c + min) = cBLANK; // seal the block
						c += min; //pass to next cell
						continue;
					}
					/*else if(last_blank_idx >= 0 && (c - last_blank_idx < my_row_img[c])){ //far behind us is / - develop the block if suff. long
						int lim = my_row_img[c] - (c - last_blank_idx);
						for(int b = 1; b < lim; ++b)
							edgewiseCell(i, c + b) = cFILLED;

						c += lim; //pass to next cell
						continue;
					}*/
					//else if(last != my_row_img[c]) 
				}
				else if(edgewiseCell(i,c) == cBLANK){
					last_blank_idx = c;
				}
			}
		}

	}
};