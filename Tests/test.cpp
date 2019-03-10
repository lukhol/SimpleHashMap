#include "pch.h"

#include "../HashMap/HashMap.h";

TEST(SIZE, MORE_THAN_INITIAL_CAPACITY) {

	HashMap<long, string> map;
	map.put(1, "jeden");
	map.put(2, "dwa");
	map.put(3, "trzy");
	map.put(8, "osiem");
	map.put(11, "jedenascie");
	map.put(22, "dwadziescia dwa");
	map.put(16, "szesnascie");
	map.put(5, "piec");
	map.put(25, "dwadziescia piec");
	map.put(61, "szescdziesiac jeden");
	map.put(15, "pietnascie");
	map.put(0, "zero");

	EXPECT_EQ(map.getSize(), 12);
}

TEST(PDF, EXERCISE) {
	HashMap<long, string> map(10);
	map.put(13, "ala");
	map.put(23, "ola");
	map.remove(13);

	EXPECT_EQ(map.getSize(), 1);
	EXPECT_EQ(map.get(23), "ola");
}

TEST(REMOVING, REMOVING_ADDING) {
	HashMap<long, string> map;
	map.put(1, "jeden");
	map.put(2, "dwa");
	map.put(3, "trzy");
	map.put(8, "osiem");
	map.put(11, "jedenascie");
	map.put(22, "dwadziescia dwa");
	map.put(16, "szesnascie");
	map.put(5, "piec");
	map.put(25, "dwadziescia piec");
	map.put(61, "szescdziesiac jeden");
	map.put(15, "pietnascie");
	map.put(0, "zero");

	map.remove(8);
	map.remove(16);
	map.remove(5);
	map.remove(22);

	EXPECT_EQ(map.getSize(), 8);

	EXPECT_EQ(map.get(2), "dwa");
	EXPECT_EQ(map.get(11), "jedenascie");
	EXPECT_EQ(map.get(3), "trzy");
	EXPECT_EQ(map.get(61), "szescdziesiac jeden");
}

class OwnClass {
private:
	const int x;
	const int y;

public:
	OwnClass() : x(0), y(0) {}
	OwnClass(const int x, const int y) : x(x), y(y) {}
	int getX() const { return x; }
	int getY() const { return y; }

	friend ostream& operator<<(ostream& os, const OwnClass& inst) {
		os << "x: " << inst.getX() << ", y: " << inst.getY();
		return os;
	}

	friend bool operator==(const OwnClass& oc1, const OwnClass& oc2) {
		return oc1.getX() == oc2.getX() && oc1.getY() == oc2.getY();
	}

	friend bool operator!=(const OwnClass& oc1, const OwnClass& oc2) {
		return !(oc1 == oc2);
	}
};

struct OwnClassKeyHash {
	unsigned int operator()(const OwnClass& key) const
	{
		return key.getX() + key.getY() * 12;
	}
};


TEST(OWN_CLASS_KEY, A) {
	HashMap<OwnClass, string, OwnClassKeyHash> map2;
	map2.put(OwnClass(2, 4), "24");
	map2.put(OwnClass(4, 6), "46");
	EXPECT_EQ(map2.getSize(), 2);
	
	map2.remove(OwnClass(2, 4));

	EXPECT_EQ(map2.getSize(), 1);
}