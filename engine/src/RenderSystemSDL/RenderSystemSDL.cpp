/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "RenderSystemSDL.hpp"

namespace RType
{

RenderSystemSDL::RenderSystemSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    if (TTF_Init() == -1) {
        std::cerr << "TTF could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }
    window = SDL_CreateWindow("R-Type", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    windowOpen = true;
    currentFont = nullptr;
    currentMusic = nullptr;
    shaderActive = false;
}

RenderSystemSDL::~RenderSystemSDL()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int RenderSystemSDL::generateUniqueId()
{
    return currentId++;
}

void RenderSystemSDL::pollEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            windowOpen = false;
        }
    }
}

bool RenderSystemSDL::getKey(KeyCode key) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    return state[SDL_GetScancodeFromKey(static_cast<SDL_Keycode>(key))];
}

bool RenderSystemSDL::getKeyUp(KeyCode key) {
    return false;
}

bool RenderSystemSDL::getKeyDown(KeyCode key) {
    return false;
}

void RenderSystemSDL::clearWindow() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void RenderSystemSDL::updateWindow() {
    SDL_RenderPresent(renderer);
}

mlg::vec3 RenderSystemSDL::getTextureSize(int id) {
    auto texture = textures[id];
    if (!texture) return mlg::vec3(0, 0, 0);
    int w, h;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &w, &h);
    return mlg::vec3(w, h, 0);
}

mlg::vec3 RenderSystemSDL::getMousePosition() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return mlg::vec3(x, y, 0);
}

void RenderSystemSDL::drawRectangle(mlg::vec4& spriteCoords, bool full, const mlg::vec3& color) {
    SDL_SetRenderDrawColor(renderer, color.x, color.y, color.z, 255);
    SDL_Rect rect = {static_cast<int>(spriteCoords.x), static_cast<int>(spriteCoords.y),
                     static_cast<int>(spriteCoords.z), static_cast<int>(spriteCoords.w)};
    SDL_RenderFillRect(renderer, &rect);
}

void RenderSystemSDL::setGameIcon(const std::string &filePath) {
    SDL_Surface* icon = SDL_LoadBMP(filePath.c_str());
    if (icon) {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    }
}

void RenderSystemSDL::loadFont(const std::string &filePath) {
    if (currentFont) {
        TTF_CloseFont(currentFont);
    }
    currentFont = TTF_OpenFont(filePath.c_str(), 24);
    if (!currentFont) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
}

int RenderSystemSDL::loadSprite(const std::string &filePath) {
    int id = generateUniqueId();
    if (textures.find(id) == textures.end()) {
        SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
        if (!surface) {
            std::cerr << "Unable to load image " << filePath << " SDL Error: " << SDL_GetError() << std::endl;
            return -1;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (texture) {
            textures[id] = std::shared_ptr<SDL_Texture>(texture, SDL_DestroyTexture);
        }
    }
    return id;
}

void RenderSystemSDL::drawSprite(int id, mlg::vec3 position, mlg::vec4 spriteRect,
                                 mlg::vec3 scale, float rotation) {
    auto texture = textures[id];
    if (!texture) return;
    SDL_Rect srcRect = {static_cast<int>(spriteRect.x), static_cast<int>(spriteRect.y),
                        static_cast<int>(spriteRect.z), static_cast<int>(spriteRect.w)};
    SDL_Rect dstRect = {static_cast<int>(position.x), static_cast<int>(position.y),
                        static_cast<int>(spriteRect.z * scale.x), static_cast<int>(spriteRect.w * scale.y)};
    SDL_RenderCopyEx(renderer, texture.get(), &srcRect, &dstRect, rotation, nullptr, SDL_FLIP_NONE);
}

void RenderSystemSDL::drawSprite(int id, mlg::vec3 position) {
    auto texture = textures[id];
    if (!texture) return;
    int w, h;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &w, &h);
    SDL_Rect dstRect = {static_cast<int>(position.x), static_cast<int>(position.y), w, h};
    SDL_RenderCopy(renderer, texture.get(), nullptr, &dstRect);
}

void RenderSystemSDL::drawSprite(const std::string& filePath, mlg::vec3 position,
                                 mlg::vec4 spriteCoords, mlg::vec3 scale, float rotation)
{
    // Charger le sprite s'il n'est pas déjà dans le cache
    int spriteId = loadSprite(filePath);
    
    if (spriteId == -1)
    {
        std::cerr << "Erreur : impossible de charger le sprite depuis " << filePath << std::endl;
        return;
    }

    auto it = textures.find(spriteId);
    if (it != textures.end())
    {
        SDL_Rect srcRect = {static_cast<int>(spriteCoords.x), static_cast<int>(spriteCoords.y),
                            static_cast<int>(spriteCoords.z), static_cast<int>(spriteCoords.w)};
        SDL_Rect dstRect = {static_cast<int>(position.x), static_cast<int>(position.y),
                            static_cast<int>(spriteCoords.z * scale.x), static_cast<int>(spriteCoords.w * scale.y)};
        SDL_RenderCopyEx(renderer, it->second.get(), &srcRect, &dstRect, rotation, nullptr, SDL_FLIP_NONE);
    }
    else
    {
        std::cerr << "Erreur : sprite non trouvé pour le fichier " << filePath << std::endl;
    }
}

