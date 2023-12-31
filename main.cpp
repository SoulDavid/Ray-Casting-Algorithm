//https://rosettacode.org/wiki/Ray-casting_algorithm

//The algorithms library defines functions for a variety of purposes (e.g. searching, sorting, counting, manipulating) that operate on ranges of elements. 
#include <algorithm>
//This header defines several general purpose functions, including dynamic memory management, random number generation, communication with the environment, integer arithmetics, searching, sorting and converting.
#include <cstdlib>
//Providing parametric manipulators
#include <iomanip>
//Defines the standard input/output stream objects
#include <iostream>
//Defines elements with the characteristics of arithmetic types.
#include <limits>

//using namespace std;
const double epsilon = std::numeric_limits<float>().epsilon();
const std::numeric_limits<double> DOUBLE;
const double MIN = DOUBLE.min();
const double MAX = DOUBLE.max();

struct Point {const double x, y; };

struct Edge {
	const Point a, b;
	
	bool operator()(const Point& p) const{
		if(a.y > b.y) return Edge{b, a}(p);
		if(p.y == a.y || p.y == b.y) return operator()({p.x, p.y + epsilon});
		if(p.y > b.y || p.y < a.y || p.x > std::max(a.x, b.x)) return false;
		if(p.x < std::min(a.x, b.x)) return true;
		
		auto blue = abs(a.x - p.x) > MIN ? (p.y - a.y) / (p.x - a.x) : MAX;
		auto red = abs(a.x - b.x) > MIN ? (b.y - a.y) / (b.x - a.x) : MAX;
		return blue >= red;
	}
};

struct Figure {
	const std::string name;
	const std::initializer_list<Edge> edges;
	
	bool contains(const Point& p) const {
		auto c = 0;
		for (auto e : edges) if (e(p)) c++;
		return c % 2 != 0;
	}
	
	template<unsigned char W = 3>
	void check(const std::initializer_list<Point>& points, std::ostream& os) const{
		os << "Is Point Inside Figure" << name << '?' << std::endl;
		for (auto p : points)
			//setW -> Modifies the field width for the next input or output only. Defaults to 0, but expands as needed.
			os << " (" << std::setw(W) << p.x << ',' << std::setw(W) << p.y << "): " << std::boolalpha << contains(p) << std::endl;
	}
};

int main()
{
	const std::initializer_list<Point> points = {{ 5.0, 5.0}, {5.0, 8.0}, {-10.0, 5.0}, {0.0, 5.0}, {10.0, 5.0}, {8.0, 5.0}, {10.0, 10.0}	};
	const Figure square = { "Square", 
		{  
{{0.0, 0.0}, {10.0, 0.0}}, {{10.0, 0.0}, {10.0, 10.0}}, {{10.0, 10.0}, {0.0, 10.0}}, {{0.0, 10.0}, {0.0, 0.0}}			}	};
	
	const Figure square_hole = { "Square_hole", 
		{  {{0.0, 0.0}, {10.0, 0.0}}, {{10.0, 0.0}, {10.0, 10.0}}, {{10.0, 10.0}, {0.0, 10.0}}, {{0.0, 10.0}, {0.0, 0.0}}, {{2.5, 2.5}, {7.5, 2.5}}, {{7.5, 2.5}, {7.5, 7.5}}, {{7.5, 7.5}, {2.5, 7.5}}, {{2.5, 7.5}, {2.5, 2.5}}
    	}	};
        
    const Figure strange = {"Strange",         
    	{  {{0.0, 0.0}, {2.5, 2.5}}, {{2.5, 2.5}, {0.0, 10.0}}, {{0.0, 10.0}, {2.5, 7.5}}, {{2.5, 7.5}, {7.5, 7.5}}, {{7.5, 7.5}, {10.0, 10.0}}, {{10.0, 10.0}, {10.0, 0.0}}, {{10.0, 0}, {2.5, 2.5}}
        }	};
        
    const Figure exagon = {"Exagon",         
    	{  {{3.0, 0.0}, {7.0, 0.0}}, {{7.0, 0.0}, {10.0, 5.0}}, {{10.0, 5.0}, {7.0, 10.0}}, {{7.0, 10.0}, {3.0, 10.0}}, {{3.0, 10.0}, {0.0, 5.0}}, {{0.0, 5.0}, {3.0, 0.0}}
        }	};
        
        for(auto f : {square, square_hole, strange, exagon})
        	f.check(points, std::cout);
        	
        return EXIT_SUCCESS;
}