#pragma once

//#include "../Rows/MutableRow.h"


/*
Mutation

visitor pattern

*/

class MutableRow; //fd
class Mutation
{
public:
	virtual void visit(MutableRow& row) = 0;
};