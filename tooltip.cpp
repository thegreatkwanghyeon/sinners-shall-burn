#include "tooltip.h"

Tooltip::Tooltip(sf::String _path) : tooltipWidth(300), tooltipHeight(300){
	tileset = new TileSet();
	texture.loadFromFile(_path);

	individualTextureWidth = texture.getSize().x/3;
	individualTextureHeight = texture.getSize().y/3; //3X3 = 9��� �ϱ� ���Ѱ� 

	texture = tileset->tileSet(_path, individualTextureWidth, individualTextureHeight); 

	for(int i=0; i<9; i++){
		sprite[i].setTexture(texture);
		sprite[i].setTextureRect(tileset->getTileSet(i));
	}

	font.loadFromFile("font/spike.ttf");
}

void Tooltip::defineSpriteScales(){ //�ؽ�Ʈ �翡 ���� ��������Ʈ ũ�� �������ش� �Ű� ���� 

	sprite[Top].setScale(((float)tooltipWidth/individualTextureWidth),1);
	sprite[Left].setScale(1,((float)tooltipHeight/individualTextureHeight));
	sprite[Center].setScale(((float)tooltipWidth/individualTextureWidth),((float)tooltipHeight/individualTextureHeight));
	sprite[Right].setScale(1,((float)tooltipHeight/individualTextureHeight));
	sprite[Bottom].setScale(((float)tooltipWidth/individualTextureWidth),1);
}

void Tooltip::defineSpritePositions(){ //9����� ��������Ʈ ��ġ ���ġ �Ű� ����
	position = mousePosition;

	sprite[TopLeft].setPosition(position.x, position.y-(2*individualTextureHeight)-tooltipHeight);
	sprite[Top].setPosition(position.x+individualTextureWidth,position.y-(2*individualTextureHeight)-tooltipHeight);
	sprite[TopRight].setPosition(position.x+individualTextureWidth+tooltipWidth, position.y-(2*individualTextureHeight)-tooltipHeight);

	sprite[Left].setPosition(position.x, position.y- tooltipHeight- individualTextureHeight);
	sprite[Center].setPosition(position.x+individualTextureWidth, position.y- tooltipHeight- individualTextureHeight);
	sprite[Right].setPosition(position.x+individualTextureWidth+tooltipWidth, position.y- tooltipHeight- individualTextureHeight);

	sprite[BottomLeft].setPosition(position.x, position.y-individualTextureHeight);
	sprite[Bottom].setPosition(position.x+individualTextureWidth, position.y-individualTextureHeight);
	sprite[BottomRight].setPosition(position.x+individualTextureWidth+tooltipWidth, position.y-individualTextureHeight);

	title.setPosition(sprite[Center].getPosition());
	description.setPosition(sprite[Center].getPosition().x, sprite[Center].getPosition().y+title.getLocalBounds().height+5);
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

void Tooltip::setScope(sf::IntRect _rect){ //hoverRect �� ���⼭ ��� ���콺�� �÷��� �� ������ ��Ÿ���°�? �̰� ���� 
	hoverRect = _rect;
}

void Tooltip::setLineBreak(int _lineLimit){
	lineLimit = _lineLimit;
}

void Tooltip::setTooltip(sf::String _title, sf::String _description, sf::IntRect _rect, int _lineLimit){

	setLineBreak(_lineLimit);
	setScope(_rect);
	setTitle(_title);
	setDescription(_description);
}

void Tooltip::update(){
	defineSpriteScales();
	defineSpritePositions();
}

void Tooltip::draw(sf::RenderWindow &window){
	mousePosition = sf::Mouse::getPosition(window);

	if(hoverRect.contains(mousePosition)){
		for(int i=0; i<9; i++){
			window.draw(sprite[i]);
		}
		window.draw(title);
		window.draw(description);
	}

}