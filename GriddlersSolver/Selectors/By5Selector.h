#pragma once

#pragma once

#include "Selector.h"
#include "../RandomGenerator.h"

#include <algorithm>
#include <cmath>

#undef min

class By5Selector : Selector
{
public:
	By5Selector(double _Q[], int _Q_cnt) : Selector(_Q, _Q_cnt)
	{
		next5 = 0;
	}

	virtual int Next() {
		int range = std::min(next5 + 5, Q_cnt);
		auto local_max = std::max_element(Q + next5, Q + range);

		

		if (this->next5 < Q_cnt) {
			this->next5 += 5;
		}
		else {
			local_max = std::max_element(Q, Q + 5);
			this->next5 = 5;
		}
			
			

		return std::distance(Q, local_max);
	}

protected:
	int next5;
};
