#include <assimp\cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <gl\GLU.h>

#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 



class Camera {
	static aiVector3D zero, yaxis, zaxis;
public:
	aiVector3D position;
	aiVector3D forward;
	aiVector3D up;

	float forwardSpeed;
	float roationSpeed;

	Camera() :forwardSpeed(0.4f), roationSpeed(0.2f) {}

	void Init(aiVector3D& p = zero, aiVector3D& f = zaxis, aiVector3D& u = yaxis) {
		position = p;
		forward = f;
		up = u;

	}

	void Update(sf::Event e) {//respond to keyboard events
		if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::D)) {
			MoveLeftRight(1);
		}

		if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::A)) {
			MoveLeftRight(-1);
		}

		if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::W)) {
			MoveForwardBack(1);
		}
		if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::S)) {
			MoveForwardBack(-1);
		}

		if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Q)) {
			MoveUpDown(1);
		}
		if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::E)) {
			MoveUpDown(-1);
		}

		if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Right)) {
			TurnRightLeft(-1);
		}
		if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Left)) {
			TurnRightLeft(1);
		}
		if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Up)) {
			TurnUpDown(1);
		}
		if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Down)) {
			TurnUpDown(-1);
		}

	}
	void MoveLeftRight(int dir) { 
		aiVector3D right = forward^up;
		right.Normalize();
		position += (right*(forwardSpeed*dir));
	}

	void MoveUpDown(int dir) { 
		position += (up*(forwardSpeed*dir));
	}

	void MoveForwardBack(int dir) {
		position += (forward*(forwardSpeed*dir));
	}

	void TurnRightLeft(int dir) { 
		aiMatrix3x3 rotate;
		aiMatrix3x3::Rotation(dir*roationSpeed, up, rotate);
		forward *= rotate;
	}

	void TurnUpDown(int dir) {
		aiMatrix3x3 rotate;
		aiVector3D right = forward^up;
		right.Normalize();
		aiMatrix3x3::Rotation(dir*roationSpeed, right, rotate);
		forward *= rotate;
		up *= rotate;
	}

	void ViewingTransform() {
		aiVector3D center = position + forward;
		gluLookAt(position.x, position.y, position.z,
			center.x, center.y, center.z, 
			up.x, up.y, up.z); 
	}

};


aiVector3D Camera::zero(0.0f);
aiVector3D Camera::yaxis(0.0f, 1.0f, 0.0f);
aiVector3D Camera::zaxis(0.0f, 0.0f, -1.0f);