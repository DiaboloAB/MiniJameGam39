/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

// std
#include "raylib.h"

class AudioManager {
public:
    static AudioManager& getInstance() {
        static AudioManager instance;
        return instance;
    }

    void init() {
        _car = LoadMusicStream("assets/audio/car.mp3");
        _footStep = LoadSound("assets/audio/footstep.wav");
        _death = LoadSound("assets/audio/death.mp3");
        _coin = LoadSound("assets/audio/coin.wav");
    }

    void playFootStep() {
        PlaySound(_footStep);
    }

    void playCoin() {
        PlaySound(_coin);
    }

    void playDeath() {
        PlaySound(_death);
    }

    void startCar() {
        PlayMusicStream(_car);
    }

    void stopCar() {
        StopMusicStream(_car);
    }

    void updateMusic() {
        UpdateMusicStream(_car);
    }

private:
    AudioManager(){};
    ~AudioManager(){};

    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    Sound _footStep;
    Sound _coin;
    Sound _death;
    Music _car;
};

#endif  // AUDIOMANAGER_H