void RenderSystemSDL::drawSprite(const std::string& filePath, mlg::vec3 position)
{
    int spriteId = loadSprite(filePath);
    
    if (spriteId == -1)
    {
        std::cerr << "Erreur : impossible de charger le sprite depuis " << filePath << std::endl;
        return;
    }

    auto it = textures.find(spriteId);
    if (it != textures.end())
    {
        int w, h;
        SDL_QueryTexture(it->second.get(), nullptr, nullptr, &w, &h);
        SDL_Rect dstRect = {static_cast<int>(position.x), static_cast<int>(position.y), w, h};

        SDL_RenderCopy(renderer, it->second.get(), nullptr, &dstRect);
    }
    else
    {
        std::cerr << "Erreur : sprite non trouvé pour le fichier " << filePath << std::endl;
    }
}


void RenderSystemSDL::drawText(const std::string& fontPath, const std::string& textStr, const mlg::vec3 position,
                               unsigned int fontSize, const mlg::vec3& color, bool centered) {
    if (!currentFont) {
        loadFont(fontPath);  // Load the font if not already loaded
    }
    SDL_Color sdlColor = { static_cast<Uint8>(color.x), static_cast<Uint8>(color.y), static_cast<Uint8>(color.z) };
    SDL_Surface* textSurface = TTF_RenderText_Solid(currentFont, textStr.c_str(), sdlColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {static_cast<int>(position.x), static_cast<int>(position.y), textSurface->w, textSurface->h};
    if (centered) {
        textRect.x -= textSurface->w / 2;
        textRect.y -= textSurface->h / 2;
    }
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void RenderSystemSDL::FullScreenWindow() {
    Uint32 fullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;
    SDL_SetWindowFullscreen(window, fullscreenFlag);
}

bool RenderSystemSDL::isWindowOpen() {
    return windowOpen;
}

void RenderSystemSDL::unloadSprite(int id) {
    textures.erase(id);
}

bool RenderSystemSDL::loadMusic(const std::string& filePath) {
    if (currentMusic) {
        Mix_FreeMusic(currentMusic);
    }
    currentMusic = Mix_LoadMUS(filePath.c_str());
    if (!currentMusic) {
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void RenderSystemSDL::playMusic(const std::string& filePath, bool loop) {
    if (!currentMusic) {
        loadMusic(filePath);
    }
    if (currentMusic) {
        Mix_PlayMusic(currentMusic, loop ? -1 : 1);
    }
}

void RenderSystemSDL::updateSounds() {}

void RenderSystemSDL::stopCurrentMusic() {
    Mix_HaltMusic();
}

void RenderSystemSDL::unloadMusic(const std::string& filePath) {
    if (currentMusic) {
        Mix_FreeMusic(currentMusic);
        currentMusic = nullptr;
    }
}

int RenderSystemSDL::loadSound(const std::string& filePath) {
    int id = generateUniqueId();
    if (soundEffects.find(id) == soundEffects.end()) {
        Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
        if (!sound) {
            std::cerr << "Failed to load sound: " << Mix_GetError() << std::endl;
            return -1;
        }
        soundEffects[id] = std::shared_ptr<Mix_Chunk>(sound, Mix_FreeChunk);
    }
    return id;
}

void RenderSystemSDL::playSound(int id) {
    auto sound = soundEffects[id];
    if (sound) {
        Mix_PlayChannel(-1, sound.get(), 0);
    }
}

void RenderSystemSDL::unloadSound(int id) {
    soundEffects.erase(id);
}

void RenderSystemSDL::setFramerateLimit(unsigned int limit) {
    // SDL does not have a direct framerate limiter, you'd need to handle it manually.
}

void RenderSystemSDL::setVerticalSyncEnabled(bool enabled) {
    SDL_GL_SetSwapInterval(enabled ? 1 : 0);
}

// Shader Management
int RenderSystemSDL::loadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    int shaderId = generateUniqueId();
    shaders[shaderId] = vertexShaderPath + ";" + fragmentShaderPath;
    return shaderId;
}

void RenderSystemSDL::setShader(int shaderId) {
    if (shaders.find(shaderId) != shaders.end()) {
        std::cout << "Shader set: " << shaders[shaderId] << std::endl;
        shaderActive = true;
        currentShaderId = shaderId;
    } else {
        std::cerr << "Shader not found with ID: " << shaderId << std::endl;
    }
}

void RenderSystemSDL::resetShader() {
    shaderActive = false;
    currentShaderId = -1;
    std::cout << "Shader reset." << std::endl;
}

}  // namespace RType
