#ifndef _MAESTRO_BOUNDS_
#define  _MAESTRO_BOUNDS_

#include <gmtk/gmtk.h>

namespace mae
{
struct Bounds : sf::FloatRect
{
	Bounds() : m_center(), m_Extents() {}

	Bounds(const gm::vec2f center, const gm::vec2f extents)	: m_center(center), m_Extents(extents * 0.5f) {}
	gm::vec2f m_center;
	gm::vec2f m_Extents;
};

}

#endif _MAESTRO_BOUNDS_
