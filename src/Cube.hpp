#ifndef CUBE_H
#define CUBE_H

#include "Block.hpp"

class Cube : public Block {

	public:
		Cube(
			Ogre::ManualObject *man,
			PrintType print,
			Real px,
			Real py,
			Real pz,
			Real sx = 100.0,
			Real sy = 100.0,
			Real sz = 100.0
		);
		virtual ~Cube();

		virtual void createBlockPoint();
		virtual void createBlockWireframe();
		virtual void createBlockSolid();

	protected:
	private:

};

#endif // CUBE_H
