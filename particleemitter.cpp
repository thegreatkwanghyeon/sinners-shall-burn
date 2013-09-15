#include "particleemitter.h"

ParticleEmitter::ParticleEmitter(int numberOfParticles){

	particleCount = 0;
	tmpElapsedTime = 0;

	for(int i=0;i<numberOfParticles;i++){
		particlePool.push_back(new Particle());
	}

	printf("generated (%d)\n", particlePool.size());
}

ParticleEmitter::~ParticleEmitter(){

}

void ParticleEmitter::setSpeedRange(int min, int max){
	minSpeed = min;
	maxSpeed = max;
}

void ParticleEmitter::setSizeRange(int min, int max){
	minSize = min;
	maxSize = max;
}

void ParticleEmitter::setLifeRange(int min, int max){
	minLife = min;
	maxLife = max;
}

void ParticleEmitter::setAngleRange(int min, int max){
	minAngle = min;
	maxAngle = max;
}

void ParticleEmitter::setEmissionRate(float emissionRate){
	this->emissionRate = emissionRate;
}

void ParticleEmitter::setPositionRange(sf::Vector2i x, sf::Vector2i y){
	minX = x.x;
	maxX = x.y;

	minY = y.x;
	maxY = y.y;
}

bool ParticleEmitter::shouldEmitSomeParticles(sf::Time deltaTime){

	tmpElapsedTime += deltaTime.asSeconds();

	if(particleCount < particlePool.size()){
		if(tmpElapsedTime >= emissionRate){
			tmpElapsedTime = 0;
			return true;
		}
	}

	return false;
}

Particle* ParticleEmitter::getAFreeParticleFromThePool(){
	for(int i=0;i<particlePool.size();i++){
		if(particlePool[i]->getLife() <= 0){
			//printf("free paricle : %d\n", i);
			return particlePool[i];
		}
	}
	return NULL;
}

void ParticleEmitter::setTexture(std::string string){
	tmpTexture.loadFromFile(string);
}

void ParticleEmitter::addParticle(){

	Particle* tmpParticle = getAFreeParticleFromThePool();

	if(tmpParticle != NULL){

		srand(GetTickCount());

		tmpParticle->setAngle(rand()%((maxAngle-minAngle)+1) + minAngle);
		tmpParticle->setLife(rand()%((maxLife-minLife)+1) + minLife);
		tmpParticle->setSpeed(rand()%((maxSpeed-minSpeed)+1) + minSpeed);
		tmpParticle->setSize(rand()%((maxSize-minSize)+1) + minSize);
		tmpParticle->setPosition(sf::Vector2f(rand()%((maxX-minX)+1) + minX, rand()%((maxY-minY)+1) + minY));
		tmpParticle->setTexture(tmpTexture);

		++particleCount;

	}

}

void ParticleEmitter::update(sf::Event &event){

	printf("particleCount : %d\n", particleCount);
	if(shouldEmitSomeParticles(deltaTime)){
		addParticle();
	}

	for(int i=0;i<particleCount;i++){
		particlePool[i]->update(event);
		if(particlePool[i]->getLife() <= 0){
			delete(particlePool[i]);
			particlePool.erase(particlePool.begin() + i);
			--particleCount;
		}
	}

	deltaTime = eTime.restart();

}

void ParticleEmitter::draw(sf::RenderWindow &window){
	for(int i=0;i<particleCount;i++){
		particlePool[i]->draw(window);
	}
}