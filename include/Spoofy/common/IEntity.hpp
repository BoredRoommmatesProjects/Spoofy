#ifndef _SPOOFY_COMMON_IENTITY_HPP_
#define _SPOOFY_COMMON_IENTITY_HPP_

#include <vector>

#include <SFML/Graphics/Texture.hpp>


class IEntity
{
public:
	IEntity()
    : m_x(0), m_y(0), m_w(0), m_h(0), m_texture(nullptr)
    {}
    
    float getEntityXPose() { return m_x; };
    float getEntityYPose() { return m_y; };

    int getEntityTextureWidth() { return m_w; };
    int getEntityTextureHeight() { return m_h; };

    sf::Texture* getEntityTexture() { return m_texture; };

    void setEntityXPose(float a_xPose) { m_x = a_xPose; };
    void setEntityYPose(float a_yPose) { m_y = a_yPose; };
    void setEntityTextureWidth(int a_width) { m_w = a_width; };
    void setEntityTextureHeight(int a_height) { m_h = a_height; };
    void setEntityTexture(sf::Texture* a_texture) { m_texture = a_texture; };

	virtual ~IEntity() {};

private:

    float m_x;
	float m_y;
	int m_w;
	int m_h;
    sf::Texture* m_texture;
};

#endif // !_SPOOFY_COMMON_IENTITY_HPP_