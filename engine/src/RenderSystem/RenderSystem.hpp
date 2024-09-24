/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once
    #include <iostream>
    #include <memory>
    #include <IRenderSystem.hpp>
    #include <unistd.h>
    #include <SFML/Window.hpp>
    #include <SFML/Graphics.hpp>

namespace RType
{
    class RenderSystem : public RType::IRenderSystem {
        public:
            RenderSystem(): _window(sf::VideoMode(1920, 1080), "RType") {};
            ~RenderSystem();

        public:
            RType::Event getInput() override;
            void clearWindow() override;
            void updateWindow() override;
            void drawText() override;
            void drawSprite() override;
            void FullScreenWindow() override;

        private:
            sf::RenderWindow _window;
            bool _isFullScreen;
    };
}