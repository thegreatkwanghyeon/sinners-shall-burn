#include "particleengine.h"
#include "WELL512a.h"

ParticleEngine::ParticleEngine(std::vector<sf::Texture> textureList, int numberOfParticles){
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

	srand(GetTickCount() + randomNumber+1);
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

	printf("size : %d\n", particleList.size());

	for(int currentParticle = 0;currentParticle < particleList.size();currentParticle++){

		float radian = particleList[currentParticle]->getAngle() * M_PI/180;
		particleList[currentParticle]->setPosition(sf::Vector2f((particleList[currentParticle]->getPosition().x + particleList[currentParticle]->getVelocity().x * cos(radian)), particleList[currentParticle]->getPosition().y + (-1 * (particleList[currentParticle]->getVelocity().y * sin(radian)))));
		particleList[currentParticle]->setLife(particleList[currentParticle]->getLife()-1);

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
