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
    : _window(sf::VideoMode(1920, 1080), "RType"), _isFullScreen(false), _nextSpriteId(1)
{
    _activeShader = nullptr;
}

RenderSystemSFML::~RenderSystemSFML() {}

void RenderSystemSFML::pollEvents()
{
    sf::Event event = {};
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _window.close();
        }
    }
}

bool RenderSystemSFML::getKey(KeyCode key)
{
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
}

bool RenderSystemSFML::getKeyUp(KeyCode key) { return false; }

bool RenderSystemSFML::getKeyDown(KeyCode key) { return false; }

void RenderSystemSFML::clearWindow()
{
    _window.clear(sf::Color::Black);
}

void RenderSystemSFML::updateWindow()
{
    _window.display();
}

std::shared_ptr<sf::Texture> RenderSystemSFML::loadTexture(const std::string& filePath)
{
    if (_textures.find(filePath) != _textures.end())
    {
        return _textures[filePath];
    }
    auto texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(filePath))
    {
        std::cerr << "Erreur lors du chargement de la texture : " << filePath << std::endl;
        return nullptr;
    }
    _textures[filePath] = texture;
    return texture;
}

int RenderSystemSFML::loadSprite(const std::string& filePath)
{
    auto texture = loadTexture(filePath);
    if (!texture)
    {
        return -1;
    }
    auto sprite = std::make_shared<sf::Sprite>();
    sprite->setTexture(*texture);
    int spriteId = _nextSpriteId++;
    _spriteCache[spriteId] = sprite;

    return spriteId;
}

void RenderSystemSFML::unloadSprite(int spriteId)
{
    if (_spriteCache.find(spriteId) != _spriteCache.end())
    {
        _spriteCache.erase(spriteId);
    }
    else
    {
        std::cerr << "Erreur : sprite avec l'ID " << spriteId << " non trouvé." << std::endl;
    }
}

void RenderSystemSFML::drawSprite(int spriteId, mlg::vec3 position, mlg::vec4 spriteCoords,
                                  mlg::vec3 scale, float rotation)
{
    auto it = _spriteCache.find(spriteId);
    if (it != _spriteCache.end())
    {
        sf::IntRect spriteRect(spriteCoords.x, spriteCoords.y, spriteCoords.z, spriteCoords.w);
        it->second->setTextureRect(spriteRect);

        it->second->setPosition(position.x, position.y);
        it->second->setScale(scale.x, scale.y);
        it->second->setRotation(rotation);
        if (_activeShader)
        {
            _window.draw(*it->second, _activeShader);
        }
        else
        {
            _window.draw(*it->second);
        }
    }
    else
    {
        std::cerr << "Erreur : sprite avec l'ID " << spriteId << " non trouvé." << std::endl;
    }
}

void RenderSystemSFML::drawSprite(int spriteId, mlg::vec3 position)
{
    auto it = _spriteCache.find(spriteId);
    if (it != _spriteCache.end())
    {
        it->second->setPosition(position.x, position.y);
        if (_activeShader)
        {
            _window.draw(*it->second, _activeShader);
        }
        else
        {
            _window.draw(*it->second);
        }
    }
    else
    {
        std::cerr << "Erreur : sprite avec l'ID " << spriteId << " non trouvé." << std::endl;
    }
}

mlg::vec3 RenderSystemSFML::getTextureSize(int spriteId)
{
    auto it = _spriteCache.find(spriteId);
    if (it != _spriteCache.end())
    {
        sf::Vector2u size = it->second->getTexture()->getSize();
        return mlg::vec3(size.x, size.y, 0);
    }
    return mlg::vec3(0, 0, 0);
}

mlg::vec3 RenderSystemSFML::getMousePosition()
{
    sf::Vector2i position = sf::Mouse::getPosition(_window);
    return mlg::vec3(position.x, position.y, 0);
}

