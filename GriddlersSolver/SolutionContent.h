#pragma once

#include "./types.h"
#include "SolutionCandidate.h"

/*
SolutionContent

can print cellcollection 
offset aware
*/

class SolutionContent
{
public:
	// Primary constructor
	SolutionContent(const SolutionCandidate& sc)
		: offset(sc.colCount)
	{		
		content.reserve(sc.rowCount * sc.colCount);
		for (int i = 0; i < sc.rowCount; ++i) {
			// Move cells into content
			auto cells = sc.GetRowResult(i);
			content.insert(content.end(), std::make_move_iterator(cells.begin()), std::make_move_iterator(cells.end()));
		}	
	}


private:
	CellCollection content;
	const int offset;
	
public:

/*
private:
	static SpanCollection _initializeSpans(const BlockCollection& _blocks, int imgwidth) {
		//empty row
		if (_blocks.size() == 0 || (_blocks.size() == 1 && _blocks[0] == 0)) {
			return { imgwidth };
		}
		//full row
		else if (_blocks.size() == 1 && _blocks[0] == imgwidth) {
			return { 0, 0 };
		}

		std::vector<int> spans(_blocks.size() + 1, 1);
		spans.front() = 0;
		return std::move(spans);
	}*/
};
