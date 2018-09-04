#include <iostream>
#include <memory>
#include <math.h>

/*
 * Point class
 */
template<typename T>
class Point
{
public:
    /* Constructor function */
    Point(): _x(0),_y(0){}
    Point (T x, T y): _x(x), _y(y){}
    Point(const Point & rPoint): _x(rPoint._x), _y(rPoint._y){}
public:
    /* Overload operator */
    const Point operator + (const Point & p1) const
    {
        Point temp(p1._x + _x, p1._y + _y);
        return temp;
    }
    
    const Point operator - (const Point &p1) const 
    {
        return Point(p1._x-_x, p1._y - _y);
    }
    
    friend std::ostream & operator << (std::ostream & out, const Point & p)
    {
        out<< "[" << p._x << "," << p._y << "]";
    }
    
public:
    /* Getter and Setter */
    T getX()
    {
        return _x;
    }
    T getY()
    {
        return _y;
    }
    
private:
    /* class data member */
    T _x;
    T _y;
};

/* Grid class */
template <typename T>
class Grid
{
public:
    /* Constructor function */
    Grid (): _point(0,0),_width(0),_height(0),_resolution(0),_pData(NULL) {}
    Grid(const Point<T> &p, int width, int height, int resolution) : _point(p), _width(width), _height(height), _resolution(resolution)
    { 
        // allocate map data 
        _pData = new T*[_height];
        for(int i=0; i< height; ++i)
            _pData[i] =  new T[_width];
    }
    
    
    ~Grid()
    {
        // delete pData in Destructor
        for(int i =0 ; i < _height; ++i) 
            delete[] _pData[i];
        delete[] _pData;
    }
    
public:
    /* Convert point of physical coordinate into grid index */ 
    int worldToGrid(const double& xMeter, const double& yMeter)
    {
        int xIndex = int(xMeter /_resolution);
        int yIndex = int(-yMeter /_resolution);
        int pDataXIndexStart = _point.getX() - _width/2;
        int pDataYIndexStart = _point.getY() - _height/2;
        
        int index = (yIndex - pDataYIndexStart)*_width + (xIndex - pDataXIndexStart);
        return index;
    }
    
    /* Convert physical point into grid coordinate, and change corresponding grid' values */ 
    void setGridValue(const double &xMeter, const double & yMeter)
    {
        int index = worldToGrid(xMeter,yMeter);
        int col = index % _width;
        int row = index / _width;
        _pData[row][col]  = 1;
    }
   
    /* Obtain corresponding grid value */
    int getGridValue(const double &xMeter, const double& yMeter)
    {
        int index  = worldToGrid(xMeter,yMeter);
        return _pData[index/_width][index%_width];
    }
    
    
public:
    /* Setter and Getter */
    Point<T> getPoint()
    {
        return _point;
    }
    
    int getWidth()
    {
        return _width;
    }
    
    int getHeight()
    {
        return _height;
    }
    
    int getResolution()
    {
        return _resolution;
    }
    
    /* print Grid in the console */
    void printGrid()
    {
        for(int i=0; i<_height; ++i)
        {
            for(int j = 0; j<_width; ++j)
            {
                std::cout<< _pData[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout<<std::endl;
    }
    
private:
    
private:
    /* class data memeber */ 
    Point<T> _point;
    int _width;
    int _height;
    int _resolution;
    T** _pData;
};

int main(int argc, char **argv) {
    /* Point test
    Point<int> p1(2,2);
    Point<int> p2(p1);
    std::cout<< p1<< std::endl;
    std::cout << p2 << std::endl;
    std::cout<<p1+p2<<std::endl;
    std::cout<<p1-p2 <<std::endl;
    std::cout<< p2.getX() << " " << p2.getY() <<  std::endl;
    */
    Grid<int> grid(Point<int>(0,0),5,5,20);
    /*
    std::cout<< grid.getPoint() << std::endl;
    std::cout << grid.getHeight() << std::endl;
    std::cout << grid.getWidth() << std::endl; 
    std::cout << grid.getResolution() << std::endl;
    */
   Point<double> p(-10,-40);
    grid.setGridValue(p.getX(),p.getY());
    
    
    grid.printGrid();
    std::cout << grid.getGridValue(p.getX(), p.getY()) << std::endl;
    return 0;
}
