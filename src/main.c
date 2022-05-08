#include <time.h>

#include <SFML/System/Clock.h>
#include <SFML/Audio.h>
#include <SFML/Audio/Sound.h>
#include <SFML/Audio/SoundBuffer.h>

#include "datatypes.h"

#define BUF_COUNT				4
#define BUF_HALLOWEEN_01		0
#define BUF_HALLOWEEN_02		1
#define BUF_HALLOWEEN_03		2
#define BUF_HALLOWEEN_GHOST		3

#define SFX_COUNT				5
#define SFX_HALLOWEEN_01		0
#define SFX_HALLOWEEN_02		1
#define SFX_HALLOWEEN_02_LOW	2
#define SFX_HALLOWEEN_03		3
#define SFX_HALLOWEEN_GHOST		4

/*
* This RNG function is modified from Super Mario 64's source code: https://github.com/n64decomp/sm64.git
*/
uint16 rng_val;
uint16 rng(uint16 max) {
	uint16 s0;
	uint16 s1;

	if(rng_val == 0x560A) rng_val = 0;
	s0 = (uint8)rng_val << 8;
	s0 ^= rng_val;
	rng_val = ((s0 & 0xFF) << 8) | ((s0 & 0xFF00) >> 8);
	s0 = ((uint8)s0 << 1) ^ rng_val;
	s1 = (s0 >> 1) ^ 0xFF80;
	if(!(s0 & 1)) {
		if(s1 == 0xAA55)
			rng_val = 0;
		else
			rng_val = s1 ^ 0x1FF4;
	} else {
		rng_val = s1 ^ 0x8180;
	}

	return (uint16)rng_val % max;
}

int main() {
	uint8 i;
	uint8 last_sample;
	uint8 current_sample;
	float32 time_elapsed = 0.0f;
	float32 time_delta = 0.0f;

	sfClock* clock;

	sfSoundBuffer* sb_buffers[BUF_COUNT];
	sfSound* sfx_samples[SFX_COUNT];

	boolean close_program = FALSE;

	rng_val = (uint16)time(NULL);
	last_sample = rng(SFX_COUNT);
	current_sample = last_sample;

	clock = sfClock_create();

	sb_buffers[BUF_HALLOWEEN_01]	= sfSoundBuffer_createFromFile("res/halloween-1.wav");
	sb_buffers[BUF_HALLOWEEN_02] 	= sfSoundBuffer_createFromFile("res/halloween-2.wav");
	sb_buffers[BUF_HALLOWEEN_03] 	= sfSoundBuffer_createFromFile("res/halloween-3.wav");
	sb_buffers[BUF_HALLOWEEN_GHOST] =  sfSoundBuffer_createFromFile("res/halloween-ghost.wav");

	sfx_samples[SFX_HALLOWEEN_01] = sfSound_create();
	sfSound_setBuffer(sfx_samples[SFX_HALLOWEEN_01], sb_buffers[BUF_HALLOWEEN_01]);
	sfSound_setVolume(sfx_samples[SFX_HALLOWEEN_01], 50.0f);
	sfSound_setPitch( sfx_samples[SFX_HALLOWEEN_01], 0.1f);

	sfx_samples[SFX_HALLOWEEN_02] = sfSound_create();
	sfSound_setBuffer(sfx_samples[SFX_HALLOWEEN_02], sb_buffers[BUF_HALLOWEEN_02]);
	sfSound_setVolume(sfx_samples[SFX_HALLOWEEN_02], 50.0f);
	sfSound_setPitch( sfx_samples[SFX_HALLOWEEN_02], 0.2f);

	sfx_samples[SFX_HALLOWEEN_02_LOW] = sfSound_create();
	sfSound_setBuffer(sfx_samples[SFX_HALLOWEEN_02_LOW], sb_buffers[BUF_HALLOWEEN_02]);
	sfSound_setVolume(sfx_samples[SFX_HALLOWEEN_02_LOW], 50.0f);
	sfSound_setPitch( sfx_samples[SFX_HALLOWEEN_02_LOW], 0.1f);

	sfx_samples[SFX_HALLOWEEN_03] = sfSound_create();
	sfSound_setBuffer(sfx_samples[SFX_HALLOWEEN_03], sb_buffers[BUF_HALLOWEEN_03]);
	sfSound_setVolume(sfx_samples[SFX_HALLOWEEN_03], 50.0f);
	sfSound_setPitch( sfx_samples[SFX_HALLOWEEN_03], 0.1f);

	sfx_samples[SFX_HALLOWEEN_GHOST] = sfSound_create();
	sfSound_setBuffer(sfx_samples[SFX_HALLOWEEN_GHOST], sb_buffers[BUF_HALLOWEEN_GHOST]);
	sfSound_setVolume(sfx_samples[SFX_HALLOWEEN_GHOST], 50.0f);
	sfSound_setPitch( sfx_samples[SFX_HALLOWEEN_GHOST], 0.1f);

	sfSound_play(sfx_samples[current_sample]);

	while(!close_program) {
		/* updating */
		time_delta = sfTime_asSeconds(sfClock_restart(clock));
		time_elapsed += time_delta;

		if(time_elapsed >= 10.0f) {
			while(current_sample == last_sample) {
				current_sample = rng(SFX_COUNT);
			};

			last_sample = current_sample;

			sfSound_play(sfx_samples[current_sample]);
			time_elapsed = 0.0f;
		}
	}

	sfClock_destroy(clock);

	for(i = 0; i < BUF_COUNT; i++)
		sfSoundBuffer_destroy(sb_buffers[i]);

	for(i = 0; i < SFX_COUNT; i++)
		sfSound_destroy(sfx_samples[i]);

	return 0;
}
