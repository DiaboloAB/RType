/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include <iostream>
#include <mlg/mlg.hpp>
#include <string>
#include <vector>

class Timer
{
   private:
    float time = 0.0f;
    bool active = false;

   public:
    Timer() {}
    ~Timer() {}

    float getTime() { return time; }
    void setTime(float time) { this->time = time; }
    void reset() { time = 0; }

    bool getState() { return active; }
    void start() { active = true; }
    void stop() { active = false; }
};