#ifndef CONST_HPP__
#define CONST_HPP__
#pragma once

/***** WORLD SETTINGS *****/

const int worldSizeX = 50; //Plus 1 (because between -25 and 25 with 0)
const int worldSizeY = 50; //Plus 1 (because between -25 and 25 with 0)
const int worldSizeZ = 50; //Plus 1 (because between -25 and 25 with 0)

const int worldMinX = int(-worldSizeX/2);
const int worldMinY = int(-worldSizeY/2);
const int worldMinZ = int(-worldSizeZ/2);

const int worldMaxX = int(worldSizeX/2);
const int worldMaxY = int(worldSizeY/2);
const int worldMaxZ = int(worldSizeZ/2);

const int nbCubesAtStart = (worldSizeX+1)*3*(worldSizeZ+1);


/***** WINDOW SETTINGS *****/

const int windowWidth = 900;
const int windowHeight = 900;


/***** SCENE SETTINGS *****/

const float camViewAngle = 70.f;
const float nearClipPlane = 0.1f;
const float farClipPlane = 100.f;

const int nbLightsMax = 5;

#endif