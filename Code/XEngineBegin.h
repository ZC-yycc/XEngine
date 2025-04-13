#ifndef WORLDCONSTRUCTOR_H
#define WORLDCONSTRUCTOR_H

class WorldConstructor
{
	friend int main();
private:
	void operator=(WorldConstructor&) = delete;
	WorldConstructor(const WorldConstructor& wc) = delete;
	WorldConstructor();
};
#endif
