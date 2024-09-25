/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "RenderSystem.hpp"

using namespace RType;

// Constructeur
RType::RenderSystem::RenderSystem() : _window(sf::VideoMode(1920, 1080), "RType"), _isFullScreen(false) {
    // Initialisation ici
}

// Destructeur
RType::RenderSystem::~RenderSystem() {
    // Libération des ressources si nécessaire
    // _window.close(); // si vous devez fermer la fenêtre
}

Event RenderSystem::getInput()
{
    sf::Event event = {};

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return (Event::ESCAPE);
        if (event.type != sf::Event::KeyPressed)
            continue;
        switch (event.key.code) {
            case sf::Keyboard::F6:
                return (Event::MENU);
            case sf::Keyboard::Enter:
                return (Event::ENTER);
            case sf::Keyboard::Space:
                return (Event::SPACE);
            case sf::Keyboard::Up:
                return (Event::GAME_UP);
            case sf::Keyboard::Down:
                return (Event::GAME_DOWN);
            case sf::Keyboard::Left:
                return (Event::GAME_LEFT);
            case sf::Keyboard::Right:
                return (Event::GAME_RIGHT);
            case sf::Keyboard::Escape:
                return (Event::ESCAPE);
            case sf::Keyboard::Backspace:
                return (Event::BACKSPACE);
                case sf::Keyboard::F11:
                return (Event::FULLSCREEN);
            case sf::Keyboard::A:
                return (Event::IN_A);
            case sf::Keyboard::B:
                return (Event::IN_B);
            case sf::Keyboard::C:
                return (Event::IN_C);
            case sf::Keyboard::D:
                return (Event::IN_D);
            case sf::Keyboard::E:
                return (Event::IN_E);
            case sf::Keyboard::F:
                return (Event::IN_F);
            case sf::Keyboard::G:
                return (Event::IN_G);
            case sf::Keyboard::H:
                return (Event::IN_H);
            case sf::Keyboard::I:
                return (Event::IN_I);
            case sf::Keyboard::J:
                return (Event::IN_J);
            case sf::Keyboard::K:
                return (Event::IN_K);
            case sf::Keyboard::L:
                return (Event::IN_L);
            case sf::Keyboard::M:
                return (Event::IN_M);
            case sf::Keyboard::N:
                return (Event::IN_N);
            case sf::Keyboard::O:
                return (Event::IN_O);
            case sf::Keyboard::P:
                return (Event::IN_P);
            case sf::Keyboard::Q:
                return (Event::IN_Q);
            case sf::Keyboard::R:
                return (Event::IN_R);
            case sf::Keyboard::S:
                return (Event::IN_S);
            case sf::Keyboard::T:
                return (Event::IN_T);
            case sf::Keyboard::U:
                return (Event::IN_U);
            case sf::Keyboard::V:
                return (Event::IN_V);
            case sf::Keyboard::W:
                return (Event::IN_W);
            case sf::Keyboard::X:
                return (Event::IN_X);
            case sf::Keyboard::Y:
                return (Event::IN_Y);
            case sf::Keyboard::Z:
                return (Event::IN_Z);
            default:
                break;
        }
    }
    return NONE;
}

void RenderSystem::clearWindow()
{
    _window.clear(sf::Color::Black);
}

void RenderSystem::updateWindow()
{
    _window.display();
}

void RenderSystem::FullScreenWindow()
{
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();

    if (_isFullScreen) {
        // Passer en mode fenêtré
        _window.create(sf::VideoMode(1920, 1080), "RType", sf::Style::Default);
        _isFullScreen = false;
    } else {
        // Passer en mode plein écran
        _window.create(fullscreenMode, "RType", sf::Style::Fullscreen);
        _isFullScreen = true;
    }
}

void RenderSystem::drawSprite() {};

void RenderSystem::drawText() {};