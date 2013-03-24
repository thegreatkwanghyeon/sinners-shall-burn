#ifndef __dialog__
#define __dialog__

#include "windowentity.h"
#include "tinyxml.h"
#include "global.h"

class Dialog : public WindowEntity {
	private:
		unsigned int windowWidth;
		unsigned int windowHeight;
		unsigned int dialogHeight;
		unsigned int currentScriptCursor;
		unsigned int currentScriptNumber;

		sf::Text script;
		sf::Text name;
		sf::Font font;
		std::wstring wStrScript;
		std::wstring wstrName;
		std::vector<std::wstring> wStrScripts;
		std::vector<std::wstring> wStrNames;


		std::wstring Dialog::getEntireDescription (std::wstring _description);
		std::vector<std::wstring> Dialog::splitWords (std::wstring &_str);
		
	public:
		Dialog(const char *_path);
		virtual ~Dialog(){}
		virtual void update(sf::Event &event);
		virtual void draw(sf::RenderWindow &window);

		void setScript(sf::String _script);
		void setRealScript(const char *_path, unsigned int _code);
};


#endif