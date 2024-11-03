/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ADMINCOMPONENTS_H
#define ADMINCOMPONENTS_H

namespace RType
{

struct Metrics
{
    std::string fontPath = "fonts/Roboto-Medium.ttf";
    int fontSize = 20;
    int font_id = -1;
    bool fps = true;
    bool gpu = true;
    bool cpu = true;
    bool ram = true;
    bool temp = true;

    bool display = false;

    Metrics() {}
    static constexpr const char* name = "Metrics";
};

struct Console
{
    std::string fontPath = "fonts/Roboto-Medium.ttf";
    int fontSize = 20;
    int font_id = -1;

    bool display = false;
    std::string input = "";
    std::vector<std::string> history;
    Console() {}
    static constexpr const char* name = "Console";
};

}  // namespace RType

#endif // ADMINCOMPONENTS_H