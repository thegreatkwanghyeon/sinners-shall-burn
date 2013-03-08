#include "dialog.h"

Dialog::Dialog(const char *_path) : WindowEntity(_path){
	dialogHeight = 150;
	currentScriptCursor = 0;
	currentScriptNumber = 0;
	font.loadFromFile("font/spike.ttf");
	windowWidth = 800;

	script.setFont(font);
	script.setColor(sf::Color(200,200,200,255));
	script.setCharacterSize(19);
}

void Dialog::setScript(sf::String _script){
	wStrScripts.push_back(getEntireDescription(_script));
}

std::vector<std::wstring> Dialog::splitWords (std::wstring &_str){ //���ڿ� �����͸� ���� �������� �����ش� 
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

std::wstring Dialog::getEntireDescription (std::wstring _description){ //���������� �ڵ� �ٹٲ��� ������ �ؽ�Ʈ �ڷḦ ������.
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
		currentLineWidth += (tmpText.getLocalBounds().width + 7);
		if(currentLineWidth > lineLimit){
			entireDescription += L"\n";
			currentLineWidth = 0;
		}
		entireDescription += (*iter + L" ");
	}


	return entireDescription;
}


void Dialog::update(sf::Event &event){
	WindowEntity::setWindowSize(windowWidth-((float)individualTextureHeight*2),150);
	WindowEntity::setPosition(sf::Vector2f(0.0f,(float)windowHeight));
	script.setPosition(individualTextureWidth,windowHeight - dialogHeight - individualTextureHeight*1.5);
	WindowEntity::update();


	script.setString(wStrScripts[currentScriptNumber].substr(0,currentScriptCursor));

	if(currentScriptCursor<wStrScripts[currentScriptNumber].size())
		currentScriptCursor++;
	//���� ���ڰ� ���� �ε��� �ȵ������, ��� �ε���Ų��.

	if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Return)){
		printf("%d < %d\n",currentScriptNumber, wStrScripts.size());
		if(currentScriptCursor<wStrScripts[currentScriptNumber].size()){
			currentScriptCursor = wStrScripts[currentScriptNumber].size();
		} //���� ���ڰ� ���� �ε��� �ȵ������, �ѹ��� �� �ε���Ų��.
		else if(currentScriptNumber<wStrScripts.size()-1){
			currentScriptCursor = 0;
			currentScriptNumber++;
		} //���ڰ� ���� �ε� �ư�, ���� ��ũ��Ʈ ��ȣ�� ������ ��ũ��Ʈ ��ȣ���� ������ ���� ��ȣ�� ��ũ��Ʈ��
		
	}
}

void Dialog::draw(sf::RenderWindow &window){
	windowWidth = window.getSize().x;
	windowHeight = window.getSize().y;
	WindowEntity::draw(window);
	window.draw(script);
}