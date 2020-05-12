#include <string>
#include <iostream>
using namespace std;

class IWeapon {
	string name;
	float damage;
	float speed;

public:
	IWeapon() = default;

	float GetDamage() {
		return damage;
	}
	void SetDamage(float d) {
		damage = d;
	}

	float GetSpeed() {
		return speed;
	}
	void SetSpeed(float s) {
		speed = s;
	}

};

class ISword : public IWeapon {

};
