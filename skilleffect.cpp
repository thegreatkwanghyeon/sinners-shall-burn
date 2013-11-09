#include "skilleffect.h"

SkillEffect::~SkillEffect(){
	list<ParticleSystem*>::iterator it_particleList;
	list<Lightning*>::iterator it_lightningList;

	for(it_particleList = particleList.begin(); it_particleList != particleList.end(); it_particleList++){
		delete *it_particleList;
	}

	for(it_lightningList = lightningList.begin(); it_lightningList != lightningList.end(); it_lightningList++){
		delete *it_lightningList;
	}

	particleList.clear();
	lightningList.clear();
}

void SkillEffect::update(){
	list<ParticleSystem*>::iterator it_particleList;
	list<Lightning*>::iterator it_lightningList;

	for(it_particleList = particleList.begin(); it_particleList != particleList.end(); it_particleList++){
		(*it_particleList)->update();
	}

	for(it_lightningList = lightningList.begin(); it_lightningList != lightningList.end(); it_lightningList++){
		(*it_lightningList)->update();
	}
}

void SkillEffect::draw(RenderWindow &window){
	list<ParticleSystem*>::iterator it_particleList;
	list<Lightning*>::iterator it_lightningList;

	for(it_particleList = particleList.begin(); it_particleList != particleList.end(); it_particleList++){
		(*it_particleList)->draw(window);
	}

	for(it_lightningList = lightningList.begin(); it_lightningList != lightningList.end(); it_lightningList++){
		(*it_lightningList)->draw(window);
	}
}

void SkillEffect::addParticle(ParticleSystem* particle){
	particleList.push_back(particle);
}

void SkillEffect::addLightning(Lightning* lightning){
	lightningList.push_back(lightning);
}
