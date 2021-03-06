/*
This source file is part of pairOculus, a student project aiming at creating a
simple 3D multiplayer game for the Oculus Rift.

Repository can be found here : https://github.com/Target6/pairOculus

Copyright (c) 2013 Target6

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "PlayerAnimation.hpp"

PlayerAnimation::PlayerAnimation(Ogre::SceneManager *sceneMgr, Ogre::Entity *entity) :
	mSceneMgr(sceneMgr),
	mEntity(entity) {
	mPlayerAnimationState = NULL;
	// Controle bones individualy
    Ogre::Bone* bHead = mEntity->getSkeleton()->getBone("HEAD");
    bHead->setManuallyControlled(true);
	Ogre::Bone* bHipRight = mEntity->getSkeleton()->getBone("HIP_RIGHT");
	bHipRight->setManuallyControlled(true);
	Ogre::Bone* bHipLeft = mEntity->getSkeleton()->getBone("HIP_LEFT");
	bHipLeft->setManuallyControlled(true);
	Ogre::Bone* bKneeRight = mEntity->getSkeleton()->getBone("KNEE_RIGHT");
	bKneeRight->setManuallyControlled(true);
	Ogre::Bone* bKneeLeft = mEntity->getSkeleton()->getBone("KNEE_LEFT");
	bKneeLeft->setManuallyControlled(true);
	Ogre::Bone* bShoulderRight = mEntity->getSkeleton()->getBone("SHOULDER_RIGHT");
	bShoulderRight->setManuallyControlled(true);
	Ogre::Bone* bShoulderLeft = mEntity->getSkeleton()->getBone("SHOULDER_LEFT");
	bShoulderLeft->setManuallyControlled(true);
	Ogre::Bone* bElbowRight = mEntity->getSkeleton()->getBone("ELBOW_RIGHT");
	bElbowRight->setManuallyControlled(true);
	Ogre::Bone* bElbowLeft = mEntity->getSkeleton()->getBone("ELBOW_LEFT");
	bElbowLeft->setManuallyControlled(true);

	setupIdleAnimation ();
	setupHeadAnimation ();
	setupRunAnimation ();

	doIdleAnimation ();
}

void PlayerAnimation::setupIdleAnimation () {
	// Setup the animation
	Ogre::Real duration=1.0;
	Ogre::Animation* animation = mSceneMgr->createAnimation(mEntity->getName() + "Idle",duration);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack* tHipRight = animation->createNodeTrack(0,mEntity->getSkeleton()->getBone("HIP_RIGHT"));
	Ogre::NodeAnimationTrack* tHipLeft = animation->createNodeTrack(1,mEntity->getSkeleton()->getBone("HIP_LEFT"));
	Ogre::NodeAnimationTrack* tShoulderRight = animation->createNodeTrack(2,mEntity->getSkeleton()->getBone("SHOULDER_RIGHT"));
	Ogre::NodeAnimationTrack* tShoulderLeft = animation->createNodeTrack(3,mEntity->getSkeleton()->getBone("SHOULDER_LEFT"));

	// Then make the animation
	Ogre::TransformKeyFrame* key;

	// Hip Right
	key = tHipRight->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(20), Ogre::Vector3::UNIT_Z));

	// Hip Left
	key = tHipLeft->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-20), Ogre::Vector3::UNIT_Z));

	// Shoulder Right
	key = tShoulderRight->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(60), Ogre::Vector3::UNIT_Z));

	// Shoulder Left
	key = tShoulderLeft->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-60), Ogre::Vector3::UNIT_Z));

	mSceneMgr->createAnimationState(mEntity->getName() + "Idle");
}

void PlayerAnimation::setupHeadAnimation () {
	// Setup the animation
	Ogre::Real duration=4.0;
	Ogre::Real step=duration/4.0;
	Ogre::Animation* animation = mSceneMgr->createAnimation(mEntity->getName() + "HeadRotate",duration);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0,mEntity->getSkeleton()->getBone("HEAD"));

	// Then make the animation
	Ogre::TransformKeyFrame* key;

	key = track->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_Y));

	key = track->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Y));

	key = track->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_Y));

	key = track->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-90), Ogre::Vector3::UNIT_Y));

	key = track->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_Y));

	mSceneMgr->createAnimationState(mEntity->getName() + "HeadRotate");
}

void PlayerAnimation::setupRunAnimation () {
	// Setup the animation
	Ogre::Real duration=0.75;
	Ogre::Real step=duration/4.0;
	Ogre::Animation* animation = mSceneMgr->createAnimation(mEntity->getName() + "Run",duration);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack* tKneeRight = animation->createNodeTrack(0,mEntity->getSkeleton()->getBone("KNEE_RIGHT"));
	Ogre::NodeAnimationTrack* tHipRight = animation->createNodeTrack(1,mEntity->getSkeleton()->getBone("HIP_RIGHT"));
	Ogre::NodeAnimationTrack* tKneeLeft = animation->createNodeTrack(2,mEntity->getSkeleton()->getBone("KNEE_LEFT"));
	Ogre::NodeAnimationTrack* tHipLeft = animation->createNodeTrack(3,mEntity->getSkeleton()->getBone("HIP_LEFT"));
	Ogre::NodeAnimationTrack* tShoulderRight = animation->createNodeTrack(4,mEntity->getSkeleton()->getBone("SHOULDER_RIGHT"));
	Ogre::NodeAnimationTrack* tShoulderLeft = animation->createNodeTrack(5,mEntity->getSkeleton()->getBone("SHOULDER_LEFT"));
	Ogre::NodeAnimationTrack* tElbowRight = animation->createNodeTrack(6,mEntity->getSkeleton()->getBone("ELBOW_RIGHT"));
	Ogre::NodeAnimationTrack* tElbowLeft = animation->createNodeTrack(7,mEntity->getSkeleton()->getBone("ELBOW_LEFT"));

	// Then make the animation
	Ogre::TransformKeyFrame* key;

	// Knee Right
	key = tKneeRight->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tKneeRight->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(45), Ogre::Vector3::UNIT_X));

	key = tKneeRight->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tKneeRight->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(80), Ogre::Vector3::UNIT_X));

	key = tKneeRight->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	// Hip Right
	key = tHipRight->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tHipRight->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(45), Ogre::Vector3::UNIT_X));

	key = tHipRight->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tHipRight->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-80), Ogre::Vector3::UNIT_X));

	key = tHipRight->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	// Knee Left
	key = tKneeLeft->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tKneeLeft->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(80), Ogre::Vector3::UNIT_X));

	key = tKneeLeft->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tKneeLeft->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(45), Ogre::Vector3::UNIT_X));

	key = tKneeLeft->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	// Hip Right
	key = tHipLeft->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tHipLeft->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-80), Ogre::Vector3::UNIT_X));

	key = tHipLeft->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tHipLeft->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(45), Ogre::Vector3::UNIT_X));

	key = tHipLeft->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	// Shoulder Right
	key = tShoulderRight->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tShoulderRight->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-45), Ogre::Vector3::UNIT_X));

	key = tShoulderRight->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tShoulderRight->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(45), Ogre::Vector3::UNIT_X));

	key = tShoulderRight->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	// Shoulder Left
	key = tShoulderLeft->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tShoulderLeft->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(45), Ogre::Vector3::UNIT_X));

	key = tShoulderLeft->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	key = tShoulderLeft->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-45), Ogre::Vector3::UNIT_X));

	key = tShoulderLeft->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3::UNIT_X));

	// Elbow Right
	key = tElbowRight->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-20), Ogre::Vector3::UNIT_X));

	key = tElbowRight->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-60), Ogre::Vector3::UNIT_X));

	key = tElbowRight->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-20), Ogre::Vector3::UNIT_X));

	key = tElbowRight->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-20), Ogre::Vector3::UNIT_X));

	key = tElbowRight->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-20), Ogre::Vector3::UNIT_X));

	// Elbow Left
	key = tElbowLeft->createNodeKeyFrame(0.0f);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-20), Ogre::Vector3::UNIT_X));

	key = tElbowLeft->createNodeKeyFrame(step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-20), Ogre::Vector3::UNIT_X));

	key = tElbowLeft->createNodeKeyFrame(2.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-20), Ogre::Vector3::UNIT_X));

	key = tElbowLeft->createNodeKeyFrame(3.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-60), Ogre::Vector3::UNIT_X));

	key = tElbowLeft->createNodeKeyFrame(4.0*step);
	key->setRotation(Ogre::Quaternion(Ogre::Degree(-20), Ogre::Vector3::UNIT_X));

	mSceneMgr->createAnimationState(mEntity->getName() + "Run");

}

void PlayerAnimation::doIdleAnimation () {
	mPlayerAnimationState = mSceneMgr->getAnimationState(mEntity->getName() + "Idle");
	mPlayerAnimationState->setEnabled(true);
}

void PlayerAnimation::doHeadAnimation () {
	mPlayerAnimationState = mSceneMgr->getAnimationState(mEntity->getName() + "Head");
	mPlayerAnimationState->setEnabled(true);
	mPlayerAnimationState->setLoop(true);
}

void PlayerAnimation::doRunAnimation () {
	mPlayerAnimationState = mSceneMgr->getAnimationState(mEntity->getName() + "Run");
	mPlayerAnimationState->setEnabled(true);
	mPlayerAnimationState->setLoop(true);
}

void PlayerAnimation::stopAnimation () {
	mPlayerAnimationState->setLoop(false);
	mPlayerAnimationState->setTimePosition(mPlayerAnimationState->getLength());
}

Ogre::AnimationState* PlayerAnimation::getPlayerAnimationState() {return mPlayerAnimationState;}
