#pragma once

#include <functional>
#include "./ConstraintProvider.h"


class ApproachProvider : public ConstraintProvider
{
public:
	ApproachProvider(const Griddler& pattern)
		: ConstraintProvider(pattern),
		orientation(Orientation::esNormal)
	{}

	enum class Orientation {
		esNormal = 1,
		esColumn,
		esRevNormal,
		esRevColumn
	};

protected:
	Orientation orientation;

public:
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
};