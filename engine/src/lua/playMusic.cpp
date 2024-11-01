/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "luaBindings.hpp"
#include "common/components/components.hpp"

void playMusicSound(lua_State* L)
{
    std::cout << "playMusicSound" << std::endl;
    RType::GameContext* gameContext =
        static_cast<RType::GameContext*>(lua_touserdata(L, lua_upvalueindex(1)));

    const char* entity = lua_tostring(L, 1);
    const char* audioPath = lua_tostring(L, 2);

    std::cout << "entity: " << entity << std::endl;
    std::cout << "audioPath: " << audioPath << std::endl;
    try {
        gameContext->get<RType::Audio>(std::string(entity)).audioQueue.push(std::string(audioPath));
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
