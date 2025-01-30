#pragma once

#include "../AbstractRow.h"
#include <functional>

class ApproachProvider
{
public:
	ApproachProvider(int rows_cnt, int cols_cnt) : height(rows_cnt), width(cols_cnt), orientation(Orientation::esNormal) {
		cells = new short * [height];
		for(int r = 0; r < height; ++r) {
			cells[r] = new short[width];
			memset(cells[r], 0, sizeof(short) * width);
		}
	}

public: 
	typedef enum {
		esNormal = 1,
		esColumn,
		esRevNormal,
		esRevColumn
	} Orientation;

	virtual ~ApproachProvider() {
		for(int r = 0; r < height; ++r)
			delete [] cells[r];

		delete [] cells;
	}

	virtual short* getRow(int row) {
		return this->cells[row];
	}

	virtual short& edgewiseCell(int row, int col) {
		switch(orientation) {
			case Orientation::esColumn: return this->cells[col][row];
			case Orientation::esRevNormal: return this->cells[row][ (width-1)-col ];
			case Orientation::esRevColumn: return this->cells[ (width-1)-col ][ row ];
			case Orientation::esNormal: 
			default:
				return this->cells[row][col];
		}
	}
	int edgewiseDimension() {
		return orientation == Orientation::esRevColumn || orientation == Orientation::esColumn ? width : height;
	}
	int edgewiseInvDimension() {
		return edgewiseDimension() == height ? width : height;
	}
	void turn(Orientation orientation) {
		this->orientation = orientation;
	}

	/*template <typename Callable>
	void applyToAllDirections(Callable fun) {
		turn(Orientation::esNormal);
		fun;
		turn(Orientation::esColumn);
		fun();
		turn(Orientation::esRevNormal);
		fun();
		turn(Orientation::esRevColumn);
		fun();
	}*/

protected:
	short ** cells;
	const int height;
	const int width;

	Orientation orientation;

};