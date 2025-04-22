#include "opennt.h"

using namespace Resources;
using namespace ResourceManager;
using namespace Math;
using namespace Systems;

EntityManager* entityManager = EntityManager::getEntityManager();
ComponentManager* componentManager = ComponentManager::getComponentManager();
CameraSystem* cameraSystem = CameraSystem::getCameraSystem();
TextureManager* textureManager = TextureManager::getTextureManager();

int main() {
	//Sets texture path
	textureManager->setTextureFolderPath("../textures");

	/*
	* Ground Entity
	*/

	//Create ground entity
	entityManager->createEntity("ground");

	//Create comopnents
	PositionComponent groundPos;
	groundPos.position = Math::Vec3(0, 0, 0);

	TextureComponent groundTexture;
	groundTexture.name = "ground.png";

	ScaleComponent groundScale;
	groundScale.scales = Math::Vec3(100, 100, 100);

	RotationComponent groundRotation;
	groundRotation.eRotation = Math::Vec3(1.57, 0, 0);

	//Add components
	componentManager->addComponent(groundPos, "ground");
	componentManager->addComponent(groundTexture, "ground");
	componentManager->addComponent(groundScale, "ground");
	componentManager->addComponent(groundRotation, "ground");

	/*
	* Player entity
	*/
	
	//Create entity
	entityManager->createEntity("person");

	//Create components
	PositionComponent personPos;
	personPos.position = Math::Vec3(0, 1, 0);

	ScaleComponent personScale;
	personScale.scales = Math::Vec3(1, 1, 1);

	TextureComponent personTexture;
	personTexture.name = "person.png";

	RotationComponent personRotation;
	personRotation.eRotation = Math::Vec3(0.5, 0, 0);

	MovementComponent personMovement;
	personMovement.movementSpeed = 0.1;

	//Add components
	componentManager->addComponent(personPos, "person");
	componentManager->addComponent(personTexture, "person");
	componentManager->addComponent(personRotation, "person");
	componentManager->addComponent(personScale, "person");
	componentManager->addComponent(personMovement, "person");

	/*
	* Tree entity
	*/
	//Create entity
	entityManager->createEntity("tree");

	//Create components
	PositionComponent treePos;
	treePos.position = Math::Vec3(-1, 1, 2);

	ScaleComponent treeScale;
	treeScale.scales = Math::Vec3(1, 1, 1);

	TextureComponent treeTexture;
	treeTexture.name = "tree.jpg";

	RotationComponent treeRotation;
	treeRotation.eRotation = Math::Vec3(0.5, 0, 0);

	//Add components
	componentManager->addComponent(treePos, "tree");
	componentManager->addComponent(treeScale, "tree");
	componentManager->addComponent(treeTexture, "tree");
	componentManager->addComponent(treeRotation, "tree");

	/*
	* Light entity
	*/
	entityManager->createEntity("light");

	//Create components
	LightSourceComponent light;
	light.lightColor = Vec3(1, 0.0, 0.0);
	light.lightPos = Vec3(0.0, 2.0, 0.0);

	//Add compnents
	componentManager->addComponent(light, "light");

	/*
	* Camera setup
	*/

	cameraSystem->setEntity("person");
	cameraSystem->setRelativePosition(Math::Vec3(0, 4, 5));

	openNT_init();
}

void gameLoop() {
	//Updates light position
	LightSourceComponent& lightComp = componentManager->getComponent<LightSourceComponent>("light");
	PositionComponent& posComp = componentManager->getComponent<PositionComponent>("person");

	lightComp.lightPos = posComp.position + Vec3(0, 0.5, 0);
}
