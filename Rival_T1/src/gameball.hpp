#ifndef GAMEBALL_HPP
#define GAMEBALL_HPP

#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;

class Ball {
public:
    Point position;      
    Vec2f velocity;      
    int radius;          
    bool visible;        

    Ball(Point startPosition, Vec2f startVelocity, int r);
    void updatePosition();
    void reset(Point newPosition, Vec2f newVelocity);
};

class Game {
private:
    VideoCapture cap;   
    Ball ball;          
    int score;          
    bool topWall, bottomWall, leftWall, rightWall; 

public:
    Game();
    void resetBall();
    void run();

private:
    void processFrame(Mat& frame);
    void checkCollision(const Mat& redMask, const Mat& frame);
    void handleWallCollisions(const Mat& frame);
};

#endif 
