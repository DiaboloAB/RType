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
    : _window(sf::VideoMode(1920, 1080), "RType"),
      _isFullScreen(false),
      _nextSpriteId(1),
      _nextFontId(1),
      _nextMusicId(1),
      _nextSoundId(1)
{
    _activeShader = nullptr;
}

RenderSystemSFML::~RenderSystemSFML() {}

void RenderSystemSFML::pollEvents()
{
    _previousKeys = _currentKeys;
    sf::Event event = {};
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) _currentKeys[KeyCode::Close] = true;
        if (event.type == sf::Event::KeyPressed)
            _currentKeys[convertSFMLKeyToKeyCode(event.key.code)] = true;
        if (event.type == sf::Event::KeyReleased)
            _currentKeys[convertSFMLKeyToKeyCode(event.key.code)] = false;
        if (event.type == sf::Event::MouseButtonPressed)
            _currentKeys[convertSFMLMouseToKeyCode(event.mouseButton.button)] = true;
        if (event.type == sf::Event::MouseButtonReleased)
            _currentKeys[convertSFMLMouseToKeyCode(event.mouseButton.button)] = false;
    }
}

bool RenderSystemSFML::getKey(KeyCode key)
{
    if (key < 0 || key >= _currentKeys.size()) return false;
    return _currentKeys[key];
}

bool RenderSystemSFML::getKeyUp(KeyCode key)
{
    if (key < 0 || key >= _currentKeys.size()) return false;
    return _currentKeys[key] == false && _previousKeys[key] == true;
}

bool RenderSystemSFML::getKeyDown(KeyCode key)
{
    if (key < 0 || key >= _currentKeys.size()) return false;
    return _currentKeys[key] == true && _previousKeys[key] == false;
}

void RenderSystemSFML::clearWindow() { _window.clear(sf::Color::Black); }

void RenderSystemSFML::updateWindow() { _window.display(); }

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
    auto it = _spriteCache.find(spriteId);
    if (it != _spriteCache.end())
    {
        if (it->second.use_count() == 1)
        {
            _spriteCache.erase(it);
        }
        else
        {
            std::cerr << "Erreur : le sprite avec l'ID " << spriteId
                      << " est encore utilisé ailleurs." << std::endl;
        }
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

        // Calculer la taille réelle du sprite après application de l'échelle
        float realWidth = spriteCoords.z * scale.x;
        float realHeight = spriteCoords.w * scale.y;

        // Calculer la position pour que le centre soit le point d'origine
        float centerX = position.x - (realWidth / 2.0f);
        float centerY = position.y - (realHeight / 2.0f);

        // Définir la position ajustée pour que le centre soit constant
        it->second->setPosition(centerX, centerY);

        // Appliquer l'échelle et la rotation
        it->second->setScale(scale.x, scale.y);
        it->second->setRotation(rotation);

        // Dessiner le sprite
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

void RenderSystemSFML::drawText(int fontID, const std::string& textStr, const mlg::vec3 position,
                                unsigned int fontSize, const mlg::vec3& color, bool centered)
{
    auto it = _fonts.find(fontID);
    if (it == _fonts.end())
    {
        std::cerr << "Erreur : police non trouvée (ID: " << fontID << ")" << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(*it->second);
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

int RenderSystemSFML::loadMusic(const std::string& filePath)
{
    for (const auto& [id, cachedMusic] : _musics)
    {
        if (cachedMusic->openFromFile(filePath))
        {
            return id;
        }
    }

    int musicId = _nextMusicId++;

    auto music = std::make_unique<sf::Music>();
    if (!music->openFromFile(filePath))
    {
        std::cerr << "Erreur lors du chargement de la musique : " << filePath << std::endl;
        return -1;
    }

    _musics[musicId] = std::move(music);

    return musicId;
}

void RenderSystemSFML::playMusic(int musicID, bool loop)
{
    auto it = _musics.find(musicID);
    if (it != _musics.end())
    {
        _currentMusic = it->second.get();
        _currentMusic->setLoop(loop);
        _currentMusic->play();
    }
    else
    {
        std::cerr << "Erreur : musique non trouvée (ID: " << musicID << ")" << std::endl;
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

void RenderSystemSFML::unloadMusic(int musicID)
{
    auto it = _musics.find(musicID);
    if (it != _musics.end())
    {
        if (it->second.use_count() == 1)
        {
            _musics.erase(it);
        }
        else
        {
            std::cerr << "Erreur : la musique avec l'ID " << musicID
                      << " est encore utilisée ailleurs." << std::endl;
        }
    }
    else
    {
        std::cerr << "Erreur : musique non trouvée pour déchargement (ID: " << musicID << ")"
                  << std::endl;
    }
}

int RenderSystemSFML::loadSound(const std::string& filePath)
{
    for (const auto& [id, buffer] : _soundCache)
    {
        if (buffer->loadFromFile(filePath))
        {
            return id;
        }
    }

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

void RenderSystemSFML::unloadSound(int soundId)
{
    auto it = _soundCache.find(soundId);
    if (it != _soundCache.end())
    {
        if (it->second.use_count() == 1)
        {
            _soundCache.erase(it);
        }
        else
        {
            std::cerr << "Erreur : le son avec l'ID " << soundId << " est encore utilisé ailleurs."
                      << std::endl;
        }
    }
    else
    {
        std::cerr << "Erreur : son avec l'ID " << soundId << " non trouvé." << std::endl;
    }
}

int RenderSystemSFML::loadFont(const std::string& filePath)
{
    for (const auto& [id, buffer] : _fonts)
    {
        if (buffer->loadFromFile(filePath))
        {
            return id;
        }
    }

    int fontId = _nextFontId++;
    auto font = std::make_shared<sf::Font>();
    if (!font->loadFromFile(filePath))
    {
        std::cerr << "Erreur : impossible de charger la police depuis " << filePath << std::endl;
        return -1;
    }

    _fonts[fontId] = font;

    return fontId;
}
void RenderSystemSFML::setFramerateLimit(unsigned int limit) { _window.setFramerateLimit(limit); }

void RenderSystemSFML::setVerticalSyncEnabled(bool enabled)
{
    _window.setVerticalSyncEnabled(enabled);
}

int RenderSystemSFML::loadShader(const std::string& vertexShaderPath,
                                 const std::string& fragmentShaderPath)
{
    for (const auto& [id, cachedShader] : _shaderCache)
    {
        if (cachedShader->loadFromFile(vertexShaderPath, fragmentShaderPath))
        {
            return id;
        }
    }

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

void RenderSystemSFML::unloadShader(int shaderId)
{
    auto it = _shaderCache.find(shaderId);
    if (it != _shaderCache.end())
    {
        if (it->second.use_count() == 1)
        {
            _shaderCache.erase(it);
        }
        else
        {
            std::cerr << "Erreur : le shader avec l'ID " << shaderId
                      << " est encore utilisé ailleurs." << std::endl;
        }
    }
    else
    {
        std::cerr << "Erreur : shader avec l'ID " << shaderId << " non trouvé." << std::endl;
    }
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
        case sf::Keyboard::Comma:
            return KeyCode::Comma;
        case sf::Keyboard::Period:
            return KeyCode::Dot;
        case sf::Keyboard::Dash:
            return KeyCode::Tiret;
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

void RenderSystemSFML::resetShader() { _activeShader = nullptr; }

}  // namespace RType
