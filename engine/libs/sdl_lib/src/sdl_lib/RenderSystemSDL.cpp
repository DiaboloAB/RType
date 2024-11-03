#include "RenderSystemSDL.hpp"

namespace RType
{

RenderSystemSDL::RenderSystemSDL()
    : _isFullScreen(false), _nextSpriteId(1), _nextFontId(1), _nextMusicId(1), _nextSoundId(1)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "Error SDL: " << SDL_GetError() << std::endl;
        return;
    }

    _window = SDL_CreateWindow("RType", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080,
                               SDL_WINDOW_SHOWN);
    if (!_window)
    {
        std::cerr << "Error while creating the window: " << SDL_GetError() << std::endl;
        return;
    }

    _renderer =
        SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer)
    {
        std::cerr << "Error while creating the renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(_window);
        return;
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "TTF Error:" << TTF_GetError() << std::endl;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "Error SDL_mixer: " << Mix_GetError() << std::endl;
    }
}

RenderSystemSDL::~RenderSystemSDL()
{
    _textures.clear();
    _spriteCache.clear();
    _fonts.clear();
    _musics.clear();
    _soundCache.clear();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

// Gestion des événements
void RenderSystemSDL::pollEvents()
{
    _previousKeys = _currentKeys;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            _currentKeys[KeyCode::Close] = true;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            _currentKeys[convertSDLKeyToKeyCode(event.key.keysym.sym)] = true;
        }
        else if (event.type == SDL_KEYUP)
        {
            _currentKeys[convertSDLKeyToKeyCode(event.key.keysym.sym)] = false;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            _currentKeys[convertSDLMouseToKeyCode(event.button.button)] = true;
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            _currentKeys[convertSDLMouseToKeyCode(event.button.button)] = false;
        }
    }
}

bool RenderSystemSDL::getKey(KeyCode key) { return _currentKeys[key]; }

bool RenderSystemSDL::getKeyUp(KeyCode key) { return _previousKeys[key] && !_currentKeys[key]; }

bool RenderSystemSDL::getKeyDown(KeyCode key) { return !_previousKeys[key] && _currentKeys[key]; }

std::shared_ptr<SDL_Texture> RenderSystemSDL::loadTexture(const std::string& filePath)
{
    auto it = _textures.find(filePath);
    if (it != _textures.end())
    {
        return it->second;
    }

    SDL_Texture* rawTexture = IMG_LoadTexture(_renderer, filePath.c_str());
    if (!rawTexture)
    {
        std::cerr << "Error while loading the texture: " << filePath << " - "
                  << IMG_GetError() << std::endl;
        return nullptr;
    }

    auto texture = std::shared_ptr<SDL_Texture>(rawTexture, SDL_DestroyTexture);
    _textures[filePath] = texture;
    return texture;
}

int RenderSystemSDL::loadSprite(const std::string& filePath)
{
    auto texture = loadTexture(filePath);
    if (!texture) return -1;
    int spriteId = _nextSpriteId++;
    _spriteCache[spriteId] = texture;
    return spriteId;
}

void RenderSystemSDL::unloadSprite(int spriteId) { _spriteCache.erase(spriteId); }

