#ifndef __Tooltip__
#define __Tooltip__

#include "windowentity.h"

class Tooltip : public WindowEntity {
	private:
		int lineLimit;
		sf::FloatRect hoverRect;
		sf::Vector2f mousePosition;
		sf::Font font;
		sf::Text title;
		sf::Text description;


		std::vector<std::wstring> splitWords (std::wstring &_str);
		std::wstring getEntireDescription (std::wstring _description);
		void setTitle(sf::String _stringTitle);
		void setDescription(sf::String _stringDescription);
		void setScope(sf::FloatRect _rect);
		void setLineBreak(int _lineLimit);

	public:
		Tooltip(const char *_path);
		virtual ~Tooltip(){}
		virtual void update();
		virtual void draw(sf::RenderWindow &window);

		void setTooltip(sf::String _title, sf::String _description, sf::FloatRect _rect, int _lineLimit);


};



#endif