//
//  SoundManager.h
//  Jam
//
//  Created by Ostap on 23.11.14.
//
//

#ifndef __Jam__SoundManager__
#define __Jam__SoundManager__

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d;
using namespace ui;

USING_NS_CC;

enum Sounds {
    sound_best_loop,
    sound_drop_item,
    sound_electro_loop,
    sound_haha,
    sound_harkem_shake,
    sound_monkey,
    sound_noise_loop,
    sound_ouch_1,
    sound_ouch_2,
    sound_ouch_3,
    sound_plane_crash,
    sound_power_down,
    sound_power_up,
    sound_raaalph,
    sound_scream_1,
    sound_scream_2,
    sound_scream_man,
    sound_toilet_open,
    sound_toilet,
    sound_wow,
    SOUND_COUNT
};

const char SOUND_NAME[SOUND_COUNT][128] = {
    "sound/best_loop.mp3",
    "sound/drop_item.mp3",
    "sound/electro_loop.mp3",
    "sound/haha.mp3",
    "sound/harkem_shake.mp3",
    "sound/monkey.mp3",
    "sound/noise_loop.mp3",
    "sound/ouch_1.mp3",
    "sound/ouch_2.mp3",
    "sound/ouch_3.mp3",
    "sound/plane_crash.mp3",
    "sound/power_down.mp3",
    "sound/power_up.mp3",
    "sound/raaalph.mp3",
    "sound/scream_1.mp3",
    "sound/scream_2.mp3",
    "sound/scream_man.mp3",
    "sound/toilet_open.mp3",
    "sound/toilet.mp3",
    "sound/wow.mp3"
};

class SoundManager {
public:
    static SoundManager* getInstance();
    
    SoundManager();
    
    void playSound(Sounds sound, bool loop, float volume);
    void pauseSound(Sounds id);
    void resumeSound(Sounds id);
    
private:
    cocos2d::experimental::AudioProfile m_audioProfile;
    __Array* m_soundsIds;
};


#endif /* defined(__Ava__SoundManager__) */
