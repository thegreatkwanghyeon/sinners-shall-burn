#include "particleengine.h"

ParticleEngine::ParticleEngine(std::vector<sf::Texture> textureList, sf::Vector2f location, int numberOfParticles){
	this->location = location;
	this->textureList = textureList;
	this->numberOfParticles = numberOfParticles;	

	randomNumber = 0;
}

void ParticleEngine::setLocation(sf::Vector2f location){
	this->location = location;
}

void ParticleEngine::init(){
	for(int i=0;i<numberOfParticles;i++){
		particleList.push_back(generateNewParticle());
	}
}

Particle* ParticleEngine::generateNewParticle(){

	srand(GetTickCount() + randomNumber);
	sf::Texture tmpTexture = textureList[(rand()%((textureList.size() - 1)+1) + 1)-1];
	sf::Vector2f tmpPosition = location;
	sf::Vector2f tmpVelocity = sf::Vector2f(1.f * (rand()%((2-1)+1)+1), 1.f * (rand()%((2-1)+1)+1));
	float tmpAngle = 1.f * ((rand()%((361-1)+1) + 1)-1);
	sf::Color tmpColor = sf::Color((rand()%(((256-1)+1)+1)-1), (rand()%(((256-1)+1)+1)-1), (rand()%(((256-1)+1)+1)-1), 255);
	int tmpLife = 200;

	++randomNumber;

	return new Particle(tmpTexture, tmpPosition, tmpVelocity, tmpAngle, tmpColor, tmpLife);
}

void ParticleEngine::update(){

	for(int currentParticle = 0;currentParticle < particleList.size();currentParticle++){

		particleList[currentParticle]->update();

		if(particleList[currentParticle]->getLife() <= 0){

			delete particleList[currentParticle];
			particleList.erase(particleList.begin() + currentParticle);
			--currentParticle;

		}

	}
}

void ParticleEngine::draw(sf::RenderWindow &window){
	for(int currnetParticle = 0;currnetParticle < particleList.size();currnetParticle++){
		particleList[currnetParticle]->draw(window);
	}
}
