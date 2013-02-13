#ifndef __tooltip__
#define __tooltip__

#include <SFML/Graphics.hpp>
#include "tileset.h"
#include <cstdio>

class Tooltip {

	private:

		enum Position{ //이것은 텍스쳐를 9 등분 할것인데 그 위치를 알려주는것이다 
			TopLeft,
			Top,
			TopRight,
			Left,
			Center,
			Right,
			BottomLeft,
			Bottom,
			BottomRight,
		};

		sf::Texture texture;
		sf::Sprite sprite[9];
		sf::Vector2i position;
		sf::Vector2i mousePosition;
		sf::Font font;
		sf::Text title;
		sf::Text description;
		sf::IntRect hoverRect;

		//sf::Unicode::Text titleUnicode;

		TileSet *tileset;

		int tooltipWidth;
		int tooltipHeight;
		int lineLimit;

		int individualTextureWidth;
		int individualTextureHeight;

		void defineSpritePositions();
		void defineSpriteScales();
		std::vector<std::string> splitWords (std::string &_str);
		std::string getEntireDescription (std::string _description);

		void setTitle(sf::String _stringTitle);
		void setDescription(sf::String _stringDescription);
		void setScope(sf::IntRect _rect);
		void setLineBreak(int _lineLimit);
		


	public:
		Tooltip(sf::String _path);
		~Tooltip();
		void update();
		void draw(sf::RenderWindow &window);
		void setTooltip(sf::String _title, sf::String _description, sf::IntRect _rect, int _lineLimit);

};

#endif