/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "RenderSystemSFML.hpp"

namespace RType
{

RenderSystemSFML::RenderSystemSFML()
    : _window(sf::VideoMode(1920, 1080), "RType"), _isFullScreen(false)
{
}

RenderSystemSFML::~RenderSystemSFML() {}

void RenderSystemSFML::pollEvents()
{
    _previousKeys = _currentKeys;
    sf::Event event = {};
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _currentKeys[KeyCode::Close] = true;
        }
        if (event.type == sf::Event::KeyPressed)
        {
            _currentKeys[convertSFMLKeyToKeyCode(event.key.code)] = true;
        }
        if (event.type == sf::Event::KeyReleased)
        {
            _currentKeys[convertSFMLKeyToKeyCode(event.key.code)] = false;
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            _currentKeys[convertSFMLMouseToKeyCode(event.mouseButton.button)] = true;
        }
        if (event.type == sf::Event::MouseButtonReleased)
        {
            _currentKeys[convertSFMLMouseToKeyCode(event.mouseButton.button)] = false;
        }
    }
}

bool RenderSystemSFML::getKey(KeyCode key)
{
    auto it = _currentKeys.find(static_cast<int>(key));
    if (it != _currentKeys.end())
    {
        return it->second;
    }
    return false;
}

bool RenderSystemSFML::getKeyUp(KeyCode key)
{
    auto it = _previousKeys.find(static_cast<int>(key));
    if (it != _previousKeys.end())
    {
        if (it->second == true && _currentKeys[static_cast<int>(key)] == false)
        {
            return true;
        }
    }
    return false;
}

bool RenderSystemSFML::getKeyDown(KeyCode key)
{
    auto it = _currentKeys.find(static_cast<int>(key));
    if (it != _currentKeys.end())
    {
        if (it->second == true && _previousKeys[static_cast<int>(key)] == false)
        {
            return true;
        }
    }
    return false;
}

void RenderSystemSFML::clearWindow() { _window.clear(sf::Color::Black); }

void RenderSystemSFML::updateWindow() { _window.display(); }

