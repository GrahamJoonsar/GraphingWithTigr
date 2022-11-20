#include "tigr.h"

#include <vector>
#include <cmath>
#include <iostream>

class Graph{
    private:
    std::vector<float> y_values;
    TPixel color;

    int miny = 0;
    int maxy = 0;

    void generateBounds(){
        miny = y_values[0];
        maxy = y_values[0];

        for (auto y : y_values){
            if (y < miny){
                miny = y;
            }
            if (y > maxy){
                maxy = y;
            }
        }
    }

    public:
    Graph(std::vector<float> _y, TPixel _color){
        y_values = _y;
        color = _color;
    }

    Tigr * createGraph(int width, int height){
        Tigr * graph_img = tigrBitmap(width, height);
        tigrClear(graph_img, tigrRGB(255, 255, 255));
        generateBounds();
        float delta_x = width/((float)y_values.size());
        float pasty = height - ((y_values[0]-miny)/((float)maxy-miny))*height;

        for (int i = 1; i < y_values.size(); i++){
            tigrLine(graph_img, delta_x*(i-1), pasty, delta_x*i, height - (y_values[i]-miny)/((float)maxy-miny)*height, color);
            pasty = height - (y_values[i]-miny)/((float)maxy-miny)*height;
        }

        return graph_img;
    }
};

int main(void){
    int width = 500;
    int height = 500;
    Tigr * screen = tigrWindow(width, height, "Graph", 0);

    std::vector<float> y_values;
    for (float i = -10; i <= 10; i += 1){
        y_values.push_back(i*i*i);
    }

    Graph g(y_values, tigrRGB(0, 0, 0));

    Tigr * graph = g.createGraph(500, 500);

    while(!tigrClosed(screen)){
        tigrClear(screen, tigrRGB(255, 255, 255));

        tigrBlit(screen, graph, 0, 0, 0, 0, 500, 500);

        tigrUpdate(screen);
    }

    tigrFree(screen);

    return 0;
}