#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <iostream>

static ma_engine engine;
static ma_sound music;

void InitAndPlayMusic(const char* filepath) {
  if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
    std::cerr << "miniaudio: engine init failed\n";
    return;
  }

  // 2) Stream the file into our 'music' object
  if (ma_sound_init_from_file(&engine, filepath, MA_SOUND_FLAG_STREAM | MA_SOUND_FLAG_ASYNC,
                              NULL,    // pGroup
                              NULL,    // pDoneFence
                              &music)  // pSound
      != MA_SUCCESS) {
    std::cerr << "miniaudio: failed to load " << filepath << "\n";
    ma_engine_uninit(&engine);
    return;
  }

  // 3) Tell it to loop, then start
  ma_sound_set_looping(&music, MA_TRUE);
  ma_sound_start(&music);
}

void ShutdownMusic() {
  ma_sound_uninit(&music);
  ma_engine_uninit(&engine);
}
