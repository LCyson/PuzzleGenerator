#include "PuzzleGenerator.h"
using namespace std;

PuzzleGenerator::PuzzleGenerator(int _nRows, int _nColumns, int _minVal, int _maxVal)
	:nRows(_nRows), nColumns(_nColumns), minVal(_minVal), maxVal(_maxVal)
{}

Puzzle PuzzleGenerator::GeneratePuzzle()
{
	timer.StartTimer();
	maxtime = 59.9;	// To make sure we don't exceed a minute
	
	return Simulated(60);
	return RandomWalk(5);	// Do a random walk for 5 seconds and return the solution.

	// We could also do as many random walks as we can within the given time limit.
	while (timer.GetElapsedTime()-5 < maxtime)
	{
		Puzzle p = RandomWalk(5);
		// Check if p is better than the best puzzle we have found so far.
	}
}

Puzzle PuzzleGenerator::Simulated(double timelimit) 
{
	Puzzle s(nRows, nColumns, minVal, maxVal);	// Generate a random puzzle with the specified values.
			
	// Keep track of the time so we don't exceed it.
	Timer t;
	t.StartTimer();
	srand( (unsigned)time(NULL) );

	Puzzle restart = s;
	
	// Loop until we hit the time limit.
	while (0.1 < timelimit-t.GetElapsedTime())	// To make sure that we don't exceed the time limit, we stop just before we hit the time limit.
	{	
		//choose a possible neighbour
		Puzzle sNew = s.GetRandomSuccessor();

		// Update the current best solution.
		double random = ((double)rand()/(double)RAND_MAX);	
		if ( PE(s.GetValue(), sNew.GetValue(), (timelimit-t.GetElapsedTime())*5) >= random )
		{
			s = sNew;
			// std::cout<<sNew.GetValue()<<std::endl;
		}
		if ( restart.GetValue() < s.GetValue() )
		{
			restart = s;
		}
	}
	
	if ( restart.GetValue() > s.GetValue() )
	{
		s = restart;
	}
	return s;
		// std::cout<<"value" << p.GetValue() - p.GetRandomSuccessor().GetValue()<<std::endl;
}

double PuzzleGenerator::PE(double e, double eN, double T)
{
	// std::cout<<"PE = " << eN - e << "/" << T <<std::endl;
	if (e < eN) return 1;
	return (exp(-(e - eN)/T));
}

Puzzle PuzzleGenerator::RandomWalk(double timelimit)
{
	// A very simple function that start at a random configuration and keeps randomly modifying it
	// until t hits the time limit. Returns the best solution found so far.

	Puzzle p(nRows, nColumns, minVal, maxVal);	// Generate a random puzzle with the specified values.
	
	// Keep track of the best puzzle found so far (and its value).
	Puzzle bestPuzzle = p;			
	int bestValue = p.GetValue();
	
	// Keep track of the time so we don't exceed it.
	Timer t;
	t.StartTimer();
	
	// Loop until we hit the time limit.
	while (t.GetElapsedTime() < timelimit-0.1)	// To make sure that we don't exceed the time limit, we stop just before we hit the time limit.
	{
		// Generate a successor of p by randomly changing the value of a random cell 
		// (since we are doing a random walk, we just replace p with its successor).
		p = p.GetRandomSuccessor();
		
		// Update the current best solution.
		if (p.GetValue() > bestValue)	// Calling GetValue() for the first time is costly
										// since the puzzle has to be evaluated first.
		{
			bestValue = p.GetValue();	// Calling it a second time simply returns the value that was computed before.
			bestPuzzle = p;
		}
	}
	
	return bestPuzzle;
	
	// The following code is not executed in this function. It exists just as an example for getting all the successors of a puzzle.
	vector<Puzzle> successors;
	bestPuzzle.GetAllSuccessors(successors);
}
