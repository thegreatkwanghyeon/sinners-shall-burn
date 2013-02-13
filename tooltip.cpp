#include "tooltip.h"

Tooltip::Tooltip(sf::String _path) : tooltipWidth(300), tooltipHeight(300){
	tileset = new TileSet();
	texture.loadFromFile(_path);

	individualTextureWidth = texture.getSize().x/3;
	individualTextureHeight = texture.getSize().y/3; //3X3 = 9등분 하기 위한것 

	texture = tileset->tileSet(_path, individualTextureWidth, individualTextureHeight); 

	for(int i=0; i<9; i++){
		sprite[i].setTexture(texture);
		sprite[i].setTextureRect(tileset->getTileSet(i));
	}

	font.loadFromFile("font/spike.ttf");
}

void Tooltip::defineSpriteScales(){ //텍스트 양에 따라서 스프라이트 크기 조절해준다 신경 ㄴㄴ 

	sprite[Top].setScale(((float)tooltipWidth/individualTextureWidth),1);
	sprite[Left].setScale(1,((float)tooltipHeight/individualTextureHeight));
	sprite[Center].setScale(((float)tooltipWidth/individualTextureWidth),((float)tooltipHeight/individualTextureHeight));
	sprite[Right].setScale(1,((float)tooltipHeight/individualTextureHeight));
	sprite[Bottom].setScale(((float)tooltipWidth/individualTextureWidth),1);
}

void Tooltip::defineSpritePositions(){ //9등분한 스프라이트 위치 재배치 신경 ㄴㄴ
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

std::vector<std::string> Tooltip::splitWords (std::string &_str){ //description 문자열 데이터를 공백 기준으로 나눠준다 
	size_t n = _str.length();
	size_t start, stop;
	std::vector<std::string> words;
	start = _str.find_first_not_of(" ");

	while ((start >= 0) && (start < n)){
		stop = _str.find_first_of(" ", start);
		if((stop<0) || (stop > n)) 
			stop = n;

		words.push_back(_str.substr(start, stop-start));
		start = _str.find_first_not_of(" ", stop+1);

	}
	return words;
}

std::string Tooltip::getEntireDescription (std::string _description){ //최종적으로 자동 줄바꿈을 적용한 텍스트 자료를 리턴함.
	std::vector<std::string> _words = splitWords(_description);
	std::string entireDescription = "";
	std::vector<std::string>::iterator iter = _words.begin();
	std::vector<std::string>::iterator iter_end = _words.end();
	int currentLineWidth = 0;

	sf::Text tmpText;
	tmpText.setFont(font);
	tmpText.setCharacterSize(14);

	for(; iter != iter_end; iter++){
		tmpText.setString(*iter);
		currentLineWidth += tmpText.getLocalBounds().width;
		if(currentLineWidth > lineLimit){
			entireDescription += "\n";
			currentLineWidth = 0;
		}
		entireDescription += (*iter + " ");
	}


	return entireDescription;
}

void Tooltip::setTitle(sf::String _stringTitle){ //타이틀 텍스트 셋팅 
	title.setString(_stringTitle);
	title.setFont(font);
}

void Tooltip::setDescription(sf::String _stringDescription){ //설명 텍스트 셋팅

	_stringDescription = getEntireDescription(_stringDescription);

	sf::Utf<8>::toUtf32(_stringDescription.begin(), _stringDescription.end(), _stringDescription.begin());
 	
	description.setString(_stringDescription);
	description.setFont(font);
	description.setColor(sf::Color(200,200,200));
	description.setCharacterSize(14);

	tooltipWidth = (title.getLocalBounds().width>description.getLocalBounds().width)?title.getLocalBounds().width:description.getLocalBounds().width;
	tooltipHeight = title.getLocalBounds().height + description.getLocalBounds().height;
}

void Tooltip::setScope(sf::IntRect _rect){ //hoverRect 는 여기서 어디에 마우스를 올려야 이 툴팁이 나타나는가? 이거 범위 
	hoverRect = _rect;
}

void Tooltip::setLineBreak(int _lineLimit){
	lineLimit = _lineLimit;
}

void Tooltip::setTooltip(sf::String _title, sf::String _description, sf::IntRect _rect, int _lineLimit){

	sf::Utf<8>::toUtf32(_description.begin(), _description.end(), _description.begin());

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