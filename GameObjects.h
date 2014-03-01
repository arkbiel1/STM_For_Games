#pragma once

class GameObjects
{
public:
	GameObjects();
	virtual ~GameObjects();
	
	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow & window);
	virtual void Update(float elapsedTime);

	virtual void SetPosition(float x, float y);

	static sf::Vector2f GetPosition2();

	virtual sf::Vector2f GetPosition() const;
	virtual float GetWidth() const;
	virtual float GetHeight() const;

	virtual sf::Rect<float> GetBoundingRect() const;
	virtual bool IsLoaded() const;

protected:
	sf::Sprite& GetSprite();
	//sf::Sprite  _sprite;

private:
	sf::Sprite  _sprite;
	sf::Texture _image;
	std::string _filename;
	bool _isLoaded;
	
};