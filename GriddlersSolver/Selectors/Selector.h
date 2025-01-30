#pragma once

class Selector
{
public:
	Selector(double _Q[], int _Q_cnt) : Q(_Q), Q_cnt(_Q_cnt)
	{
	}
	virtual ~Selector() {}

	virtual int Next() = 0;

protected:
	const int Q_cnt;
	const double * Q;
};