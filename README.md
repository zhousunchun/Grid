# Grid
# Class data in Grid
### 1. Coordinate from left top: point p(x,y);
### 2. Height and width of grid: int height, width;
### 3. Step of grid: int step;
### 4. Data value in the grid: int * data;

```c++
template <tyname T>
class Grid
{
public:
  Grid();
  Grid(const & Grid);
  Grid(int x, int y, int height, int width, int step);
  init(); // allocate pData;
  ~Grid(); // release the pData;
public:
  void linePointsBetweenPoints(const Point & p1, const Point & p2, const vector<Point> & points);
  void areaAroundPoint(const Point & center, const int xOffset, const int yOffset, const vector<Point> points);
public:
  void worldToGrid(const int xMeter, const int yMeter, int resolution, const int & xIndex, const int &yIndex);
  void gridToWorld(const int xIndex, const int yIndex, int resolution, const int & xMeter, const int & yMeter);
public:
  int getPointValue(const Point & point);
  void setPointValue(const Point & point, int value);
  int getPointsValue（const vector<Point> & points);
  void setPointsValue(const vector<Point> & points, int value);
public:
  void updateMap(const vector<Point> & points);
public:
  bool isInBoundary(const Point & p);
  void mapIncrement();
  void resizeMap(const int newHeight, const int newWidth); // add grid size ??? way: change data structor? 
public:
  int getMaxXRange(); ??
  int getMinXRange(); ??
  int getMaxYRange(); ??
  int getMinYRange(); ??
private:
  int x,y;
  int height, width;
  int step;
  T* pData;
};
```
# Class functions
### 1. Constructor function;
