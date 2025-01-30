#pragma once

#include "BasicEstimator.h"

class FairEstimator : public BasicEstimator
{
public:
	FairEstimator(ColumnCollection _pattern, int _pattern_size) : BasicEstimator(_pattern, _pattern_size) {}

	virtual double MaxFitness() {
		return col_cnt;
	}

	virtual double estimate(GriddlerCandidate * candidate) {
		int * iter = new int[col_cnt];
		int * jump = new int[col_cnt];
		bool * res = new bool[col_cnt];

		ColumnCollection col_res = new std::vector<int>[col_cnt];

		int row_cnt = col_cnt; //todo
		int fitness = 0;

		////
		memset(iter, 0, col_cnt * sizeof(int));
		memset(jump, 0, col_cnt * sizeof(int));

		
		for(int i = 0; i < col_cnt; ++i)
			candidate->FillListByColumnResult(col_res[i], i);
		//

		for(int r = 0; r < row_cnt && fitness == 0; ++r) {

			candidate->FillListByResult(res, r);

			for(int i = 0; i < col_cnt; ++i) {
				if(candidate->rows[i]->IsFinal())
					continue;

				if(res[i] && (jump[i] == 0 || jump[i] >= r )) {
					//badaj czy blad
					if( iter[i] < col_res[i].size() && iter[i] < pattern[i].size() &&
						col_res[i][ iter[i] ] == pattern[i][ iter[i] ]) {
						//
						jump[i] = pattern[i][ iter[i] ] + 1;
						++iter[i];
					}
					else {
						fitness = r;
						break;
					}
					 
				}
			}

			
		   //;
		}


		delete [] iter;
		delete [] res;
		delete [] jump;
		delete [] col_res;

		return double (fitness > 0 ? fitness : MaxFitness());
	};

};