void RenderSystemSDL::drawSprite(int spriteId, mlg::vec3 position, mlg::vec4 spriteRect,
                                 mlg::vec3 scale, float rotation)
{
    auto it = _spriteCache.find(spriteId);
    if (it != _spriteCache.end())
    {
        SDL_Rect srcRect = {static_cast<int>(spriteRect.x), static_cast<int>(spriteRect.y),
                            static_cast<int>(spriteRect.z), static_cast<int>(spriteRect.w)};

        float realWidth = spriteRect.z * scale.x;
        float realHeight = spriteRect.w * scale.y;

        float centerX = position.x - (scale.x > 0 ? 0 : realWidth);
        float centerY = position.y - (scale.y > 0 ? 0 : realHeight);

        SDL_Rect dstRect = {static_cast<int>(centerX), static_cast<int>(centerY),
                            static_cast<int>(realWidth), static_cast<int>(realHeight)};

        if (SDL_RenderCopyEx(_renderer, it->second.get(), &srcRect, &dstRect, rotation, nullptr,
                             SDL_FLIP_NONE) != 0)
        {
            std::cerr << "Error SDL_RenderCopyEx : " << SDL_GetError() << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: Sprite with ID " << spriteId << " not found." << std::endl;
    }
}

void RenderSystemSDL::drawSprite(int spriteId, mlg::vec3 position)
{
    auto it = _spriteCache.find(spriteId);
    if (it != _spriteCache.end())
    {
        SDL_Rect dstRect = {static_cast<int>(position.x), static_cast<int>(position.y), 0, 0};
        SDL_QueryTexture(it->second.get(), nullptr, nullptr, &dstRect.w, &dstRect.h);
        SDL_RenderCopy(_renderer, it->second.get(), nullptr, &dstRect);
    }
    else
    {
        std::cerr << "Error: Sprite with ID " << spriteId << " not found." << std::endl;
    }
}

void RenderSystemSDL::drawRectangle(mlg::vec4& spriteCoords, bool full, const mlg::vec3& color)
{
    SDL_Rect rect = {static_cast<int>(spriteCoords.x), static_cast<int>(spriteCoords.y),
                     static_cast<int>(spriteCoords.z), static_cast<int>(spriteCoords.w)};
    SDL_SetRenderDrawColor(_renderer, static_cast<Uint8>(color.x), static_cast<Uint8>(color.y),
                           static_cast<Uint8>(color.z), 255);

    if (full)
    {
        SDL_RenderFillRect(_renderer, &rect);
    }
    else
    {
        SDL_RenderDrawRect(_renderer, &rect);
    }
}

mlg::vec3 RenderSystemSDL::getTextureSize(int spriteId)
{
    auto it = _spriteCache.find(spriteId);
    if (it != _spriteCache.end())
    {
        int width, height;
        SDL_QueryTexture(it->second.get(), nullptr, nullptr, &width, &height);
        return mlg::vec3(static_cast<float>(width), static_cast<float>(height), 0);
    }
    return mlg::vec3(0, 0, 0);
}

int RenderSystemSDL::loadFont(const std::string& filePath)
{

    if (_fontCache.find(filePath) != _fontCache.end())
    {
        return _fontCache[filePath];
    }

    int fontID = _nextFontId++;
    TTF_Font* rawFont = TTF_OpenFont(filePath.c_str(), 24);
    if (!rawFont)
    {
        std::cerr << "SFMLRenderSystem: Error loading font: " << filePath << std::endl;
        return -1;
    }

    std::cerr << "SFMLRenderSystem: Error loading font: " << filePath << std::endl;
    _fonts[fontID] = std::shared_ptr<TTF_Font>(rawFont, TTF_CloseFont);
    _fontCache[filePath] = fontID;
    return fontID;
}

void RenderSystemSDL::drawText(int fontID, const std::string& textStr, const mlg::vec3 position,
                               unsigned int fontSize, const mlg::vec3& color, bool centered)
{
    auto it = _fonts.find(fontID);
    if (it == _fonts.end())
    {
        std::cerr << "Error: Font not found (ID: " << fontID << ")" << std::endl;
        return;
    }
    SDL_Color sdlColor = {static_cast<Uint8>(color.x), static_cast<Uint8>(color.y),
                          static_cast<Uint8>(color.z)};
    SDL_Surface* surface = TTF_RenderText_Solid(it->second.get(), textStr.c_str(), sdlColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_Rect dstRect = {static_cast<int>(position.x), static_cast<int>(position.y), surface->w,
                        surface->h};

    if (centered)
    {
        dstRect.x -= dstRect.w / 2;
        dstRect.y -= dstRect.h / 2;
    }
    SDL_RenderCopy(_renderer, texture, nullptr, &dstRect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void RenderSystemSDL::unloadFont(int fontID)
{
    auto it = _fonts.find(fontID);
    if (it != _fonts.end() && it->second.use_count() == 1)
    {
        _fonts.erase(it);
    }
}

int RenderSystemSDL::loadMusic(const std::string& filePath)
{
    if (_musicCache.find(filePath) != _musicCache.end())
    {
        return _musicCache[filePath];
    }

    int musicID = _nextMusicId++;
    Mix_Music* rawMusic = Mix_LoadMUS(filePath.c_str());
    if (!rawMusic)
    {
        std::cerr << "Error while loading the music: " << Mix_GetError() << std::endl;
        return -1;
    }

    _musics[musicID] = std::shared_ptr<Mix_Music>(rawMusic, Mix_FreeMusic);
    _musicCache[filePath] = musicID;
    return musicID;
}

void RenderSystemSDL::playMusic(int musicID, bool loop)
{
    auto it = _musics.find(musicID);
    if (it != _musics.end())
    {
        Mix_PlayMusic(it->second.get(), loop ? -1 : 1);
    }
}

void RenderSystemSDL::stopCurrentMusic() { Mix_HaltMusic(); }

void RenderSystemSDL::unloadMusic(int musicID)
{
    auto it = _musics.find(musicID);
    if (it != _musics.end() && it->second.use_count() == 1)
    {
        _musics.erase(it);
    }
}

int RenderSystemSDL::loadSound(const std::string& filePath)
{
    if (_sound_Cache.find(filePath) != _sound_Cache.end())
    {
        return _sound_Cache[filePath];
    }

    int soundID = _nextSoundId++;
    Mix_Chunk* rawSound = Mix_LoadWAV(filePath.c_str());
    if (!rawSound)
    {
        std::cerr << "Error while loading the sound: " << Mix_GetError() << std::endl;
        return -1;
    }

    _soundCache[soundID] = std::shared_ptr<Mix_Chunk>(rawSound, Mix_FreeChunk);
    _sound_Cache[filePath] = soundID;
    return soundID;
}

void RenderSystemSDL::playSound(const int soundID)
{
    auto it = _soundCache.find(soundID);
    if (it != _soundCache.end())
    {
        Mix_PlayChannel(-1, it->second.get(), 0);
    }
}

void RenderSystemSDL::unloadSound(const int soundID)
{
    auto it = _soundCache.find(soundID);
    if (it != _soundCache.end() && it->second.use_count() == 1)
    {
        _soundCache.erase(it);
    }
}

mlg::vec3 RenderSystemSDL::getMousePosition()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    return mlg::vec3(static_cast<float>(x), static_cast<float>(y), 0);
}

void RenderSystemSDL::setGameIcon(const std::string& filePath)
{
    SDL_Surface* icon = IMG_Load(filePath.c_str());
    if (!icon)
    {
        std::cerr << "Error while loading the icon: : " << IMG_GetError() << std::endl;
        return;
    }
    SDL_SetWindowIcon(_window, icon);
    SDL_FreeSurface(icon);
}

void RenderSystemSDL::clearWindow()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

void RenderSystemSDL::updateWindow() { SDL_RenderPresent(_renderer); }

void RenderSystemSDL::FullScreenWindow(bool fullscreen)
{
    _isFullScreen = fullscreen;
    SDL_SetWindowFullscreen(_window, _isFullScreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

void RenderSystemSDL::setFramerateLimit(unsigned int limit) { SDL_Delay(1000 / limit); }

void RenderSystemSDL::setVerticalSyncEnabled(bool enabled)
{
    SDL_GL_SetSwapInterval(enabled ? 1 : 0);
}

int RenderSystemSDL::loadShader(const std::string& vertexShaderPath,
                                const std::string& fragmentShaderPath)
{
    std::cerr << "Error: Shaders are not supported by SDL without OpenGL." << std::endl;
    return -1;
}

void RenderSystemSDL::setShader(int shaderId)
{
    std::cerr << "Error: Shaders are not supported by SDL without OpenGL." << std::endl;
}

void RenderSystemSDL::resetShader()
{
    std::cerr << "Error: Shaders are not supported by SDL without OpenGL." << std::endl;
}

void RenderSystemSDL::unloadShader(int shaderId)
{
    std::cerr << "Error: Shaders are not supported by SDL without OpenGL." << std::endl;
}

KeyCode RenderSystemSDL::convertSDLKeyToKeyCode(SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_a:
            return KeyCode::A;
        case SDLK_b:
            return KeyCode::B;
        case SDLK_c:
            return KeyCode::C;
        case SDLK_d:
            return KeyCode::D;
        case SDLK_e:
            return KeyCode::E;
        case SDLK_f:
            return KeyCode::F;
        case SDLK_g:
            return KeyCode::G;
        case SDLK_h:
            return KeyCode::H;
        case SDLK_i:
            return KeyCode::I;
        case SDLK_j:
            return KeyCode::J;
        case SDLK_k:
            return KeyCode::K;
        case SDLK_l:
            return KeyCode::L;
        case SDLK_m:
            return KeyCode::M;
        case SDLK_n:
            return KeyCode::N;
        case SDLK_o:
            return KeyCode::O;
        case SDLK_p:
            return KeyCode::P;
        case SDLK_q:
            return KeyCode::Q;
        case SDLK_r:
            return KeyCode::R;
        case SDLK_s:
            return KeyCode::S;
        case SDLK_t:
            return KeyCode::T;
        case SDLK_u:
            return KeyCode::U;
        case SDLK_v:
            return KeyCode::V;
        case SDLK_w:
            return KeyCode::W;
        case SDLK_x:
            return KeyCode::X;
        case SDLK_y:
            return KeyCode::Y;
        case SDLK_z:
            return KeyCode::Z;
        case SDLK_UP:
            return KeyCode::UpArrow;
        case SDLK_DOWN:
            return KeyCode::DownArrow;
        case SDLK_LEFT:
            return KeyCode::LeftArrow;
        case SDLK_RIGHT:
            return KeyCode::RightArrow;
        case SDLK_ESCAPE:
            return KeyCode::Escape;
        case SDLK_SPACE:
            return KeyCode::Space;
        case SDLK_RETURN:
            return KeyCode::Enter;
        case SDLK_BACKSPACE:
            return KeyCode::Backspace;
        case SDLK_TAB:
            return KeyCode::Tab;
        case SDLK_0:
            return KeyCode::Alpha0;
        case SDLK_1:
            return KeyCode::Alpha1;
        case SDLK_2:
            return KeyCode::Alpha2;
        case SDLK_3:
            return KeyCode::Alpha3;
        case SDLK_4:
            return KeyCode::Alpha4;
        case SDLK_5:
            return KeyCode::Alpha5;
        case SDLK_6:
            return KeyCode::Alpha6;
        case SDLK_7:
            return KeyCode::Alpha7;
        case SDLK_8:
            return KeyCode::Alpha8;
        case SDLK_9:
            return KeyCode::Alpha9;
        case SDLK_COMMA:
            return KeyCode::Comma;
        case SDLK_PERIOD:
            return KeyCode::Dot;
        case SDLK_MINUS:
            return KeyCode::Tiret;
        default:
            return KeyCode::None;
    }
}

KeyCode RenderSystemSDL::convertSDLMouseToKeyCode(Uint8 button)
{
    switch (button)
    {
        case SDL_BUTTON_LEFT:
            return KeyCode::Mouse0;
        case SDL_BUTTON_RIGHT:
            return KeyCode::Mouse2;
        case SDL_BUTTON_MIDDLE:
            return KeyCode::Mouse3;
        case SDL_BUTTON_X1:
            return KeyCode::Mouse4;
        case SDL_BUTTON_X2:
            return KeyCode::Mouse5;
        default:
            return KeyCode::None;
    }
}

KeyCode RenderSystemSDL::convertSDLJoystickButtonToKeyCode(Uint8 button)
{
    switch (button)
    {
        case 0: return KeyCode::ButtonA;        // A button
        case 1: return KeyCode::ButtonB;        // B button
        case 2: return KeyCode::ButtonX;        // X button
        case 3: return KeyCode::ButtonY;        // Y button
        case 4: return KeyCode::LeftBumper;     // Left bumper (LB)
        case 5: return KeyCode::RightBumper;    // Right bumper (RB)
        case 6: return KeyCode::LeftTrigger;    // Left trigger (may also be an axis)
        case 7: return KeyCode::RightTrigger;   // Right trigger (may also be an axis)
        case 8: return KeyCode::Select;         // Select/Back button
        case 9: return KeyCode::Start;          // Start/Options button
        case 10: return KeyCode::LeftStickPress; // Pressable left stick
        case 11: return KeyCode::RightStickPress; // Pressable right stick
        case 12: return KeyCode::DPadUp;        // D-Pad up
        case 13: return KeyCode::DPadDown;      // D-Pad down
        case 14: return KeyCode::DPadLeft;      // D-Pad left
        case 15: return KeyCode::DPadRight;     // D-Pad right

        default: return KeyCode::None;
    }
}

void RenderSystemSDL::setSoundVolume(int volume)
{
    _soundVolume = volume;
}

}  // namespace RType