void RenderSystemSFML::FullScreenWindow()
{
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();

    try
    {
        if (_isFullScreen)
        {
            _window.create(sf::VideoMode(1920, 1080), "RType", sf::Style::Default);
            _isFullScreen = false;
        }
        else
        {
            _window.create(fullscreenMode, "RType", sf::Style::Fullscreen);
            _isFullScreen = true;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erreur lors du changement de mode plein écran : " << e.what() << std::endl;
    }
}

bool RenderSystemSFML::loadTexture(const std::string& textureName, const std::string& filePath)
{
    try
    {
        auto texture = std::make_unique<sf::Texture>();
        if (!texture->loadFromFile(filePath))
        {
            throw std::runtime_error("Erreur lors du chargement de la texture : " + filePath);
        }
        _textures[textureName] = std::move(texture);
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return false;
    }
}

void RenderSystemSFML::unloadTexture(const std::string& textureName)
{
    auto it = _textures.find(textureName);
    if (it != _textures.end())
    {
        _textures.erase(it);
    }
}

void RenderSystemSFML::loadSprite(const std::string& filePath)
{
    try
    {
        if (!loadTexture(filePath, filePath))
        {
            throw std::runtime_error("Erreur lors du chargement du sprite : " + filePath);
        }

        auto it = _textures.find(filePath);
        if (it != _textures.end())
        {
            sf::Sprite sprite;
            sprite.setTexture(*it->second);
            _sprites[filePath] = sprite;
        }
        else
        {
            throw std::runtime_error("Erreur : texture non trouvée (" + filePath + ")");
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
}

void RenderSystemSFML::unloadSprite(const std::string& spriteName)
{
    auto it = _sprites.find(spriteName);
    if (it != _sprites.end())
    {
        _sprites.erase(it);
    }
    else
    {
        std::cerr << "Erreur : sprite non trouvé (" << spriteName << ")" << std::endl;
    }
}

void RenderSystemSFML::drawSprite(const std::string& spriteName, mlg::vec2 position,
                                  mlg::vec4 spriteCoords, mlg::vec2 scale, float rotation)
{
    auto it = _sprites.find(spriteName);
    if (it != _sprites.end())
    {
        sf::IntRect spriteRect(spriteCoords.x, spriteCoords.y, spriteCoords.z, spriteCoords.w);
        it->second.setTextureRect(spriteRect);
        it->second.setPosition(position.x, position.y);
        it->second.setScale(scale.x, scale.y);
        it->second.setRotation(rotation);
        _window.draw(it->second);
    }
    else
    {
        std::cerr << "Erreur : sprite non trouvé (" << spriteName << ")" << std::endl;
    }
}

void RenderSystemSFML::drawSprite(const std::string& spriteName, mlg::vec2 position)
{
    auto it = _sprites.find(spriteName);
    if (it != _sprites.end())
    {
        it->second.setPosition(position.x, position.y);
        _window.draw(it->second);
    }
    else
    {
        std::cerr << "Erreur : sprite non trouvé (" << spriteName << ")" << std::endl;
    }
}

void RenderSystemSFML::drawRectangle(mlg::vec4& spriteCoords, bool full, const mlg::vec3& color)
{
    sf::RectangleShape rectangle(sf::Vector2f(spriteCoords.z, spriteCoords.w));
    rectangle.setPosition(spriteCoords.x, spriteCoords.y);

    sf::Color sfcolor(static_cast<sf::Uint8>(color.x * 255), static_cast<sf::Uint8>(color.y * 255),
                      static_cast<sf::Uint8>(color.z * 255));

    if (full)
    {
        rectangle.setFillColor(sfcolor);
    }
    else
    {
        rectangle.setFillColor(sf::Color::Transparent);
        rectangle.setOutlineThickness(1);
        rectangle.setOutlineColor(sfcolor);
    }
    _window.draw(rectangle);
}

bool RenderSystemSFML::loadMusic(const std::string& musicName, const std::string& filePath)
{
    try
    {
        if (_musics.find(musicName) != _musics.end())
        {
            return true;
        }

        auto music = std::make_unique<sf::Music>();
        if (!music->openFromFile(filePath))
        {
            throw std::runtime_error("Erreur lors du chargement de la musique : " + filePath);
        }

        _musics[musicName] = std::move(music);
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return false;
    }
}

void RenderSystemSFML::drawText(const std::string& fontPath, const std::string& textStr,
                                const mlg::vec2 position, unsigned int fontSize,
                                const mlg::vec3& color)
{
    try
    {
        if (_fonts.find(fontPath) == _fonts.end())
        {
            throw std::runtime_error("Erreur : police non reconnue (" + fontPath + ")");
        }

        sf::Font& font = _fonts[fontPath];
        sf::Text text;
        text.setFont(font);
        text.setString(textStr);
        text.setCharacterSize(fontSize);
        text.setPosition(position.x, position.y);

        text.setFillColor(sf::Color(static_cast<sf::Uint8>(color.x * 255),
                                    static_cast<sf::Uint8>(color.y * 255),
                                    static_cast<sf::Uint8>(color.z * 255)));
        _window.draw(text);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
}

void RenderSystemSFML::playMusic(const std::string& musicName, bool loop)
{
    if (_currentMusic != nullptr)
    {
        _currentMusic->stop();
    }

    try
    {
        auto it = _musics.find(musicName);
        if (it != _musics.end())
        {
            _currentMusic = it->second.get();
            _currentMusic->setLoop(loop);
            _currentMusic->play();
        }
        else
        {
            throw std::runtime_error("Erreur : musique non trouvée (" + musicName + ")");
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
}

void RenderSystemSFML::stopCurrentMusic()
{
    if (_currentMusic != nullptr)
    {
        _currentMusic->stop();
        _currentMusic = nullptr;
    }
}

void RenderSystemSFML::unloadMusic(const std::string& musicName)
{
    auto it = _musics.find(musicName);
    if (it != _musics.end())
    {
        if (_currentMusic == it->second.get())
        {
            _currentMusic->stop();
            _currentMusic = nullptr;
        }
        _musics.erase(it);
    }
}

bool RenderSystemSFML::loadSound(const std::string& soundName, const std::string& filePath)
{
    try
    {
        if (_soundBuffers.find(soundName) != _soundBuffers.end())
        {
            return true;
        }

        auto buffer = std::make_unique<sf::SoundBuffer>();
        if (!buffer->loadFromFile(filePath))
        {
            throw std::runtime_error("Erreur lors du chargement du son : " + filePath);
        }

        _soundBuffers[soundName] = std::move(buffer);
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return false;
    }
}

void RenderSystemSFML::playSound(const std::string& soundName)
{
    try
    {
        auto it = _soundBuffers.find(soundName);
        if (it != _soundBuffers.end())
        {
            sf::Sound sound;
            sound.setBuffer(*it->second);
            _sounds.push_back(sound);
            _sounds.back().play();
        }
        else
        {
            throw std::runtime_error("Erreur : son non trouvé (" + soundName + ")");
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
}

void RenderSystemSFML::unloadSound(const std::string& soundName)
{
    auto it = _soundBuffers.find(soundName);
    if (it != _soundBuffers.end())
    {
        _soundBuffers.erase(it);
    }
}

KeyCode RenderSystemSFML::convertSFMLKeyToKeyCode(sf::Keyboard::Key key)
{
    switch (key)
    {
        case sf::Keyboard::A:
            return KeyCode::A;
        case sf::Keyboard::B:
            return KeyCode::B;
        case sf::Keyboard::C:
            return KeyCode::C;
        case sf::Keyboard::D:
            return KeyCode::D;
        case sf::Keyboard::E:
            return KeyCode::E;
        case sf::Keyboard::F:
            return KeyCode::F;
        case sf::Keyboard::G:
            return KeyCode::G;
        case sf::Keyboard::H:
            return KeyCode::H;
        case sf::Keyboard::I:
            return KeyCode::I;
        case sf::Keyboard::J:
            return KeyCode::J;
        case sf::Keyboard::K:
            return KeyCode::K;
        case sf::Keyboard::L:
            return KeyCode::L;
        case sf::Keyboard::M:
            return KeyCode::M;
        case sf::Keyboard::N:
            return KeyCode::N;
        case sf::Keyboard::O:
            return KeyCode::O;
        case sf::Keyboard::P:
            return KeyCode::P;
        case sf::Keyboard::Q:
            return KeyCode::Q;
        case sf::Keyboard::R:
            return KeyCode::R;
        case sf::Keyboard::S:
            return KeyCode::S;
        case sf::Keyboard::T:
            return KeyCode::T;
        case sf::Keyboard::U:
            return KeyCode::U;
        case sf::Keyboard::V:
            return KeyCode::V;
        case sf::Keyboard::W:
            return KeyCode::W;
        case sf::Keyboard::X:
            return KeyCode::X;
        case sf::Keyboard::Y:
            return KeyCode::Y;
        case sf::Keyboard::Z:
            return KeyCode::Z;
        case sf::Keyboard::Up:
            return KeyCode::UpArrow;
        case sf::Keyboard::Down:
            return KeyCode::DownArrow;
        case sf::Keyboard::Left:
            return KeyCode::LeftArrow;
        case sf::Keyboard::Right:
            return KeyCode::RightArrow;
        case sf::Keyboard::Escape:
            return KeyCode::Escape;
        case sf::Keyboard::Space:
            return KeyCode::Space;
        case sf::Keyboard::Enter:
            return KeyCode::Enter;
        case sf::Keyboard::Backspace:
            return KeyCode::Backspace;
        case sf::Keyboard::Tab:
            return KeyCode::Tab;
        case sf::Keyboard::Num0:
            return KeyCode::Alpha0;
        case sf::Keyboard::Num1:
            return KeyCode::Alpha1;
        case sf::Keyboard::Num2:
            return KeyCode::Alpha2;
        case sf::Keyboard::Num3:
            return KeyCode::Alpha3;
        case sf::Keyboard::Num4:
            return KeyCode::Alpha4;
        case sf::Keyboard::Num5:
            return KeyCode::Alpha5;
        case sf::Keyboard::Num6:
            return KeyCode::Alpha6;
        case sf::Keyboard::Num7:
            return KeyCode::Alpha7;
        case sf::Keyboard::Num8:
            return KeyCode::Alpha8;
        case sf::Keyboard::Num9:
            return KeyCode::Alpha9;
        default:
            return KeyCode::None;
    }
}

KeyCode RenderSystemSFML::convertSFMLMouseToKeyCode(sf::Mouse::Button button)
{
    switch (button)
    {
        case sf::Mouse::Left:
            return KeyCode::Mouse0;
        case sf::Mouse::Right:
            return KeyCode::Mouse2;
        case sf::Mouse::Middle:
            return KeyCode::Mouse3;
        case sf::Mouse::XButton1:
            return KeyCode::Mouse4;
        case sf::Mouse::XButton2:
            return KeyCode::Mouse5;
        default:
            return KeyCode::None;
    }
}

mlg::vec2 RenderSystemSFML::getMousePosition()
{
    sf::Vector2i position = sf::Mouse::getPosition(_window);
    return mlg::vec2(position.x, position.y, 0);
}

mlg::vec2 RenderSystemSFML::getTextureSize(const std::string& spriteName)
{
    auto it = _sprites.find(spriteName);
    if (it != _sprites.end())
    {
        auto size = it->second.getTexture()->getSize();
        return mlg::vec2(size.x, size.y, 0);
    }
    return mlg::vec2(0, 0, 0);
}

void RenderSystemSFML::setGameIcon(const std::string& filePath)
{
    try
    {
        sf::Image icon;
        if (!icon.loadFromFile(filePath))
        {
            throw std::runtime_error("Erreur lors du chargement de l'icône du jeu : " + filePath);
        }
        _window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
}

void RenderSystemSFML::loadFont(const std::string& filePath)
{
    sf::Font font;
    try
    {
        if (!font.loadFromFile(filePath))
        {
            throw std::runtime_error("Erreur lors du chargement de la police : " + filePath);
        }
        _fonts[filePath] = font;
        std::cout << "Police chargée : " << filePath << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
}

void RenderSystemSFML::setFramerateLimit(unsigned int limit) { _window.setFramerateLimit(limit); }

void RenderSystemSFML::setVerticalSyncEnabled(bool enabled)
{
    _window.setVerticalSyncEnabled(enabled);
}

}  // namespace RType
