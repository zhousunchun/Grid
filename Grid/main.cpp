#include <iostream>
#include <memory>
#include <math.h>
#include <memory.h>
#include <vector> 
#include <cstdlib>

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
        return out;
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
        if(0 == _height || 0 == _width)
            _pData = NULL;
        else
        {
            _pData = new int[_width*_height]();
        }
    }
    
    ~Grid()
    {
        if(_pData == NULL)
            return ;
        else
        {
            delete[] _pData;
        }
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
//     int pDataIndexCalc(const int & xIndex, const int & yIndex)
//     {
//         Point<int> point(xIndex,yIndex);
//         int incrementNumberLimits = 5;
//         int incrementNumber = 0;
//         while(!isInBoundary(point))
//         {
//             extendGrid();
//             if(incrementNumber >incrementNumberLimits) break;
//             ++incrementNumber;
//         }
//         int pDataXIndexStart = _point.getX() - _width/2;
//         int pDataYIndexStart = _point.getY() - _height/2;
//         
//         int index = (yIndex - pDataYIndexStart) * _width + (xIndex - pDataXIndexStart);
//         return index;
//     }
//     
//     void setGridValueByIndex(const int & index)
//     {
//         
//         int col = index %_width;
//         int row = index /_width;
//         
//         _pData[row][col] = 1;
//     }
    /* Convert physical point into grid coordinate, and change corresponding grid' values */ 
    void setGridValue(const double &xMeter, const double & yMeter)
    {
        
        int index = worldToGrid(xMeter,yMeter);
        std::cout<<"index"<< index<<std::endl;
        *(_pData + index) = 1;
    }
   
    /* Obtain corresponding grid value */
    int getGridValue(const double &xMeter, const double& yMeter)
    {
        int index  = worldToGrid(xMeter,yMeter);
        return *(_pData+index);
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
    
    int*  getGridData()
    {
        return _pData;
    }
    
    friend std::ostream & operator << (std::ostream &out, const Grid& grid)
    {
        int * pData = grid._pData;
        for(int i=0; i<grid._height;++i)
        {
            for (int j=0; j<grid._width; ++j)
            {
                out << *(pData+i*grid._width+j) << " ";
            }
            out<< std::endl;
        }
        out<<std::endl;
        return out;
    }

    bool isInBoundary(Point<T> & p)
    {
        return (p.getX() <= _point.getX() + _width/2 && p.getX() >= _point.getX() - _width/2);
    }

    void extendGrid()
    {
        delete[] _pData;
        _width = 2*_width +1;
        _height = 2*_height+1;
        _pData = new int[_width*_height]();
    }
    
    void bresenhamLine(Point<int> & p1, Point<int> & p2,  std::vector<Point<int> > & points)
    {
        int x1 = p1.getX();
        int y1 = p1.getY();
        int x2 = p2.getX();
        int y2 = p2.getY();
        points.clear();
        
        bool steep = abs(y2-y1) > abs(x2-x1);
        if(steep)
        {
            std::swap(x1,y1);
            std::swap(x2,y2);
        }
        if(x1 > x2)
        {
            std::swap(x1,x2);
            std::swap(y1,y2);
        }
        
        int deltaX = x2-x1;
        int deltaY = abs(y2-y1);
        int error = 0;
        int ystep;
        int y = y1;
        
        if(y1<y2)
        {
            ystep = 1;
        }
        else{
            ystep = -1;
        }
        
        int pointX;
        int pointY;
        
        for(int x = x1; x< x2; ++x)
        {
            if(steep)
            {
                pointX = y;
                pointY = x;
            }
            else
            {
                pointX = x;
                pointY = y;
            }
            
            error += deltaY;
            if(2*error >= deltaX)
            {
                y+= ystep;
                error -= deltaX;
            }
            points.push_back(Point<int>(pointX,pointY));
        }
    }
    
    void updateMap(std::vector<Point<int> > points)
    {
        std::vector<Point<int> >::iterator it;
        for (it = points.begin(); it!=points.end(); ++it)
        {
            std::cout<< *it<<std::endl;
            std::cout<< "isInBoundary" << isInBoundary(*it) << std::endl;
            while(!isInBoundary(*it))
            {
                extendGrid();
            }
//             int index = pDataIndexCalc(it->getX(), it->getY());
//             setGridValueByIndex(index);
            setGridValue(it->getX(),it->getY());
        }
    }
    
private:
    
private:
    /* class data memeber */ 
    Point<T> _point;
    int _width;
    int _height;
    int _resolution;
//     T** _pData;
    int* _pData;
};

int main(int argc, char **argv) 
{
//     std::cout<<"Class Point Tests"<<std::endl;
//     Point<int> p1(2,2); // constructor function 1
//     Point<int> p2(p1); // constructor function 2
//     std::cout<< p1<< std::endl; //  overload operator <<  and insert point into stream
//     std::cout << p2 << std::endl; 
//     std::cout<<p1+p2<<std::endl; // overload operator +, and return the result of two point 
//     std::cout<<p1-p2 <<std::endl; // overload opeartor - 
//     std::cout<< p2.getX() << " " << p2.getY() <<  std::endl;  // test the getter function of Point class
//     
//     std::cout << std::endl;
//     std::cout << "Class Grid Tests" << std::endl;
    
    Grid<int> grid(Point<int>(0,0),11,11,1); //constructor function
//     std::cout << grid <<std::endl;
//     std::cout<< grid.getPoint() << std::endl; // test the getter function of Grid Class
//     std::cout << grid.getHeight() << std::endl;
//     std::cout << grid.getWidth() << std::endl;
//     std::cout << grid.getResolution() << std::endl;
//     Point<double> p(1,0);
//     grid.setGridValue(p.getX(),p.getY()); // change the value in the grid

//    std::cout<<grid<<std::endl; // overload opeator << to print the grid
//    std::cout << grid.getGridValue(p.getX(), p.getY()) << std::endl; // test getter fucntion of the Grid Class
//    Point<int> p3(-2,-2);
//    std::cout << grid.isInBoundary(p3);
//     grid.extendGrid();
//     std::cout<< grid.getPoint() << std::endl; // test the getter function of Grid Class
//     std::cout << grid.getHeight() << std::endl;
//     std::cout << grid.getWidth() << std::endl;
//     std::cout << grid.getResolution() << std::endl;
//     grid.setGridValue(p.getX(),p.getY());
//     std::cout<<grid<<std::endl;
//     Point<int> point(2,-3);
//     std::cout << grid.worldToGrid(point.getX(),point.getY())<< std::endl;
//     grid.setGridValue(point.getX(), point.getY());
//     std::cout<<grid.getGridValue(point.getX(),point.getY()) << std::endl;
    Point<int> pointStart(0,0), pointEnd(6,-6);
    std::vector<Point<int> > points;
    grid.bresenhamLine(pointStart,pointEnd, points);
    grid.updateMap(points);
    std::cout<<grid<<std::endl;
    return 0;
}
