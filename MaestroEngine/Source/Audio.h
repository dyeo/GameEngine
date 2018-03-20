#ifndef _MAESTRO_AUDIO_H_
#define _MAESTRO_AUDIO_H_

#include "System.h"

#include <vector>

namespace mae
{

	class Audio : public System
	{

		friend class Sound;
		friend class Music;

		// methods
	public:

		Audio(Engine *const engine);

		virtual Component *const OnComponentCreate(EntityHandle srcEnt, std::type_index cmpType) override;

		virtual bool OnComponentDestroy(EntityHandle srcEnt, Component *const srcCmp) override;
		
		// members
	private:

		std::vector<Sound *> sounds;
		std::vector<Music *> music;

	};

}

#endif // !_MAESTRO_AUDIO_H_
