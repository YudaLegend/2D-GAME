#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <algorithm>


#define SCREEN_X 16
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25

#define LEVEL1 "levels/level01.txt"
#define LEVEL2 "levels/level1-2.txt"

Scene::Scene()
{
	map = NULL;
	player = NULL;
	mapBackground = NULL;
	enemies.clear();
	int_blocks.clear();
	jmoneys.clear();
	mush.clear();
	destruit_blocks.clear();
	star.clear();
	coins.clear();

}

Scene::~Scene()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	if (mapBackground != NULL)
		delete mapBackground;
	if (enemies.size() != 0)
		enemies.clear();
	if (int_blocks.size() != 0)
		int_blocks.clear();
	if (jmoneys.size() != 0)
		jmoneys.clear();
	if (mush.size() != 0)
		mush.clear();
	if (coins.size() != 0)
		coins.clear();
	if (star.size() != 0)
		star.clear();
	if (destruit_blocks.size() != 0)
		destruit_blocks.clear();
}

void Scene::clear() {
	map = NULL;
	player = NULL;
	mapBackground = NULL;
	enemies.clear();
	int_blocks.clear();
	jmoneys.clear();
	mush.clear();
	coins.clear();
	star.clear();
	destruit_blocks.clear();
}
void Scene::initMap(int level) {
	if (level == 1) {
		map = TileMap::createTileMap(LEVEL1, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		map->setScene(this);
		mapBackground = BackgroundMap::createBackgroundMap(LEVEL1, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	}
	else if (level == 2){
		map = TileMap::createTileMap(LEVEL2, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		map->setScene(this);
		mapBackground = BackgroundMap::createBackgroundMap(LEVEL2, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	}
}

void Scene::reshape(int w, int h) {
	float scale = h / 480.f;
	float offset = (w - 8 * 16 * scale) / 2;

	projection = glm::ortho(16.f, w - offset, 240.f+16.f, 16.f);
	projection = glm::scale(projection, glm::vec3(scale));
}


bool Scene::initIntBlocks() {
	if (this->fileName == LEVEL1) {
		for (int i = 0; i < pos_blocks.size(); ++i) {
			InterrogantBlock* block = new InterrogantBlock();
			block->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			block->setPosition(pos_blocks[i] * 16);
			block->setSize(glm::vec2(16, 16));
			int_blocks.push_back(block);
		}
	}
	else {
		for (int i = 0; i < pos_blocks2.size(); ++i) {
			InterrogantBlock* block = new InterrogantBlock();
			block->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			block->setPosition(pos_blocks2[i] * 16);
			block->setSize(glm::vec2(16, 16));
			int_blocks.push_back(block);
		}
	}


	return true;
}
bool Scene::initStar() {
	for (int i = 0; i < pos_star.size(); ++i) {
		Star* s = new Star();
		s->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		s->setPosition(pos_star[i] * 16);
		s->setSize(glm::vec2(16, 16));
		s->setCollisionMap(map);
		star.push_back(s);
	}
	return true;
}
bool Scene::initJmoneys() {


	if (this->fileName == LEVEL1) {
		for (int i = 0; i < pos_jmoneys.size(); ++i) {
			JumpingMoney* jcoins = new JumpingMoney();
			jcoins->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			jcoins->setPosition((pos_jmoneys[i] * 16) + glm::ivec2(4, 0));
			jcoins->setSize(glm::vec2(16, 16));
			jmoneys.push_back(jcoins);
		}
	}
	else {
		for (int i = 0; i < pos_jmoneys2.size(); ++i) {
			JumpingMoney* jcoins = new JumpingMoney();
			jcoins->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			jcoins->setPosition((pos_jmoneys2[i] * 16) + glm::ivec2(4, 0));
			jcoins->setSize(glm::vec2(16, 16));
			jmoneys.push_back(jcoins);
		}
	}


	return true;
}

void Scene::init(int level)
{

	initShaders();
	if (level == 1)
		this->fileName = LEVEL1;
	else if (level == 2)
		this->fileName = LEVEL2;
	initMap(level);

	

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	//player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setPosition(glm::vec2(10, 50));

	player->setTileMap(map);
	scroll = -1.f;
	if (this->fileName == LEVEL1) {
		initMush();
		initJmoneys();
		initIntBlocks();
		initDetrui_block();
		initStar();
		initCoins();
	}
	else {
		this->clear();
		initShaders();
		if (level == 1)
			this->fileName = LEVEL1;
		else if (level == 2)
			this->fileName = LEVEL2;
		initMap(level);



		player = new Player();
		player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		//player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
		player->setPosition(glm::vec2(10, 50));

		player->setTileMap(map);
		scroll = -1.f;
		initMush2();
		initJmoneys2();
		int_blocks.resize(0);
		initIntBlocks2();
		initStar2();
		initCoins2();
	}
	initEnemies();
	initGameUI();
	projection = glm::ortho(16.f, float(SCREEN_WIDTH)+16.f, float(SCREEN_HEIGHT)+16.f, 16.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;

	player->update(deltaTime,scroll);
	glm::ivec2 playerpos = player->getPosition();
	if (playerpos.y > 230) {
		Game::instance().mediaPlayer->dieSound();
		Game::instance().die(0, 0, 1, 150);
	}

	//Scroll la camara
	if (playerpos.x >= ( -scroll + 129.f) && -scroll < 3072) {
		scroll = (-playerpos.x + 128.f)+1;
	}

	if (this->fileName == LEVEL2) {
		if (playerpos.x >= (-scroll + 129.f) && -scroll < 3238) {
			scroll = (-playerpos.x + 128.f) + 1;
		}
	}

	if (playerpos.x >= 3160 && playerpos.x <= 3163 && player->level1end == 0 && this->fileName == LEVEL1) { player->level1end = 1;  Game::instance().mediaPlayer->winSound();  gameUI->setFinish();
	}
	else if (playerpos.x >= 3414 && playerpos.x <= 3417 && player->level2end == 0 && this->fileName == LEVEL2) {
		player->level2end = 1; Game::instance().mediaPlayer->winSound(); gameUI->setFinish();
	}
	else if (playerpos.x >= 904 && playerpos.x <= 919 && this->fileName == LEVEL1 && player->middle) {
		player->tubetransport1(); Game::instance().mediaPlayer->pipeSound(); scroll = -3376.00000;
	}
	else if (playerpos.x >= 3569 && this->fileName == LEVEL1) { player->tubetransport2(); 
		Game::instance().mediaPlayer->pipeSound();
		glm::ivec2 playerpos = player->getPosition();
		scroll = (-playerpos.x + 128.f) + 1;
	}
	else if (playerpos.x >= 2640 && playerpos.x <= 2644 && this->fileName == LEVEL2) {
		player->tubetransport3(); Game::instance().mediaPlayer->pipeSound(); scroll = -3072;
	}
	//else if (playerpos.x >= 3160 && player->level1end == 0 && this->fileName == LEVEL1) { player->tubetransport3(); }
	//else if (playerpos.x >= 3160 && player->level1end == 0 && this->fileName == LEVEL1) { player->tubetransport4(); }
	//else if (playerpos.x >= 3160 && player->level1end == 0 && this->fileName == LEVEL1) { player->tubetransport5(); }
	//else if (playerpos.x >= 3160 && player->level1end == 0 && this->fileName == LEVEL1) { player->tubetransport6(); }
	player->update(deltaTime, scroll);

	//update bloques interrogantes
	for (unsigned int i = 0; i < int_blocks.size(); ++i) {
		int_blocks[i]->update(deltaTime, scroll);
	}
	for (unsigned int i = 0; i < mush.size(); ++i) {

		if (mush[i]->isActivated()) {
			mush[i]->update(deltaTime, scroll);
		}
		if (mush[i]->touchMario(playerpos, player->getMarioMode())) {
			//player->setStartMode(true);
			Game::instance().mediaPlayer->powerupSound();
			gameUI->updateScore(500);
			if (!player->getMarioMode()) {
				player->setBig();
				player->convertion();
			}
			mush[i]->setActivate(false);
			mush[i]->setPosition(glm::ivec2(0, 0));
		}
		if (player->collisionInt()) {

			glm::ivec2 blockpos = player->posInt();
			glm::ivec2 mushPos = mush[i]->getPosition();

			if (blockpos == (mushPos / 16)) {
				Game::instance().mediaPlayer->powerup_appearsSound();
				mush[i]->setActivate(true);
				mush[i]->setHit();
			}
		}
	}
	//Jumping moneys
	for (unsigned int i = 0; i < jmoneys.size(); ++i) {
		jmoneys[i]->update(deltaTime, scroll);

		if (player->collisionInt() && jmoneys[i]->MarioDown(playerpos) && !jmoneys[i]->gone) {
			jmoneys[i]->gone = true;
			Game::instance().mediaPlayer->coinSound();
			gameUI->updateCoins();
			gameUI->updateScore(100);
		}
		if (jmoneys[i]->needDelete()) {
			jmoneys.erase(std::remove(jmoneys.begin(), jmoneys.end(), jmoneys[i]), jmoneys.end());
		}
	}

	//Colision con los bloques interrogantes
	if (player->collisionInt()) {
		glm::ivec2 blockpos = player->posInt();
		for (unsigned int i = 0; i < int_blocks.size(); ++i) {
			if (! int_blocks[i] ->isUnlocked() ) {
				int_blocks[i]->unlock(blockpos);
			}	
		}	
	}
	// Para que los monstruos no se aparezcan cuando el mario este muy lejos
	for (unsigned int i = 0; i < enemies.size(); ++i) {
		glm::ivec2 enemypos = enemies[i]->getPosition();
		if (enemypos.x <= (-scroll + 320)) { //Aqui 272 son pixeles
			enemies[i]->update(deltaTime, scroll);

			if (enemies[i]->enemyKillMario(playerpos, player->getMarioMode()) && !player->getStarMode()) {
				if (player->getMarioMode()) { player->setSmall(); }
				else {
					Game::instance().mediaPlayer->dieSound();
					Game::instance().die(0, 0, 1, 150);
					//player->setStartMode();
				}

			}

			if (enemies[i]->MarioUp(playerpos, &playerpos.y, player->getMarioMode())) {
				gameUI->updateScore(100);
				player->setJump();
				
			}
			if ((enemies[i]->enemyKillMario(playerpos, player->getMarioMode()) && player->getStarMode())) { 
				enemies[i]->setDeathCounter(); 
				gameUI->updateScore(100);
			}
			if (enemies[i]->isDead()) {
				enemies.erase(std::remove(enemies.begin(), enemies.end(), enemies[i]), enemies.end());
			}
		}
		
	}
	for (unsigned int i = 0; i < star.size(); ++i) {

		if (star[i]->isActivated()) {
			star[i]->update(deltaTime, scroll);

		}
		if (star[i]->touchMario(playerpos, player->getMarioMode())) {
			//player->setStartMode(true);
			player->setStartMode();
			star[i]->setActivate(false);
			star[i]->setPosition(glm::ivec2(0, 0));
		}
		if (player->collisionInt()) {
			glm::ivec2 blockpos = player->posInt();
			glm::ivec2 StarPos = star[i]->getPosition();

			if (blockpos == (StarPos / 16)) {
				star[i]->setActivate(true);
				star[i]->setHit();
			}
		}
	}
	if (player->collisionBlock()) {
		glm::ivec2 block = player->posInt();

		for (unsigned int i = 0; i < destruit_blocks.size(); ++i) {
			if (!destruit_blocks[i]->isUnlocked()) {
				destruit_blocks[i]->unlock(block);
			}
		}
	}
	for (int i = 0; i < pos_coins.size(); ++i) {


		coins[i]->update(deltaTime, scroll);
		if (coins[i]->MarioCollide(playerpos, player->getMarioMode())) {
			Game::instance().mediaPlayer->coinSound();
			//player->setStartMode(true);
		}
		if (coins[i]->needDelete()) {
			coins[i]->setPosition(glm::ivec2(0, 0));
		}
	}
	for (unsigned int i = 0; i < destruit_blocks.size(); ++i) {
		destruit_blocks[i]->update(deltaTime, scroll);

		if (destruit_blocks[i]->deadC()) {
			glm::ivec2 dpos = destruit_blocks[i]->getPosition();
			map->setMapTile(dpos / 16);
			destruit_blocks.erase(std::remove(destruit_blocks.begin(), destruit_blocks.end(), destruit_blocks[i]), destruit_blocks.end());
		}
	}
	gameUI->update(deltaTime, scroll);
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(scroll, 0.f, 0.f)) * glm::mat4(1.0f);

	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	mapBackground->render();
	map->render();
	for (unsigned int i = 0; i < pos_coins.size(); ++i) {
		coins[i]->render();
	}
	for (int i = 0; i < destruit_blocks.size(); ++i) {
		destruit_blocks[i]->render();
	}
	for (unsigned int i = 0; i < star.size(); ++i) {
		if (star[i]->isActivated()) {
			star[i]->render();
		}
	}
	for (unsigned int i = 0; i < mush.size(); ++i) {
		if (mush[i]->isActivated()) {
			mush[i]->render();
		}
	}

	for (unsigned int i = 0; i < jmoneys.size(); ++i) {
		jmoneys[i]->render();
	}
	

	for (unsigned int i = 0; i < enemies.size(); ++i) {
		enemies[i]->render();
	}

	for (unsigned int i = 0; i < int_blocks.size(); ++i) {
		int_blocks[i]->render();
	}



	player->render();
	gameUI->render();
}

bool Scene::MarioUpEnemy(Player& p, Enemy& e) {
	return false;
}

bool Scene::initEnemies() {
	ifstream fin;
	string line;
	stringstream sstream;
	fin.open(fileName.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	while (line.compare(0, 3, "END") != 0) {
		bool isMush = line.compare(0, 11, "MUSHMONSTER") == 0;
		bool isTurtle = line.compare(0, 6, "TURTLE") == 0;

		if (isMush || isTurtle) {
			stringstream sstream;
			int n_enemies;
			getline(fin, line);
			sstream.str(line);
			sstream >> n_enemies;
			
			for (int i = 0; i < n_enemies; ++i) {
				stringstream sstream;
				float x_pos = 0;
				float y_pos = 0;
				char orientation;
				getline(fin, line);
				sstream.str(line);
				sstream >> x_pos >> y_pos >> orientation;
				
				if (isMush) {
					MushMonster* mushMons = new MushMonster();
					mushMons->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
					mushMons->setPosition(glm::vec2(x_pos * map->getTileSize(), y_pos * map->getTileSize()));
					mushMons->setOrientation(orientation);
					mushMons->setSize(glm::vec2(16, 16));
					mushMons->setCollisionMap(map);
					enemies.push_back(mushMons);
				}
				else if (isTurtle) {
					Turtle* turtle = new Turtle();
					turtle->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
					turtle->setPosition(glm::vec2(x_pos * map->getTileSize(), y_pos * map->getTileSize()));
					turtle->setOrientation(orientation);
					turtle->setSize(glm::vec2(16, 24));
					turtle->setCollisionMap(map);
					enemies.push_back(turtle);
				}
			}
		}
		getline(fin, line);
	}
	fin.close();
	return true;
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void Scene::initGameUI() {
	gameUI = new GameUI();
	gameUI->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	//gameUI->setPosition(glm::vec2(10, 50));
	gameUI->setTileMap(map);
}

bool Scene::initMush() {
	if (this->fileName == LEVEL1) {
		for (int i = 0; i < pos_mush.size(); ++i) {
			MushRoom* m = new MushRoom();
			m->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			m->setPosition(pos_mush[i] * 16);
			m->setSize(glm::vec2(16, 16));
			m->setCollisionMap(map);
			mush.push_back(m);
		}
	}
	else {
		for (int i = 0; i < pos_mush2.size(); ++i) {
			MushRoom* m = new MushRoom();
			m->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			m->setPosition(pos_mush2[i] * 16);
			m->setSize(glm::vec2(16, 16));
			m->setCollisionMap(map);
			mush.push_back(m);
		}
	}

	return true;
}

bool Scene::initDetrui_block() {
	for (int i = 0; i < pos_destru_blocks.size(); ++i) {
		Block* b = new Block();
		b->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		b->setPosition(pos_destru_blocks[i] * 16);
		b->setSize(glm::vec2(16, 16));
		destruit_blocks.push_back(b);
	}
	return true;
}

bool Scene::initCoins() {
	if (this->fileName == LEVEL1) {
		for (int i = 0; i < pos_coins.size(); ++i) {

			Coins* c = new Coins();
			c->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			c->setPosition(pos_coins[i] * 16);
			c->setSize(glm::vec2(16, 16));
			coins.push_back(c);

		}
	}
	else {
		for (int i = 0; i < pos_coins2.size(); ++i) {

			Coins* c = new Coins();
			c->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			c->setPosition(pos_coins2[i] * 16);
			c->setSize(glm::vec2(16, 16));
			coins.push_back(c);

		}
	}

	return true;

}

bool Scene::initStar2() {
	for (int i = 0; i < pos_star2.size(); ++i) {
		Star* s = new Star();
		s->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		s->setPosition(pos_star2[i] * 16);
		s->setSize(glm::vec2(16, 16));
		s->setCollisionMap(map);
		star.push_back(s);
	}
	return true;
}

bool Scene::initCoins2() {
	for (int i = 0; i < pos_coins2.size(); ++i) {


		Coins* c = new Coins();
		c->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		c->setPosition(pos_coins2[i] * 16);
		c->setSize(glm::vec2(16, 16));
		coins.push_back(c);
	}
	return true;

}
bool Scene::initMush2() {
	for (int i = 0; i < pos_mush2.size(); ++i) {
		MushRoom* m = new MushRoom();
		m->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		m->setPosition(pos_mush2[i] * 16);
		m->setSize(glm::vec2(16, 16));
		m->setCollisionMap(map);
		mush.push_back(m);
	}
	return true;
}

bool Scene::initIntBlocks2() {

	for (int i = 0; i < pos_blocks2.size(); ++i) {
		InterrogantBlock* block = new InterrogantBlock();
		block->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		block->setPosition(pos_blocks2[i] * 16);
		block->setSize(glm::vec2(16, 16));
		int_blocks.push_back(block);
	}

	return true;
}

bool Scene::initJmoneys2() {

	for (int i = 0; i < pos_jmoneys2.size(); ++i) {
		JumpingMoney* jcoins = new JumpingMoney();
		jcoins->init(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		jcoins->setPosition((pos_jmoneys2[i] * 16) + glm::ivec2(4, 0));
		jcoins->setSize(glm::vec2(16, 16));
		jmoneys.push_back(jcoins);
	}

	return true;
}