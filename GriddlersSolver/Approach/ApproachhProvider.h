#pragma once

#include "../Rows/ConstrainedRow.h"
#include <functional>

class ConstraintProvider
{
public:
	ConstraintProvider(const Griddler& pattern)
		: cells(pattern),
		height(pattern.GetImageHeight()),
		width(pattern.GetImageWidth()),
		orientation(Orientation::esNormal)
	{}

protected:
	ConstraintProvider()
		: height(0), width(0), orientation(Orientation::esNormal)
	{}

public:
	enum class Orientation {
		esNormal = 1,
		esColumn,
		esRevNormal,
		esRevColumn
	};


	virtual const ConstrainedRow& getRow(int row) const = 0;

	virtual CellState& edgewiseCell(int row, int col) {
		/*switch(orientation) {
			case Orientation::esColumn: return this->cells[col][row];
			case Orientation::esRevNormal: return this->cells[row][ (width-1)-col ];
			case Orientation::esRevColumn: return this->cells[ (width-1)-col ][ row ];
			case Orientation::esNormal:
			default:
				return this->cells[row][col];
		}*/
		CellState r;
		return r;
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
	const int height;
	const int width;
	SolutionContent cells;

	Orientation orientation;

};