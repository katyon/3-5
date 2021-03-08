#ifndef INCLUDE_AL_SOUND
#define INCLUDE_AL_SOUND

#include <vorbis/vorbisfile.h> 
#include <al.h> 
#include <alc.h> 
#include <Windows.h>
#include <thread>
#include <mutex>
#include <assert.h>
#include <intsafe.h>

bool alc_open_device();
void alc_close_device();

class sound_effect
{
public:
	sound_effect() = default;
	virtual ~sound_effect() = default;
	virtual void process(const float* input_samples[2], float* output_samples[2], int sample_frames, int frequency) = 0;
};
class volume_effect : public sound_effect
{
public:
	volume_effect() {}
	virtual ~volume_effect() {};
	virtual void process(const float* input_samples[2], float* output_samples[2], int sample_frames, int frequency)
	{
		float volumes[2]{ powf(10.0f, volumes_db[0] / 20.0f), powf(10.0f, volumes_db[1] / 20.0f) };
		float z[2]{ 0, 0 };
		float a1[2]{ 0.49f, 0.49f };
		float a0[2]{ 1.0f - a1[0], 1.0f - a1[1] };
		for (int frame = 0; frame < sample_frames; ++frame)
		{
			output_samples[0][frame] = (input_samples[0][frame] * a0[0] + z[0] * a1[0]) * volumes[0];
			z[0] = input_samples[0][frame];
			output_samples[1][frame] = (input_samples[1][frame] * a0[1] + z[0] * a1[1]) * volumes[1];
			z[1] = input_samples[1][frame];
		}
	}
	float volumes_db[2]{ -6.f/*dB*/, -6.f/*dB*/ };
};
class delay_effect : public sound_effect
{
	std::mutex mutex;

	float delat_time{ 0.5f };
	float wet{ 0.2f };
	float dry{ 0.8f };
	bool bypass{ false };
public:
	float& delat_time_s() { std::lock_guard lock(mutex); return delat_time; }
	float& wet_s() { std::lock_guard lock(mutex); return wet; }
	float& dry_s() { std::lock_guard lock(mutex); return dry; }
	bool& bypass_s() { std::lock_guard lock(mutex); return bypass; }

	float* circular_buffer[2]; // circular_buffer
	const int buffer_length{ 48000 * 10 };
	int writing_position{ 0 };

	delay_effect()
	{
		circular_buffer[0] = new float[buffer_length];
		circular_buffer[1] = new float[buffer_length];
	}
	~delay_effect()
	{
		delete[] circular_buffer[0];
		delete[] circular_buffer[1];
	};
	void process(const float* input_samples[2], float* output_samples[2], int sample_frames, int frequency)
	{
		const int delay_samples{ static_cast<int>(frequency * delat_time_s()) };

		for (int frame = 0; frame < sample_frames; ++frame)
		{
			writing_position++;
			if (writing_position >= buffer_length)
			{
				writing_position = 0;
			}
			assert(writing_position >= 0 && writing_position < buffer_length);

			int reading_position = writing_position - delay_samples;
			if (reading_position < 0)
			{
				reading_position += buffer_length;
			}
			assert(reading_position >= 0 && reading_position < buffer_length);

			if (bypass_s())
			{
				output_samples[0][frame] = input_samples[0][frame];
				output_samples[1][frame] = input_samples[1][frame];
			}
			else
			{
				output_samples[0][frame] = dry_s() * input_samples[0][frame] + wet_s() * circular_buffer[0][reading_position];
				output_samples[1][frame] = dry_s() * input_samples[1][frame] + wet_s() * circular_buffer[1][reading_position];
			}

			circular_buffer[0][writing_position] = input_samples[0][frame];
			circular_buffer[1][writing_position] = input_samples[1][frame];
		}

	}
};

class sound_buffer
{
public:
	ALuint buffer;
	ALuint source;
	ALenum format = AL_FORMAT_STEREO16;
	ALsizei total_bytes = 0;

	sound_buffer(const char* filename);
	virtual ~sound_buffer();
	sound_buffer(sound_buffer&) = delete;
	sound_buffer& operator=(sound_buffer&) = delete;

	std::string filename;
	ALsizei samples = 0;
	ALsizei sample_frames = 0;
	ALshort* raw_data = nullptr;
	ALsizei bits = 16;
	ALsizei channels = 2;
	ALsizei frequency = 44100;

	void play() const
	{
		alBufferData(buffer, format, raw_data, total_bytes, frequency);
		alSourcei(source, AL_BUFFER, buffer);
		alSourcePlay(source);
	}

