#ifndef __tooltip__
#define __tooltip__

#include "stdafx.h"
#include "tileset.h"


class Tooltip {

	private:

		enum Position{ //�̰��� �ؽ��ĸ� 9 ��� �Ұ��ε� �� ��ġ�� �˷��ִ°��̴� 
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
		std::vector<std::wstring> splitWords (std::wstring &_str);
		std::wstring getEntireDescription (std::wstring _description);

		void setTitle(sf::String _stringTitle);
		void setDescription(sf::String _stringDescription);
		void setScope(sf::IntRect _rect);
		void setLineBreak(int _lineLimit);
		


	public:
		Tooltip(sf::String _path);
		~Tooltip(){delete tileset;};
		void update();
		void draw(sf::RenderWindow &window);
		void setTooltip(sf::String _title, sf::String _description, sf::IntRect _rect, int _lineLimit);

};

#endif