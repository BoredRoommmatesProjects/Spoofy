#ifndef _SPOOFY_COMMON_SPOOFYENTITY_HPP_
#define _SPOOFY_COMMON_SPOOFYENTITY_HPP_

#include <vector>

#include "common/IEntity.hpp"


class SpoofyEntity : public IEntity
{
public:
	SpoofyEntity()
    : IEntity(), m_dx(0), m_dy(0), m_health(1), m_reload(0), m_side(0)
    {}
    
    float getEntityDxVelocity() { return m_dx; };
    float getEntityDyVelocity() { return m_dy; };
    int getEntityHealth() { return m_health; };
    int getEntityReload() { return m_reload; };
    int getEntitySide() { return m_side; };

    void setEntityDxVelocity(float a_dxVelocity) { m_dx = a_dxVelocity; };
    void setEntityDyVelocity(float a_dyVelocity) { m_dy = a_dyVelocity; };
    void setEntityHealth(int a_health) { m_health = a_health; };
    void setEntityReload(int a_reload) { m_reload = a_reload; };
    void setEntitySide(int a_side) { m_side = a_side; };

	virtual ~SpoofyEntity() {};

private:

    float m_dx;
	float m_dy;
	int m_health;
	int m_reload;
	int m_side;
};

#endif // !_SPOOFY_COMMON_SPOOFYENTITY_HPP_