#include "Input.hpp"

Input::Input(Ogre::RenderWindow *window):
	mCallbackMouseMoved(0),
	mCallbackMousePressed(0),
	mCallbackMouseReleased(0),
	mCallbackKeyPressed(0),
	mCallbackKeyReleased(0),
	mCallbackHeadMoved(0)
{

	Ogre::LogManager::getSingletonPtr()->logMessage("Initializing OIS");

	mWindow = window;

	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	OIS::ParamList pl;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	mInputManager = OIS::InputManager::createInputSystem(pl);

	Ogre::LogManager::getSingletonPtr()->logMessage("OIS Initialized");
	
	Ogre::LogManager::getSingletonPtr()->logMessage("Initializing OVR");
	OVR::System::Init(OVR::Log::ConfigureDefaultLog(OVR::LogMask_All));
	
	Ogre::LogManager::getSingletonPtr()->logMessage("OVR Initialized");

}

Input::~Input(){

	Ogre::LogManager::getSingletonPtr()->logMessage("Destroying OIS");

	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);

	if(mInputManager){

		mInputManager->destroyInputObject(mMouse);
		mInputManager->destroyInputObject(mKeyboard);
		OIS::InputManager::destroyInputSystem(mInputManager);
		mInputManager = 0;

	}

	Ogre::LogManager::getSingletonPtr()->logMessage("OIS Destroyed");

}

void Input::capture(){

	mMouse->capture();
	mKeyboard->capture();
	mSensorFusionDevice->capture();

}

void Input::setMouseListener(
	boost::function<bool (const OIS::MouseEvent&)> callbackMouseMoved,
	boost::function<
		bool (const OIS::MouseEvent&, OIS::MouseButtonID)
	> callbackMousePressed,
	boost::function<
		bool (const OIS::MouseEvent&, OIS::MouseButtonID)
	> callbackMouseReleased
){

	mMouse = static_cast<OIS::Mouse*>(
		mInputManager->createInputObject(OIS::OISMouse, true)
	);
	mCallbackMouseMoved = callbackMouseMoved;
	mCallbackMousePressed = callbackMousePressed;
	mCallbackMouseReleased = callbackMouseReleased;
	mMouse->setEventCallback(this);

}

void Input::setKeyboardListener(
	boost::function<bool (const OIS::KeyEvent&)> callbackKeyPressed,
	boost::function<bool (const OIS::KeyEvent&)> callbackKeyReleased
){

	mKeyboard = static_cast<OIS::Keyboard*>(
		mInputManager->createInputObject(OIS::OISKeyboard, true)
	);
	mCallbackKeyPressed = callbackKeyPressed;
	mCallbackKeyReleased = callbackKeyReleased;
	mKeyboard->setEventCallback(this);

}

void Input::setSensorFusionListener(
	boost::function<bool (const Ogre::Vector3 &evt)> callbackHeadMoved
){

	mSensorFusionDevice = new SensorFusionDevice();
	mCallbackHeadMoved = callbackHeadMoved;
	mSensorFusionDevice->setEventCallback(this);

}

bool Input::mouseMoved(const OIS::MouseEvent &arg){

	if(mCallbackMouseMoved == NULL)
		return true;

	return mCallbackMouseMoved(arg);

}

bool Input::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id){

	if(mCallbackMousePressed == NULL)
		return true;

	return mCallbackMousePressed(arg, id);
}

bool Input::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){

	if(mCallbackMouseReleased == NULL)
		return true;

	return mCallbackMouseReleased(arg, id);
}

bool Input::keyPressed(const OIS::KeyEvent &arg){

	if(mCallbackKeyPressed == NULL)
		return true;
	return mCallbackKeyPressed(arg);

}

bool Input::keyReleased(const OIS::KeyEvent &arg){

	if(mCallbackKeyReleased == NULL)
		return true;
	return mCallbackKeyReleased(arg);

}

bool Input::headMoved(const Ogre::Vector3 &evt){

	if(mCallbackHeadMoved == NULL)
		return true;
	return mCallbackHeadMoved(evt);

}
