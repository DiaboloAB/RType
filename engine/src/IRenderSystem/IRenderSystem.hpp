/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

    #include <iostream>
    #include <memory>
    #include "../common/Event.hpp"

namespace RType
{
    class IRenderSystem {
        public:
            IRenderSystem();
            ~IRenderSystem();

        public:
            virtual RType::Event getInput() = 0;
            virtual void clearWindow() = 0;
            virtual void updateWindow() = 0;
            virtual void drawSprite() = 0;
            virtual void drawText() = 0;
            virtual void FullScreenWindow() = 0;
        private:
    };
}

