#ifdef _M_IX86 //x86
#pragma comment( lib, "./OpenAL/WIN32/OpenAL32.lib" )
#if _DEBUG
#pragma comment( lib, "./OpenAL/WIN32/libvorbis_staticD.lib" )
#pragma comment( lib, "./OpenAL/WIN32/libvorbisfile_staticD.lib" )
#pragma comment( lib, "./OpenAL/WIN32/libogg_staticD.lib" )
#else
#pragma comment( lib, "./OpenAL/WIN32/libvorbis_static.lib" )
#pragma comment( lib, "./OpenAL/WIN32/libvorbisfile_static.lib" )
#pragma comment( lib, "./OpenAL/WIN32/libogg_static.lib" )
#endif
#else
#pragma comment( lib, "./OpenAL/WIN64/OpenAL32.lib" )
#if _DEBUG
#pragma comment( lib, "./OpenAL/WIN64/libvorbis_staticD.lib" )
#pragma comment( lib, "./OpenAL/WIN64/libvorbisfile_staticD.lib" )
#pragma comment( lib, "./OpenAL/WIN64/libogg_staticD.lib" )
#else
#pragma comment( lib, "./OpenAL/WIN64/libvorbis_static.lib" )
#pragma comment( lib, "./OpenAL/WIN64/libvorbisfile_static.lib" )
#pragma comment( lib, "./OpenAL/WIN64/libogg_static.lib" )
#endif
#endif

#include "AL_Sound.h"

#include <string.h>

#include <thread>
#include <chrono>
#include <libloaderapi.h>


static ALCdevice*	alc_device	=	nullptr;
static ALCcontext*	alc_context	=	nullptr;
static HMODULE		alc_dll		=	nullptr;

bool alc_open_device()
{
	//if(!alc_dll)alc_dll = LoadLibraryW(L"");
	// Verify that a given extension is available for the current context
	ALCboolean enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
	if (enumeration == AL_FALSE)
	{
		assert(false && "Enumeration extension not availablet");
	}
	// Retrieve a list of available devices
	// Each device name is separated by a single NULL character
	// and the list is terminated with 2 NULL characters
	const ALCchar* deviceNameList = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
	const ALCchar* defaultDeviceName = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
	alc_device = alcOpenDevice(defaultDeviceName);
	assert(alc_device && "Unable to open default device");
	if (!alc_device)
	{
		return false;
	}
	alc_context = alcCreateContext(alc_device, NULL);
	assert(alc_context && "Failed to create context");
	if (alc_context == NULL)
	{
		alcCloseDevice(alc_device);
		return false;
	}
	if (!alcMakeContextCurrent(alc_context))
	{
		assert(false && "Failed to make default context");
		alcDestroyContext(alc_context);
		alcCloseDevice(alc_device);
		return false;
	}
	return true;
}
void alc_close_device()
{
	alcMakeContextCurrent(NULL);
	alcDestroyContext(alc_context);
	alcCloseDevice(alc_device);
	//if (alc_dll) { FreeLibrary(alc_dll); }
}

sound_buffer::sound_buffer(const char* filename) : buffer(0), source(0), filename(filename)
{
	FILE* fp;
	fopen_s(&fp, filename, "rb");
	assert(fp && "sound_buffer::open : 'fopen_s' error");

	OggVorbis_File vf;
	int ov_e = ov_open(fp, &vf, NULL, 0);
	assert(ov_e == 0 && "sound_buffer::open : 'ov_open' error");

	vorbis_info* info = ov_info(&vf, -1);
	frequency = info->rate;

	format = info->channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
	channels = info->channels;
	total_bytes = info->channels * sizeof(ALshort) * static_cast<ALsizei>(ov_pcm_total(&vf, -1));
	samples = total_bytes / sizeof(ALshort);
	sample_frames = samples / channels;
	raw_data = new ALshort[samples];

	int read = 0;
	while (true)
	{
		int bitstream = 0;
		long size = ov_read(&vf, &(reinterpret_cast<char*>(raw_data)[read]), total_bytes - read, 0, 2, 1, &bitstream);
		if (size <= 0)
			break;
		read += size;
	}
	assert(total_bytes == read && "sound_buffer::open : 'ov_read' error");

	fclose(fp);
	ov_clear(&vf);

	alGenBuffers(1, &buffer);
	assert(alGetError() == AL_NO_ERROR && "alGenBuffers error");

	alGenSources(1, &source);
	assert(alGetError() == AL_NO_ERROR && "alGenSources error");
}
sound_buffer::~sound_buffer()
{
	alSourceStop(source);
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);

	delete[] raw_data;
}
void sound_buffer::query_samples(float* channel_buffers[2], size_t buffer_size, int frame_offset)
{
	assert(frame_offset < sample_frames && "");

	for (size_t frame = 0; frame < buffer_size; ++frame)
	{
		size_t sample_offset = (frame_offset + frame) * channels;
		if (channel_buffers[0])
		{
			channel_buffers[0][frame] = (sample_offset < samples) ? static_cast<float>(raw_data[sample_offset + 0]) / SHORT_MAX : 0.0f;
		}
		if (channel_buffers[1])
		{
			channel_buffers[1][frame] = (sample_offset < samples) ? static_cast<float>(raw_data[sample_offset + (channels == 1 ? 0 : 1)]) / SHORT_MAX : 0.0f;
		}
	}
}

