// GriddlersSolver.cpp : Defines the entry point for the console application.
//

#define RunTests

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <process.h>

#include "Griddlers/Griddler.h"
#include "GeneticAlgorithm.h"
//#include "Griddlers/ConcreteGriddler7x7.h"
/*
#include "SolutionCandidate.h"

#include "Estimators/ColumnwiseEstimator.h"
#include "Estimators/BasicEstimator.h"
#include "Estimators/EntropyEstimator.h"

#include "Selectors/RouletteSelector.h"
#include "Selectors/By5Selector.h"*/

struct itrec {
	int iter;
	double max;
	double avg;
	double sum;
};

void Alg(std::vector<itrec> &poprec);
void Bulk();
void Standard();


#ifndef RunTests
int main(int argc, char* argv[])
{
	//std::vector<itrec> r;
	//std::cout << "dupa";
	///---Alg(r);
	//--Bulk();
	GA();
	//Standard();

	return 0;
}
#endif

unsigned int __stdcall run_thread(void * arg) 
{
	std::vector<itrec>* v = reinterpret_cast< std::vector<itrec>* >(arg) ;
	Alg(*v);

	_endthreadex(0);

	return 0;
}

void savetocsvmax(std::ofstream &f, std::vector<std::vector<itrec>> &v, int tcnt)
{
	f << "iter;max;avg;sum" << std::endl;
	for (auto it = v.begin(); it < v.end(); ++it) {
		f << (*it).back().iter << ";" <<(*it).back().max << ";" << (*it).back().avg << ";" << (*it).back().sum << std::endl;
	}
}

void savetocsv(std::ofstream &f, std::vector<itrec> &v, int thrid)
{
	f << "Thread;" << thrid << ";popsize;" << (int)(v.front().sum / v.front().avg) << std::endl;
	for (auto it = v.begin(); it < v.end(); ++it) {
		f << (*it).iter << ";" << (*it).max << ";" << (*it).avg << ";" << (*it).sum << std::endl;
	}
}

void Bulk()
{
	const int thsiz = 3;
	std::vector<std::vector<itrec>> svg(thsiz);
	HANDLE hThread[thsiz];

	for(int i = 0; i < thsiz; ++i) {
	 hThread[i] = (HANDLE) _beginthreadex(NULL, 0, run_thread, &svg[i], 0, NULL);
	}

	 WaitForMultipleObjects(thsiz,
											   &hThread[0],
											   true, //wait all
											   INFINITE
											  );

	 std::ofstream str("E:\\ga\\1.csv");

	 savetocsvmax(str,svg,thsiz);
	 for(int i = 0; i < thsiz; ++i) {
	   savetocsv(str, svg[i], i);
	}
	str.close();
}

