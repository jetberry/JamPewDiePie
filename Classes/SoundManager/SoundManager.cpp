//
//  SoundManager.cpp
//  Jam
//
//  Created by Ostap on 23.11.14.
//
//

#include "SoundManager.h"

static SoundManager *s_soundManager = NULL;

SoundManager *SoundManager::getInstance() {
    if (!s_soundManager) {
        s_soundManager = new SoundManager();
    }
    return s_soundManager;
}

SoundManager::SoundManager() {
    m_audioProfile.name = "AudioProfileTest";
    m_audioProfile.maxInstances = SOUND_COUNT;
    m_audioProfile.minDelay = 1.0;
    
    m_soundsIds = __Array::create();
    m_soundsIds->retain();
    for (int i = 0; i < SOUND_COUNT; i++) {
//        int id = cocos2d::experimental::AudioEngine::play2d(SOUND_NAME[i], true, 0.4f, &m_audioProfile);
        __Integer* integer = __Integer::create(-1);
        m_soundsIds->addObject(integer);
    }
}

void SoundManager::playSound(Sounds sound, bool loop, float volume) {
    __Integer* id = static_cast<__Integer*>(m_soundsIds->getObjectAtIndex(sound));
    
    if (id->getValue() == -1) { // создать
        int new_id = cocos2d::experimental::AudioEngine::play2d(SOUND_NAME[sound], loop, volume, &m_audioProfile);
        __Integer* integer = __Integer::create(new_id);
        m_soundsIds->setObject(integer, sound);
        
        cocos2d::experimental::AudioEngine::setFinishCallback(new_id, [&](int id, const std::string& filePath){
            for (int i = 0; i < m_soundsIds->count(); i++) {
                __Integer* number = static_cast<__Integer*>(m_soundsIds->getObjectAtIndex(i));
                if (number->getValue() == id) {
                    __Integer* integer = __Integer::create(-1);
                    m_soundsIds->setObject(integer, i);
                    break;
                }
            }
        });
    } else { // проиграть
        cocos2d::experimental::AudioEngine::setCurrentTime(id->getValue(), 0);
        cocos2d::experimental::AudioEngine::setLoop(id->getValue(), loop);
        cocos2d::experimental::AudioEngine::setVolume(id->getValue(), volume);
        cocos2d::experimental::AudioEngine::resume(id->getValue());
    }
}

void SoundManager::pauseSound(Sounds sound_id) {
    __Integer* id = static_cast<__Integer*>(m_soundsIds->getObjectAtIndex(sound_id));
    cocos2d::experimental::AudioEngine::pause(id->getValue());
}

void SoundManager::resumeSound(Sounds sound_id) {
    __Integer* id = static_cast<__Integer*>(m_soundsIds->getObjectAtIndex(sound_id));
    cocos2d::experimental::AudioEngine::resume(id->getValue());
}

