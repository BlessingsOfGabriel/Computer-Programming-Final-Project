#include "LoadMedia.h"

LoadedTexture loadedTexture;
LoadedSound loadedSound;

LoadedTexture::LoadedTexture() {
    free();
    _loadedTextures.clear();
    std::string names[16] = {"Archer","Board", "Common", "GameOver1","GameOver2","GoldTower","Knight","StartMenu","Soldier","Store","Tower","Tutorial1","Tutorial2","Tutorial3","Tutorial4","Tutorial5"};
    for (int i = 0;i < 16; i++) _toLoadFileName.push_back(names[i]);
}

LoadedTexture::~LoadedTexture() {
    free();
    _loadedTextures.clear();
}

void LoadedTexture::free() {
    for (std::map<std::string, SDL_Texture*>::iterator it = _loadedTextures.begin(); it != _loadedTextures.end(); it++) {
        SDL_DestroyTexture(it->second);
        it->second = NULL;
    }
}

SDL_Texture* LoadedTexture::_loadTextureFromFile(std::string name) {
    try {
        SDL_Texture* newTexture = NULL;
        std::string prefix = "../media/images/", postfix = ".png";
        SDL_Surface* loadedSurface = IMG_Load((prefix + name + postfix).c_str());
        if (loadedSurface == NULL) throw IMG_GetError();
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if (newTexture == NULL) throw SDL_GetError();
        SDL_FreeSurface( loadedSurface );
        return newTexture;
    }
    catch (const char* s) {
        return NULL;
    }
}

void LoadedTexture::loadAllTexture() {
    for (int i = 0;i < _toLoadFileName.size(); i++) {
      _loadedTextures[_toLoadFileName[i]] = _loadTextureFromFile(_toLoadFileName[i]);
    }
}

SDL_Texture* LoadedTexture::getTexture(std::string name) {
    return _loadedTextures[name];
}

LoadedSound::LoadedSound() {
    free();
    _loadedSound.clear();
    std::string names[1] = {"BGM"};
    for (int i = 0;i < 1; i++) _toLoadFileName.push_back(names[i]);
}

LoadedSound::~LoadedSound() {
    free();
    _loadedSound.clear();
}

void LoadedSound::loadAllSound() {
    for (int i = 0;i < _toLoadFileName.size(); i++) {
      _loadedSound[_toLoadFileName[i]] = _loadSoundFromFile(_toLoadFileName[i]);
    }
}


Mix_Chunk* LoadedSound::_loadSoundFromFile(std::string name) {
    std::string prefix = "../media/sound/", profix = ".wav";
    return Mix_LoadWAV((prefix + name + profix).c_str());
}


Mix_Chunk* LoadedSound::getSound(std::string name) {
    return _loadedSound[name];
}

void LoadedSound::playSound(int channel, std::string name, int times) {
    Mix_PlayChannel(channel, _loadedSound[name], times);
    return;
}

void LoadedSound::free() {
    for (std::map<std::string, Mix_Chunk*>::iterator it = _loadedSound.begin(); it != _loadedSound.end(); it++) {
        Mix_FreeChunk(it->second);
        it->second = NULL;
    }
}
