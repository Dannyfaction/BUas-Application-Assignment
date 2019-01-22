#include "TextureManager.h"

void TextureManager::LoadTextures()
{
	//Player texture and animations is an edited version of this Character https://opengameart.org/content/alternate-lpc-character-sprites-george
	playerTexture.loadFromFile("Textures/George_Edited.png");

	enemyTexture.loadFromFile("Textures/Enemy_EditedV2.0.png");

	//Snowball Sprite found with a google image search https://fr.kisspng.com/png-qt9l43/
	ballTexture.loadFromFile("Textures/Snowball.png");

	//Seamless Background Texture found with a google image search https://sftextures.com/wp-content/plugins/sf-textures-plugin/sf-textures-preview.php?tiling=Seamless&image=https://sftextures.com/wp-content/uploads/2015/01/snow-white-rough-air-fresh-light-frozen-frosty-ground-clear-seamless-texture-256x256.jpg
	backgroundTexture.loadFromFile("Textures/Seamless_Snow.jpg");

	//Wall Texture is an edited version of the following image which was found with a google image search https://www.kisspng.com/png-ice-cube-stock-photography-royalty-free-blue-crush-182395/
	wallTexture.loadFromFile("Textures/Ice_Wall.png");
	wallTexture.setRepeated(true);

	//Heart sprite taken from https://opengameart.org/content/heart-pixel-art
	heartTexture.loadFromFile("Textures/Heart.png");

	//Game over sprite found with a google image search https://pngimage.net/wp-content/uploads/2018/06/game-over-png-2.png
	gameOverTexture.loadFromFile("Textures/Game_Over.png");
}
