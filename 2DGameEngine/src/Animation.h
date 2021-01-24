#pragma once

class Animation
{
	// FUNCTIONS
public:
	Animation() {};
	Animation(unsigned int index, unsigned int numFrames, unsigned int animSpeed);

private:

	// VARS
public:
	unsigned int index;
	unsigned int numFrames;
	unsigned int animationSpeed;

private:

};