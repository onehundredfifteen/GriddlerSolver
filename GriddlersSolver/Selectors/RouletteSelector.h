#pragma once

#include "Selector.h"
#include "../RandomGenerator.h"

class RouletteSelector : Selector
{
public:
	RouletteSelector(double _Q[], int _Q_cnt) : Selector(_Q, _Q_cnt)
	{
		Q_sum = 0.0;
		for(int i = 0; i < Q_cnt; ++i)
			Q_sum += Q[i];
		//no need to use kahan algorithm - on 1500 objects we have error = 0,0000000000314
	}
	
	virtual int Next() {
		double P_sum = 0.0;
		double hit = RandomGenerator::Next()(0.0, 1.0);

		for(int i = 0; i < Q_cnt; ++i) {
			P_sum += (Q[i] / Q_sum);

			if(P_sum > hit)
				return i;
		}

		return Q[Q_cnt-1];
	}

protected:
	 double Q_sum;
};