#include "tooltip.h"

Tooltip::Tooltip(const char *_path) : WindowEntity(_path){
	font.loadFromFile("font/spike.ttf");
}

std::vector<std::wstring> Tooltip::splitWords (std::wstring &_str){ //description ���ڿ� �����͸� ���� �������� �����ش� 
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

std::wstring Tooltip::getEntireDescription (std::wstring _description){ //���������� �ڵ� �ٹٲ��� ������ �ؽ�Ʈ �ڷḦ ������.
	std::vector<std::wstring> _words = splitWords(_description);
	std::wstring entireDescription = L"";
	std::vector<std::wstring>::iterator iter = _words.begin();
	std::vector<std::wstring>::iterator iter_end = _words.end();
	int currentLineWidth = 0;

	sf::Text tmpText;
	tmpText.setFont(font);
	tmpText.setCharacterSize(14);

	for(; iter != iter_end; iter++){
		tmpText.setString(*iter);
		currentLineWidth += tmpText.getLocalBounds().width;
		if(currentLineWidth > lineLimit){
			entireDescription += L"\n";
			currentLineWidth = 0;
		}
		entireDescription += (*iter + L" ");
	}


	return entireDescription;
}

void Tooltip::setTitle(sf::String _stringTitle){ //Ÿ��Ʋ �ؽ�Ʈ ���� 
	title.setString(_stringTitle);
	title.setFont(font);
}

void Tooltip::setDescription(sf::String _stringDescription){ //���� �ؽ�Ʈ ����

	_stringDescription = getEntireDescription(_stringDescription);
 	
	description.setString(_stringDescription);
	description.setFont(font);
	description.setColor(sf::Color(200,200,200));
	description.setCharacterSize(14);

	tooltipWidth = (title.getLocalBounds().width>description.getLocalBounds().width)?title.getLocalBounds().width:description.getLocalBounds().width;
	tooltipHeight = title.getLocalBounds().height + description.getLocalBounds().height;
}

void Tooltip::setScope(sf::FloatRect _rect){ //hoverRect �� ���⼭ ��� ���콺�� �÷��� �� ������ ��Ÿ���°�? �̰� ���� 
	hoverRect = _rect;
}

void Tooltip::setLineBreak(int _lineLimit){
	lineLimit = _lineLimit;
}



void Tooltip::setTooltip(sf::String _title, sf::String _description, sf::FloatRect _rect, int _lineLimit){

	setLineBreak(_lineLimit);
	setScope(_rect);
	setTitle(_title);
	setDescription(_description);
	WindowEntity::setWindowSize((title.getLocalBounds().width>description.getLocalBounds().width)?title.getLocalBounds().width:description.getLocalBounds().width,title.getLocalBounds().height + description.getLocalBounds().height);
}

void Tooltip::update(){
	WindowEntity::update();
	title.setPosition(sprite[Center].getPosition());
	description.setPosition(sprite[Center].getPosition().x, sprite[Center].getPosition().y+title.getLocalBounds().height+5);
}

void Tooltip::draw(sf::RenderWindow &window){
	mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
	WindowEntity::setPosition(mousePosition);
	

	if(hoverRect.contains(mousePosition)){
		WindowEntity::draw(window);
		window.draw(title);
		window.draw(description);
	}
}