void RenderSystemSFML::setGameIcon(const std::string& filePath)
{
    sf::Image icon;
    if (!icon.loadFromFile(filePath))
    {
        std::cerr << "Erreur lors du chargement de l'icône du jeu : " << filePath << std::endl;
        return;
    }
    _window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void RenderSystemSFML::drawText(const std::string& fontPath, const std::string& textStr,
                                const mlg::vec3 position, unsigned int fontSize,
                                const mlg::vec3& color, bool centered)
{
    sf::Font font;
    if (!font.loadFromFile(fontPath))
    {
        std::cerr << "Erreur lors du chargement de la police : " << fontPath << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(textStr);
    text.setCharacterSize(fontSize);
    text.setPosition(position.x, position.y);

    sf::Color sfColor(color.x, color.y, color.z);
    text.setFillColor(sfColor);

    if (centered)
    {
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f,
                       textRect.top + textRect.height / 2.0f);
    }

    _window.draw(text);
}

void RenderSystemSFML::drawRectangle(mlg::vec4& spriteCoords, bool full, const mlg::vec3& color)
{
    sf::RectangleShape rectangle(sf::Vector2f(spriteCoords.z, spriteCoords.w));
    rectangle.setPosition(spriteCoords.x, spriteCoords.y);

    sf::Color sfcolor(color.x, color.y, color.z);
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

void RenderSystemSFML::FullScreenWindow()
{
    if (_isFullScreen)
    {
        _window.create(sf::VideoMode(1920, 1080), "RType", sf::Style::Default);
        _isFullScreen = false;
    }
    else
    {
        _window.create(sf::VideoMode::getDesktopMode(), "RType", sf::Style::Fullscreen);
        _isFullScreen = true;
    }
}

bool RenderSystemSFML::loadMusic(const std::string& filePath)
{
    auto music = std::make_unique<sf::Music>();
    if (!music->openFromFile(filePath))
    {
        std::cerr << "Erreur lors du chargement de la musique : " << filePath << std::endl;
        return false;
    }
    _musics[filePath] = std::move(music);
    return true;
}

void RenderSystemSFML::playMusic(const std::string& filePath, bool loop)
{
    auto it = _musics.find(filePath);
    if (it != _musics.end())
    {
        _currentMusic = it->second.get();
        _currentMusic->setLoop(loop);
        _currentMusic->play();
    }
    else
    {
        std::cerr << "Erreur : musique non trouvée (" << filePath << ")" << std::endl;
    }
}

void RenderSystemSFML::stopCurrentMusic()
{
    if (_currentMusic)
    {
        _currentMusic->stop();
        _currentMusic = nullptr;
    }
}

void RenderSystemSFML::unloadMusic(const std::string& musicName) { _musics.erase(musicName); }

int RenderSystemSFML::loadSound(const std::string& filePath)
{
    int soundId = _nextSoundId++;

    auto soundBuffer = std::make_shared<sf::SoundBuffer>();
    if (!soundBuffer->loadFromFile(filePath))
    {
        std::cerr << "Erreur : impossible de charger le son depuis " << filePath << std::endl;
        return -1;
    }

    _soundCache[soundId] = soundBuffer;

    return soundId;
}

void RenderSystemSFML::updateSounds()
{
    _activeSounds.erase(std::remove_if(_activeSounds.begin(), _activeSounds.end(),
                                       [](const sf::Sound& sound)
                                       { return sound.getStatus() == sf::Sound::Stopped; }),
                        _activeSounds.end());
}

void RenderSystemSFML::playSound(int soundId)
{
    auto it = _soundCache.find(soundId);
    if (it != _soundCache.end())
    {
        _activeSounds.emplace_back();
        sf::Sound& sound = _activeSounds.back();
        sound.setBuffer(*it->second);
        sound.play();
    }
    else
    {
        std::cerr << "Erreur : son avec l'ID " << soundId << " non trouvé." << std::endl;
    }
}

void RenderSystemSFML::unloadSound(int soundId) { _soundCache.erase(soundId); }

void RenderSystemSFML::loadFont(const std::string& filePath)
{
    sf::Font font;
    if (!font.loadFromFile(filePath))
    {
        std::cerr << "Erreur lors du chargement de la police : " << filePath << std::endl;
        return;
    }
    _fonts[filePath] = font;
}

void RenderSystemSFML::setFramerateLimit(unsigned int limit) { _window.setFramerateLimit(limit); }

void RenderSystemSFML::setVerticalSyncEnabled(bool enabled)
{
    _window.setVerticalSyncEnabled(enabled);
}

int RenderSystemSFML::loadShader(const std::string& vertexShaderPath,
                                 const std::string& fragmentShaderPath)
{
    int shaderId = _nextShaderId++;

    auto shader = std::make_shared<sf::Shader>();
    if (!shader->loadFromFile(vertexShaderPath, fragmentShaderPath))
    {
        std::cerr << "Erreur : impossible de charger le shader depuis " << vertexShaderPath
                  << " et " << fragmentShaderPath << std::endl;
        return -1;
    }

    _shaderCache[shaderId] = shader;

    return shaderId;
}

void RenderSystemSFML::setShader(int shaderId)
{
    auto it = _shaderCache.find(shaderId);
    if (it != _shaderCache.end())
    {
        _activeShader = it->second.get();
    }
    else
    {
        std::cerr << "Erreur : shader avec l'ID " << shaderId << " non trouvé." << std::endl;
    }
}

void RenderSystemSFML::resetShader() { _activeShader = nullptr; }

}  // namespace RType