	void play(sound_effect* sound_effect)
	{
		assert(sound_effect && "");

		float* input_samples[2]{ new float[sample_frames] , new float[sample_frames] };
		query_samples(input_samples, sample_frames, 0);

		float* output_samples[2]{ new float[sample_frames] , new float[sample_frames] };
		sound_effect->process(const_cast<const float**>(input_samples), output_samples, sample_frames, frequency);

		ALshort* cooked_data = new ALshort[static_cast<size_t>(sample_frames) * 2];
		for (size_t frame = 0; frame < sample_frames; ++frame)
		{
			cooked_data[frame * 2 + 0] = static_cast<ALshort>(output_samples[0][frame] * SHORT_MAX);
			cooked_data[frame * 2 + 1] = static_cast<ALshort>(output_samples[1][frame] * SHORT_MAX);
		}

		alBufferData(buffer, AL_FORMAT_STEREO16, cooked_data, total_bytes * (channels == 1 ? 2 : 1), frequency);
		alSourcei(source, AL_BUFFER, buffer);
		alSourcePlay(source);

		delete[] input_samples[0];
		delete[] input_samples[1];
		delete[] output_samples[0];
		delete[] output_samples[1];
		delete[] cooked_data;
	}
	// destructive processing
	void process(sound_effect* sound_effect)
	{
		float* input_samples[2]{ new float[sample_frames] , new float[sample_frames] };
		query_samples(input_samples, sample_frames, 0);

		float* output_samples[2]{ new float[sample_frames] , new float[sample_frames] };
		sound_effect->process(const_cast<const float**>(input_samples), output_samples, sample_frames, frequency);

		if (channels == 1)
		{
			format = AL_FORMAT_STEREO16;
			channels = 2;
			samples *= 2;
			total_bytes *= 2;
			delete[] raw_data;
			raw_data = new ALshort[samples];
		}
		for (size_t frame = 0; frame < sample_frames; ++frame)
		{
			raw_data[frame * 2 + 0] = static_cast<ALshort>(output_samples[0][frame] * SHORT_MAX);
			raw_data[frame * 2 + 1] = static_cast<ALshort>(output_samples[1][frame] * SHORT_MAX);
		}

		delete[] input_samples[0];
		delete[] input_samples[1];
		delete[] output_samples[0];
		delete[] output_samples[1];
	}
	void stop() const
	{
		alSourceStop(source);
	}
	void pause() const
	{
		alSourcePause(source);
	}
	void rewind() const
	{
		alSourceRewind(source);
	}
	bool playing() const
	{
		ALint source_state;
		alGetSourcei(source, AL_SOURCE_STATE, &source_state);
		return source_state == AL_PLAYING;
	}
	void volume(float gain) const
	{
		alSourcef(source, AL_GAIN, gain);
	}
	void loop() const
	{
		alSourcei(source, AL_LOOPING, 1);
	}
	void unloop() const
	{
		alSourcei(source, AL_LOOPING, 0);
	}

	float sec_offset() const
	{
		ALfloat sec_offset = 0;
		alGetSourcef(source, AL_SEC_OFFSET, &sec_offset);
		return sec_offset;
	}
	int sample_offset() const
	{
		ALint sample_offset = 0;
		alGetSourcei(source, AL_SAMPLE_OFFSET, &sample_offset);
		return sample_offset;
	}
	int frame_offset() const
	{
		ALint sample_offset = 0;
		alGetSourcei(source, AL_SAMPLE_OFFSET, &sample_offset);
		return sample_offset;
	}
	int byte_offset() const
	{
		ALint byte_offset = 0;
		alGetSourcei(source, AL_BYTE_OFFSET, &byte_offset);
		return byte_offset;
	}

	void query_samples(float* channel_buffers[2], size_t buffer_size, int sample_offset);
};


class sound_stream
{
	static constexpr uint32_t queue_buffer_samples{ 8192 };
	static constexpr uint32_t queue_buffers{ 4 };

	ALshort* raw_data{};
	ALshort* cooked_data{};
	ALfloat* input_samples[2]{};
	ALfloat* output_samples[2]{};

public:
	sound_effect* effect = nullptr;

	ALuint source = 0;
	sound_stream(const char* filename, sound_effect* effect);
	virtual ~sound_stream();
	sound_stream(sound_stream&) = delete;
	sound_stream& operator=(sound_stream&) = delete;

	void play() const
	{
		if (alIsSource(source))
		{
			ALenum state;
			alGetSourcei(source, AL_SOURCE_STATE, &state);
			switch (state)
			{
			case AL_STOPPED:
			case AL_INITIAL:
			case AL_PAUSED:
				alSourcePlay(source);
				break;
			case AL_PLAYING:
				break;
			}
		}
	}
	void stop() const
	{
		alSourceStop(source);
	}
	void pause() const
	{
		alSourcePause(source);
	}
	void volume(float gain) const
	{
		alSourcef(source, AL_GAIN, gain);
	}
	bool playing() const
	{
		ALint source_state;
		alGetSourcei(source, AL_SOURCE_STATE, &source_state);
		return source_state == AL_PLAYING;
	}

private:
	ALuint buffers[queue_buffers];
	vorbis_info* info;

	FILE* fp = 0;
	OggVorbis_File vf;

	void update();
	void stream(ALuint buffer);

	std::unique_ptr<std::thread> streaming_thread;
	std::mutex streaming_mutex;
};

#endif // !INCLUDE_AL_SOUND