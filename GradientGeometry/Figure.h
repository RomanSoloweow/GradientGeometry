#pragma once

class Canvas;

class Figure
{
	public:
	virtual void Draw(Canvas& canvas, bool asNewCanvas = true) = 0;
	virtual void Fill(Canvas& canvas, bool asNewCanvas = true) = 0;
};

