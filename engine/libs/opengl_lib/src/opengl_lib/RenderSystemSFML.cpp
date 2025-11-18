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
    : _isFullScreen(false), _nextSpriteId(1), _nextFontId(1), _nextMusicId(1), _nextSoundId(1)
{
    _activeShader = nullptr;

    if (!glfwInit()) throw std::runtime_error("Failed to initialize GLFW\n");
    _window = glfwCreateWindow(1280, 960, "Wow - Fractal - OMG", NULL, NULL);
    if (!_window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window\n");
    }
    glfwMakeContextCurrent(_window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        throw std::runtime_error("Failed to initialize GLEW\n");
    }
}

RenderSystemSFML::~RenderSystemSFML() {}

void RenderSystemSFML::pollEvents() {}

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

void RenderSystemSFML::clearWindow() {}

void RenderSystemSFML::updateWindow() {}

std::shared_ptr<sf::Texture> RenderSystemSFML::loadTexture(const std::string& filePath)
{
    if (_textures.find(filePath) != _textures.end())
    {
        return _textures[filePath];
    }
    auto texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(filePath))
    {
        std::cerr << "SFMLRenderSystem: Error loading texture: " << filePath << std::endl;
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
    }
    else
    {
        std::cerr << "SFMLRenderSystem: Error unloading sprite: " << spriteId << std::endl;
    }
}

void RenderSystemSFML::drawSprite(int spriteId, mlg::vec3 position, mlg::vec4 spriteCoords,
                                  mlg::vec3 scale, float rotation)
{
}

void RenderSystemSFML::drawSprite(int spriteId, mlg::vec3 position) {}

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

mlg::vec3 RenderSystemSFML::getMousePosition() {}

void RenderSystemSFML::setGameIcon(const std::string& filePath) {}

void RenderSystemSFML::drawText(int fontID, const std::string& textStr, const mlg::vec3 position,
                                unsigned int fontSize, const mlg::vec3& color, bool centered)
{
}

void RenderSystemSFML::drawRectangle(mlg::vec4& spriteCoords, bool full, const mlg::vec3& color) {}

void RenderSystemSFML::FullScreenWindow(bool fullscreen) {}

int RenderSystemSFML::loadMusic(const std::string& filePath)
{
    if (_musicCache.find(filePath) != _musicCache.end())
    {
        return _musicCache[filePath];
    }

    int musicId = _nextMusicId++;
    auto music = std::make_unique<sf::Music>();
    if (!music->openFromFile(filePath))
    {
        std::cerr << "SFMLRenderSystem: Error loading music: " << filePath << std::endl;
        return -1;
    }

    _musics[musicId] = std::move(music);
    _musicCache[filePath] = musicId;

    return musicId;
}

void RenderSystemSFML::playMusic(int musicID, bool loop)
{
    auto it = _musics.find(musicID);
    if (it != _musics.end())
    {
        if (musicID != _currentMusicId)
        {
            stopCurrentMusic();
        }
        _currentMusic = it->second.get();
        _currentMusic->setLoop(loop);
        _currentMusic->play();
        _currentMusicId = musicID;
    }
    else
    {
        std::cerr << "SFMLRenderSystem: Error playing music: music not found" << std::endl;
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
    }
    else
    {
        std::cerr << "SFMLRenderSystem: Error unloading music: music not found" << std::endl;
    }
}

int RenderSystemSFML::loadSound(const std::string& filePath)
{
    if (_soundCache.find(filePath) != _soundCache.end())
    {
        return _soundCache[filePath];
    }

    int soundId = _nextSoundId++;

    auto soundBuffer = std::make_shared<sf::SoundBuffer>();
    if (!soundBuffer->loadFromFile(filePath))
    {
        std::cerr << "SFMLRenderSystem: Error loading sound: " << filePath << std::endl;
        return -1;
    }

    _sounds[soundId] = soundBuffer;
    _soundCache[filePath] = soundId;

    return soundId;
}

void RenderSystemSFML::playSound(int soundId)
{
    auto it = _sounds.find(soundId);
    if (it != _sounds.end())
    {
        _activeSounds.emplace_back();
        sf::Sound& sound = _activeSounds.back();
        sound.setBuffer(*it->second);
        sound.setVolume(_soundVolume);
        sound.play();
    }
    else
    {
        std::cerr << "SFMLRenderSystem: Error playing sound: sound not found" << std::endl;
    }
}

void RenderSystemSFML::unloadSound(int soundId)
{
    auto it = _sounds.find(soundId);
    if (it != _sounds.end())
    {
        if (it->second.use_count() == 1)
        {
            _sounds.erase(it);
        }
    }
    else
    {
        std::cerr << "SFMLRenderSystem: Error unloading sound: sound not found" << std::endl;
    }
}

