#include <string>
#include <iostream>
using namespace std;

class IRarityFactory {
public:
	/*
	virtual ISword* CreateSword() const = 0;
	virtual IAxe* CreateAxe() const = 0;
	virtual ISpear* CreateSpear() const = 0;
	virtual IBow* CreateBow() const = 0;
	*/

	virtual void CreateSword() = 0;
	virtual void CreateAxe() = 0;
	virtual void CreateSpear() = 0;
	virtual void CreateBow() = 0;
};

class CommonFactory : public IRarityFactory {
public:
	void CreateSword() {
		cout << "Common Sword created." << endl;
	}
};

class RareFactory {
	void CreateSword() {
		cout << "Rare Sword created." << endl;
	}
};

class EpicFactory {
	void CreateSword() {
		cout << "Epic Sword created." << endl;
	}
};

class LegendaryFactory {
	void CreateSword() {
		cout << "Legendary Sword created." << endl;
	}
};



