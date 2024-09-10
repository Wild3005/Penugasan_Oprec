#ifndef GAME_HPP
#define GAME_HPP
#include <opencv2/opencv.hpp>
using namespace cv;
class peluru{
    private:
    int velx;
    int vely;
    public:
    float radius;
    Point position;
    peluru(Point position, int velxy, float r){
        this-> position = position;
        velx = velxy;
        vely = velxy;
        radius = r;
    }
    void move_peluru(){
        position.x += velx;
        position.y += vely;
    }
    void koresi_layar(int cols, int rows) {
    if (position.x > rows)
        position.x = 0;
    if (position.x < 0)
        position.x = rows;
    if (position.y > cols)
        position.y = 0;
    if (position.y < 0)
        position.y = cols;
}
    void reset_peluru(Point position,int velxy, float r){
        this->position = position;
        velx = velxy;
        vely = velxy;
        radius = r;
    }

    
};
#endif