void Alg(std::vector<itrec> &poprec)
{
	/*
	Griddler griddler(TEST_20x20_GRIDDLER); //SIMPLE_7x7_GRIDDLER TEST_20x20_GRIDDLER // SOLVED_20x20_GRIDDLER
	

	const int pop = 1200;
	GriddlerCandidate ** population = new GriddlerCandidate * [pop];
	GriddlerCandidate ** population_t, **to_del;
	double Q[pop];
	
	for(int i = 0; i < pop; ++i) {
		population[i] = griddler.GetNewCandidate();
	}
	
	bool hit = false;
	bool to_break = false;
	const int max_iter = 80;
	int iter = 1;
	double q;
	double max = 0.0;
	double local_max = 0.0;
	int max_index = 0;
	double pop_avg_diff = 0.0;

	GriddlerCandidate * elite = nullptr;
	
	ColumnwiseEstimator estimator(griddler.getColumnPattern(), griddler.getColumnPatternSize());
	BasicEstimator estimator2(griddler.getColumnPattern(), griddler.getColumnPatternSize());

	while(!to_break)
	{
		itrec rec;
		memset(&rec, 0 , sizeof(rec));

		std::cout << "\nIter " << iter << ": ";

		for(int i = 0; i < pop; ++i) {
			
			q = estimator( population[i] );
			//std::cout << q << " ";
			Q[i]=q;

			hit = (q > 0.99);
			hit = hit == false ? iter >= max_iter : true;

			
			if(q > local_max)
			{
				local_max = q;
				max_index = i;

				std::cout <<  estimator( population[i] ) << "; ";
			}
			if(q > max)
			{
				max = q;

				if(elite)
					delete elite;

				elite = new GriddlerCandidate(*population[max_index]);
			}

			if(hit)
			{
				to_break = true;
			}
			
		}

		rec.max = Q[max_index];
		for(int i = 0; i < pop; ++i) {
			rec.sum += Q[i];
		}
		rec.avg = rec.sum / (double)pop;

		rec.iter = iter;
		poprec.push_back(rec);

		std::cout << char(30) << "=" << (rec.avg - pop_avg_diff) << " > max " << rec.max;
		pop_avg_diff = rec.avg;

		if(!to_break)
		{
			RouletteSelector selector(Q, pop); 
			//By5Selector selector(Q, pop);
			RouletteSelector cx_selector(Q, pop);

			population_t = new GriddlerCandidate * [pop];

			/*for(int i = 0; i < pop; ++i)
				population_t[i] = new GriddlerCandidate( *population[selector.Next()] ); 

			to_del = population;
			population = population_t;

			for(int i = 0; i < pop; i+=2) {
				population[i]->DoCrossingOver(population[selector.Next()], 0.6);	
				//population[i]->DoCrossingOver(population[i+1], 0.6);	
			}*/

			//ruchansko dzieci to pierwsze pol populacji

/*
			for (int i = 0; i < pop; ++i) {


				if (Q[i] < pop_avg_diff) {

					GriddlerCandidate * gc = new GriddlerCandidate(*population[selector.Next()]);
					gc->DoCrossingOver(population[cx_selector.Next()], 0.6);
					population_t[i] = gc;
				}
				//else if(Q[i])
					//population_t[i] = new GriddlerCandidate(*population[i]);
				else
					population_t[i] = new GriddlerCandidate(*population[selector.Next()]);
			}


			to_del = population;
			population = population_t;


			for(int i = 0; i < pop; ++i) {
				population[i]->DoMutate(0.98);
				delete to_del[i];
			}
			delete [] to_del;
			
		}
	
		
		++iter;
	}
	std::cout << std::endl;

	//------------------
	std::vector<double> result, eresult;
	GriddlerCandidate * final = population[max_index];

	if(iter >= max_iter) {
	
		std::cout << "Final max population:\n";
		//estimator.FillListByFitting(result,final);
	
		/*for (std::vector<double>::iterator it = result.begin(); it != result.end(); ++it)
		{	
			std::cout << *it << ' ';
			if(it == result.begin())
				std::cout << "= ";

		
		}*/
/*
		std::cout << Q[max_index] << std::endl;

		final->PrintToStream(std::cout);

		//estimator.FillListByFitting(eresult,elite);
	
		std::cout << "Elite:" << std::endl;
	}
	else 
		std::cout << "Solved:" << std::endl;

	/*for (std::vector<double>::iterator it = eresult.begin(); it != eresult.end(); ++it)
	{	
		std::cout << *it << ' ';
		if(it == eresult.begin())
			std::cout << "= ";
	}*/
/*
	std::cout << estimator(elite) << std::endl;

	elite->PrintToStream(std::cout);

	std::cout << "\nColumn Pattern:\n";
	
	for(int line = 0; line < 7; ++line) {
		for(int i = 0; i < griddler.getColumnPatternSize(); i+=1) {
			if(line < griddler.getColumnPattern()[i].size()) {
				int cc = griddler.getColumnPattern()[i][line];
				if(cc > 9) {
					char r = 'A';
					r += (cc - 10);
					std::cout << r;
				}
				else
					std::cout << cc;
			}
			else 
				std::cout << ' ';
			
		}
		std::cout << '\n';
	}

	int y;
	std::cin >> y;
	*/
}

void Standard() {
	///Griddler griddler(SIMPLE_7x7_GRIDDLER); //SIMPLE_7x7_GRIDDLER TEST_20x20_GRIDDLER // SOLVED_20x20_GRIDDLER


	//const int pop = 1200;
	///GriddlerCandidate ** population = new GriddlerCandidate *[pop];
}



void BruteForce()
{
	//kolumny
	/*std::vector<int> * c = new std::vector<int>[7];
	c[0].push_back(1);
	c[0].push_back(1);
	c[1].push_back(2);
	c[1].push_back(1);
	c[2].push_back(1);
	c[2].push_back(1);
	c[2].push_back(1);
	c[3].push_back(1);
	c[3].push_back(1);
	c[3].push_back(1);
	c[4].push_back(2);
	c[4].push_back(1);
	c[4].push_back(1);
	c[5].push_back(3);
	c[5].push_back(1);
	c[6].push_back(2);
	c[6].push_back(5);
	
	bool hit = false;
	int iter = 1;
	double q;

	BasicEstimator estimator(c,7);
	while(!hit)
	{
		int h = 0;
		
		//GriddlerCandidate * giddler = new GriddlerCandidate(1);

		std::cout << "Iter \n";
		//q = estimator(giddler);
		
		hit = q >= 6;
		
		++iter;

		//if(!hit)
			//delete giddler;
	}
	//std::cout <<::

	delete [] c;*/
}