int RenderSystemSFML::loadFont(const std::string& filePath)
{
    if (_fontCache.find(filePath) != _fontCache.end())
    {
        return _fontCache[filePath];
    }

    int fontId = _nextFontId++;
    auto font = std::make_shared<sf::Font>();
    if (!font->loadFromFile(filePath))
    {
        std::cerr << "SFMLRenderSystem: Error loading font: " << filePath << std::endl;
        return -1;
    }

    _fonts[fontId] = font;
    _fontCache[filePath] = fontId;

    return fontId;
}
void RenderSystemSFML::setFramerateLimit(unsigned int limit) {}

void RenderSystemSFML::setVerticalSyncEnabled(bool enabled) {}

int RenderSystemSFML::loadShader(const std::string& vertexShaderPath,
                                 const std::string& fragmentShaderPath)
{
    if (_shaderCache.find(vertexShaderPath) != _shaderCache.end())
    {
        return -1;
    }

    int shaderId = _nextShaderId++;

    auto shader = std::make_shared<sf::Shader>();
    if (!shader->loadFromFile(vertexShaderPath, fragmentShaderPath))
    {
        std::cerr << "SFMLRenderSystem: Error loading shader: " << vertexShaderPath << " - "
                  << fragmentShaderPath << std::endl;
        return -1;
    }

    _shaders[shaderId] = shader;
    _shaderCache[vertexShaderPath] = shaderId;

    return shaderId;
}

void RenderSystemSFML::unloadShader(int shaderId)
{
    auto it = _shaders.find(shaderId);
    if (it != _shaders.end())
    {
        if (it->second.use_count() == 1)
        {
            _shaders.erase(it);
        }
    }
    else
    {
        std::cerr << "SFMLRenderSystem: Error unloading shader: shader not found" << std::endl;
    }
}

void RenderSystemSFML::setShader(int shaderId)
{
    auto it = _shaders.find(shaderId);
    if (it != _shaders.end())
    {
        _activeShader = it->second.get();
    }
    else
    {
        std::cerr << "SFMLRenderSystem::setShader : shader with ID " << shaderId << " not found."
                  << std::endl;
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
        case sf::Keyboard::F1:
            return KeyCode::F1;
        case sf::Keyboard::F2:
            return KeyCode::F2;
        case sf::Keyboard::F3:
            return KeyCode::F3;
        case sf::Keyboard::F4:
            return KeyCode::F4;
        case sf::Keyboard::F5:
            return KeyCode::F5;
        case sf::Keyboard::F6:
            return KeyCode::F6;
        case sf::Keyboard::F7:
            return KeyCode::F7;
        case sf::Keyboard::F8:
            return KeyCode::F8;
        case sf::Keyboard::F9:
            return KeyCode::F9;
        case sf::Keyboard::F10:
            return KeyCode::F10;
        case sf::Keyboard::F11:
            return KeyCode::F11;
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
            return KeyCode::Mouse1;
        case sf::Mouse::Middle:
            return KeyCode::Mouse2;
        case sf::Mouse::XButton1:
            return KeyCode::Mouse4;
        case sf::Mouse::XButton2:
            return KeyCode::Mouse5;
        default:
            return KeyCode::None;
    }
}

KeyCode RenderSystemSFML::convertSFMLJoystickButtonToKeyCode(unsigned int button)
{
    switch (button)
    {
        case 0:
            return KeyCode::ButtonA;  // A button
        case 1:
            return KeyCode::ButtonB;  // B button
        case 2:
            return KeyCode::ButtonX;  // X button
        case 3:
            return KeyCode::ButtonY;  // Y button
        case 4:
            return KeyCode::LeftBumper;  // Left bumper (LB)
        case 5:
            return KeyCode::RightBumper;  // Right bumper (RB)
        case 6:
            return KeyCode::LeftTrigger;  // Left trigger (may also be an axis)
        case 7:
            return KeyCode::RightTrigger;  // Right trigger (may also be an axis)
        case 8:
            return KeyCode::Select;  // Select/Back button
        case 9:
            return KeyCode::Start;  // Start/Options button
        case 10:
            return KeyCode::LeftStickPress;  // Pressable left stick
        case 11:
            return KeyCode::RightStickPress;  // Pressable right stick
        case 12:
            return KeyCode::DPadUp;  // D-Pad up
        case 13:
            return KeyCode::DPadDown;  // D-Pad down
        case 14:
            return KeyCode::DPadLeft;  // D-Pad left
        case 15:
            return KeyCode::DPadRight;  // D-Pad right

        default:
            return KeyCode::None;
    }
}

void RenderSystemSFML::setSoundVolume(int volume) { _soundVolume = volume; }

void RenderSystemSFML::resetShader() { _activeShader = nullptr; }

}  // namespace RType