sound_stream::sound_stream(const char* filename, sound_effect* effect) : source(0), fp(0), effect(effect)
{
	fopen_s(&fp, filename, "rb");
	assert(fp && "sound_stream::open : 'fopen_s' error");

	int ov_e = ov_open(fp, &vf, NULL, 0);
	assert(ov_e == 0 && "Failed to initialize an OggVorbis_File structure");

	info = ov_info(&vf, -1);

	raw_data = new ALshort[static_cast<size_t>(queue_buffer_samples) * info->channels];
	cooked_data = new ALshort[static_cast<size_t>(queue_buffer_samples) * 2];

	input_samples[0] = new ALfloat[queue_buffer_samples];
	input_samples[1] = new ALfloat[queue_buffer_samples];

	output_samples[0] = new ALfloat[queue_buffer_samples];
	output_samples[1] = new ALfloat[queue_buffer_samples];

	alGenSources(1, &source);
	alGenBuffers(queue_buffers, buffers);
	for (int i = 0; i < queue_buffers; ++i)
	{
		stream(buffers[i]);
	}
	alSourceQueueBuffers(source, queue_buffers, buffers);

	alSourcef(source, AL_GAIN, 0.02f);
	alSource3f(source, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	alSource3f(source, AL_DIRECTION, 0.0f, 0.0f, 0.0f);
	alSourcef(source, AL_ROLLOFF_FACTOR, 0.0f);
	alSourcei(source, AL_SOURCE_RELATIVE, AL_TRUE);

	streaming_mutex.lock();
	streaming_thread = std::make_unique<std::thread>([&]() {
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
		while (!streaming_mutex.try_lock())
		{
			update();
		}
		streaming_mutex.unlock();
	}
	);
}
sound_stream::~sound_stream()
{
	if (streaming_thread)
	{
		streaming_mutex.unlock();
		streaming_thread->join();
	}

	ALint queued;
	if (alIsSource(source))
	{
		alSourceStop(source);
		alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
		while (queued--)
		{
			ALuint buffer;
			alSourceUnqueueBuffers(source, 1, &buffer);
		}
		alDeleteBuffers(1, buffers);
		alDeleteSources(1, &source); source = 0;
	}
	if (fp)
	{
		ov_clear(&vf);
		fclose(fp);
		fp = 0;
	}

	delete[] raw_data;
	delete[] cooked_data;

	delete[] input_samples[0];
	delete[] input_samples[1];

	delete[] output_samples[0];
	delete[] output_samples[1];
}
void sound_stream::update()
{
	if (alIsSource(source))
	{
		ALint processed;
		alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
		while (processed-- > 0)
		{
			ALuint buffer;
			alSourceUnqueueBuffers(source, 1, &buffer);
			stream(buffer);
			alSourceQueueBuffers(source, 1, &buffer);
		}
	}
}
void sound_stream::stream(ALuint buffer)
{
	long raw_data_bytes = queue_buffer_samples * info->channels * sizeof(ALshort);
	long total_bytes_read = 0L;
	while (total_bytes_read < raw_data_bytes)
	{
		int current_section;
		long bytes_read = ov_read(&vf, &(reinterpret_cast<char*>(raw_data)[total_bytes_read]), raw_data_bytes - total_bytes_read, 0, 2, 1, &current_section);
		if (bytes_read > 0)
		{
			total_bytes_read += bytes_read;
		}
		else if (bytes_read == 0)
		{
			ov_pcm_seek(&vf, 0);
		}
		else
		{
			assert(false && "ov_read error");
			break;
		}
	}

	for (size_t sample = 0; sample < queue_buffer_samples; ++sample)
	{
		size_t raw_data_offset = sample * info->channels;
		input_samples[0][sample] = static_cast<float>(raw_data[raw_data_offset + 0]) / SHORT_MAX;
		input_samples[1][sample] = static_cast<float>(raw_data[raw_data_offset + (info->channels == 1 ? 0 : 1)]) / SHORT_MAX;
	}

	assert(effect && "");
	effect->process(const_cast<const float**>(input_samples), output_samples, queue_buffer_samples, info->rate);

	for (size_t sample = 0; sample < queue_buffer_samples; ++sample)
	{
		cooked_data[sample * 2 + 0] = static_cast<ALshort>(output_samples[0][sample] * SHORT_MAX);
		cooked_data[sample * 2 + 1] = static_cast<ALshort>(output_samples[1][sample] * SHORT_MAX);
	}
	alBufferData(buffer, AL_FORMAT_STEREO16, cooked_data, total_bytes_read * (info->channels == 1 ? 2 : 1), info->rate);
}
