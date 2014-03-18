#include "OculusCamera.hpp"

OculusCamera::OculusCamera(Ogre::Camera *leftCam, Ogre::Camera *rightCam):
	mIPD(0),
	mLeftCamera(0),
	mRightCamera(0),
	mNodePosition(Ogre::Vector3::ZERO),
	mBaseOffset(Ogre::Vector3::ZERO),
	mCameraOffset(Ogre::Vector3::ZERO),
	mStereoConfig(new OVR::Util::Render::StereoConfig())
{

	setLeftCamera(leftCam);
	setRightCamera(rightCam);
	mIPD = mStereoConfig->GetIPD() * 0.5f;
	mBaseOffset.x = mIPD/2;
	mBaseOffset.y = 0.55;
	mBaseOffset.z = 0.75;
	setPosition(mNodePosition);
	applyOffset();

}

OculusCamera::~OculusCamera() {}

void OculusCamera::move(Ogre::Vector3 vec){

	mLeftCamera->move(vec);
	mRightCamera->move(vec);
	mNodePosition += vec;

}

void OculusCamera::yaw(Ogre::Radian ang){

	mLeftCamera->yaw(ang);
	mRightCamera->yaw(ang);
	removeOffset();
	applyOffset();

}

void OculusCamera::pitch(Ogre::Radian ang){

	mLeftCamera->pitch(ang);
	mRightCamera->pitch(ang);
	removeOffset();
	applyOffset();

}

void OculusCamera::roll(Ogre::Radian ang){

	mLeftCamera->roll(ang);
	mRightCamera->roll(ang);
	removeOffset();
	applyOffset();

}

void OculusCamera::setPosition(Ogre::Vector3 pos){

	mLeftCamera->setPosition(pos);
	mRightCamera->setPosition(pos);
	mNodePosition = pos;
	applyOffset();

}

Ogre::Quaternion OculusCamera::getOrientation(){
	return mLeftCamera->getOrientation();
}

void OculusCamera::setOrientation(Ogre::Quaternion ori){

	yaw(ori.getYaw() - mLeftCamera->getOrientation().getYaw());
	pitch(ori.getPitch() - mLeftCamera->getOrientation().getPitch());
	roll(ori.getRoll() - mLeftCamera->getOrientation().getRoll());

}

void OculusCamera::lookAt(Ogre::Vector3 vec){

	removeOffset();
	mLeftCamera->lookAt(vec);
	mRightCamera->lookAt(vec);
	applyOffset();

}
#include <iostream>
void OculusCamera::increaseIPD(){
	mIPD += 0.001/2;
	mBaseOffset.x = mIPD/4;
	std::cout << mIPD << std::endl;
}

void OculusCamera::decreaseIPD(){
	mIPD -= 0.001;
	mBaseOffset.x = mIPD/4;
	std::cout << mIPD << std::endl;
}

void OculusCamera::setCameras(Ogre::Camera *leftCam, Ogre::Camera *rightCam){
	setLeftCamera(leftCam);
	setRightCamera(rightCam);
}

void OculusCamera::setLeftCamera(Ogre::Camera *cam){

	mLeftCamera = cam;

	mLeftCamera->setAspectRatio(mStereoConfig->GetAspect());
	mLeftCamera->setFOVy(Ogre::Radian(mStereoConfig->GetYFOVRadians()));

	Ogre::Matrix4 proj = Ogre::Matrix4::IDENTITY;
	proj.setTrans(Ogre::Vector3(mStereoConfig->GetProjectionCenterOffset(), 0, 0));
	mLeftCamera->setCustomProjectionMatrix(true, proj * mLeftCamera->getProjectionMatrix());

}

void OculusCamera::setRightCamera(Ogre::Camera *cam){

	mRightCamera = cam;

	mRightCamera->setAspectRatio(mStereoConfig->GetAspect());
	mRightCamera->setFOVy(Ogre::Radian(mStereoConfig->GetYFOVRadians()));

	Ogre::Matrix4 proj = Ogre::Matrix4::IDENTITY;
	proj.setTrans(Ogre::Vector3(-mStereoConfig->GetProjectionCenterOffset(), 0, 0));
	mRightCamera->setCustomProjectionMatrix(true, proj * mRightCamera->getProjectionMatrix());

}

Ogre::Camera *OculusCamera::getLeftCamera(){
	return mLeftCamera;
}

Ogre::Camera *OculusCamera::getRightCamera(){
	return mRightCamera;
}

void OculusCamera::removeOffset(){

	mRightCamera->setPosition(mNodePosition);
	mLeftCamera->setPosition(mNodePosition);

}

void OculusCamera::applyOffset(){

	mCameraOffset = Ogre::Vector3::ZERO;
	mCameraOffset = - mRightCamera->getRight() * mBaseOffset.x;
	mCameraOffset = mRightCamera->getUp() * mBaseOffset.y;
	mCameraOffset = mRightCamera->getDirection() * mBaseOffset.z;

	mRightCamera->move(mCameraOffset);
	mCameraOffset += 2 * mRightCamera->getRight() * mBaseOffset.x;
	mLeftCamera->move(mCameraOffset);

}
