#pragma once

#include "fmod.hpp"
#include "fmod_errors.h"

class Sound
{
private:
  static FMOD::System*  _system;
  static FMOD::Channel* _channel;
  static int    _nsounds; // Compte d'occurrences.

  FMOD::Sound*  _sound;
  void init (void);
public:
  Sound  (const char*); // Charge un fichier de sons.
  ~Sound ();            // Libere les echantillons.
  void play (float volume =1., float pan =0.); // Le fait jouer.
};
