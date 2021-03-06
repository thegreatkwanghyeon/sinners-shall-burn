#include "dialog.h"

Dialog::Dialog(const char *_path) : WindowEntity(_path){
	visible = false;
	dialogHeight = 150;
	currentScriptCursor = 0;
	currentScriptNumber = 0;

	font.loadFromFile("font/aPinoL.ttf");
	windowWidth = 800;

	script.setFont(font);
	script.setColor(sf::Color(200,200,200,255));
	script.setCharacterSize(19);

	name.setFont(font);
	name.setColor(sf::Color(255,255,255,255));
	name.setCharacterSize(24);
}

void Dialog::setScript(sf::String _script){
	wStrScripts.push_back(getEntireDescription(_script));
}

std::vector<std::wstring> Dialog::splitWords (std::wstring &_str){ //문자열 데이터를 공백 기준으로 나눠준다 
	size_t n = _str.length();
	size_t start, stop;
	std::vector<std::wstring> words;
	start = _str.find_first_not_of(L" ");

	while ((start >= 0) && (start < n)){
		stop = _str.find_first_of(L" ", start);
		if((stop<0) || (stop > n)) 
			stop = n;

		words.push_back(_str.substr(start, stop-start));
		start = _str.find_first_not_of(L" ", stop+1);

	}
	return words;
}

std::wstring Dialog::getEntireDescription (std::wstring _description){ //최종적으로 자동 줄바꿈을 적용한 텍스트 자료를 리턴함.
	std::vector<std::wstring> _words = splitWords(_description);
	std::wstring entireDescription = L"";
	std::vector<std::wstring>::iterator iter = _words.begin();
	std::vector<std::wstring>::iterator iter_end = _words.end();
	int currentLineWidth = 0;
	int lineLimit = windowWidth-(individualTextureHeight*2);

	sf::Text tmpText;
	tmpText.setFont(font);
	tmpText.setCharacterSize(19);

	for(; iter != iter_end; iter++){
		tmpText.setString(*iter + L"  ");
		currentLineWidth += (int)(tmpText.getLocalBounds().width + 7);
		if(currentLineWidth > lineLimit){
			entireDescription += L"\n";
			currentLineWidth = 0;
		}
		entireDescription += (*iter + L" ");
	}

	return entireDescription;
}

void Dialog::setRealScript(const char *_path, unsigned int _code){
	TiXmlDocument xmlScript;
	xmlScript.LoadFile(_path);
	TiXmlElement *scriptNode = xmlScript.FirstChildElement("script");
	TiXmlElement *dialogNode = xmlScript.FirstChildElement("script")->FirstChildElement("dialog");

	visible = true;

	for(; scriptNode; scriptNode = scriptNode->NextSiblingElement()){
		int _tmpCode;
		scriptNode->Attribute("code",&_tmpCode) ;
		if(_tmpCode== _code)
			break;
	}

	dialogNode = scriptNode->FirstChildElement("dialog");
	

	for(; dialogNode; dialogNode = dialogNode->NextSiblingElement()){
		wStrScripts.push_back(getEntireDescription(MTW(dialogNode->ToElement()->GetText())));
		wStrNames.push_back(MTW(dialogNode->Attribute("name")));
	}

}


void Dialog::update(sf::Event &event){
	WindowEntity::setWindowSize(windowWidth-((float)individualTextureHeight*2),150);
	WindowEntity::setPosition(sf::Vector2f(0.0f,(float)windowHeight));
	
	name.setPosition(individualTextureWidth,windowHeight - dialogHeight - individualTextureHeight*1.5);
	script.setPosition(individualTextureWidth,windowHeight - dialogHeight - individualTextureHeight*1.5 + name.getLocalBounds().height + 10);
	WindowEntity::update();


	script.setString(wStrScripts[currentScriptNumber].substr(0,currentScriptCursor));
	name.setString(wStrNames[currentScriptNumber]);

	if(currentScriptCursor<wStrScripts[currentScriptNumber].size())
		currentScriptCursor++;
	//아직 글자가 전부 로딩이 안됐을경우, 계속 로딩시킨다.

	if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Return)){
		if(currentScriptCursor<wStrScripts[currentScriptNumber].size()){
			currentScriptCursor = wStrScripts[currentScriptNumber].size();
		} //아직 글자가 전부 로딩이 안됐을경우, 한번에 다 로딩시킨다.
		else if(currentScriptNumber<wStrScripts.size()-1){
			currentScriptCursor = 0;
			currentScriptNumber++;
		} //글자가 전부 로딩 됐고, 현재 스크립트 번호가 마지막 스크립트 번호보다 작으면 다음 번호의 스크립트로
		else if(currentScriptNumber==wStrScripts.size()-1){
			visible = false;
		}
	}
}

void Dialog::draw(sf::RenderWindow &window){
	if(visible){
		windowWidth = window.getSize().x;
		windowHeight = window.getSize().y;
		WindowEntity::draw(window);
		window.draw(script);
		window.draw(name);
	}
}