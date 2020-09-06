[![](https://img.shields.io/github/stars/RomanSoloweow/GradientGeometry)](https://github.com/RomanSoloweow/GradientGeometry) [![](https://img.shields.io/github/license/RomanSoloweow/GradientGeometry)](https://github.com/RomanSoloweow/GradientGeometry) [![](https://img.shields.io/github/languages/code-size/RomanSoloweow/GradientGeometry)](https://github.com/RomanSoloweow/GradientGeometry) 
 [![]( https://img.shields.io/github/last-commit/RomanSoloweow/GradientGeometry)](https://github.com/RomanSoloweow/GradientGeometry) 
# GradientGeometry
It's crazy project for drawing figures in console. For drawing used Bresenham's algorithms.

## Features
### Figures
- [Triangle](#Triangle)
- [Circle](#Circle)
- [Box](#Box)
- [Line](#Line)

## Examples
### Triangle
 ```C++
Canvas canvas;
Triangle Triangle(1500, 100, 100, 1900, 2900, 1900);
canvas.FillFigure(Triangle);
```
![](https://github.com/RomanSoloweow/GradientGeometry/blob/gh-pages/Images/FillTriangle.jpg)

### Circle
 ```C++
Canvas canvas;
Circle Circle(1500, 1000, 900);
canvas.FillFigure(Circle);
```
![](https://github.com/RomanSoloweow/GradientGeometry/blob/gh-pages/Images/FillCircle.jpg)

### Box
 ```C++
Canvas canvas;
Box Box(100, 100, 2900, 1900);
canvas.FillFigure(Box);
```
![](https://github.com/RomanSoloweow/GradientGeometry/blob/gh-pages/Images/FillBox.jpg)

### Line
 ```C++
Canvas canvas;
Line Line1(100, 100, 2900, 1900);
Line Line2(2900, 100, 100, 1900);
canvas.DrawFigure(Line1);
canvas.DrawFigure(Line2);
```
![](https://github.com/RomanSoloweow/GradientGeometry/blob/gh-pages/Images/Lines.jpg)

## License📑

Copyright (c) SimpleStateMachine

Licensed under the [MIT](LICENSE) license.

