#pragma once

#include "Node.h";

using namespace std;

template <typename K>
struct KeyHash {
	unsigned int operator()(const K& key) const
	{
		return static_cast<unsigned int>(key);
	}
};

template <class K, class V, typename F = KeyHash<K>>
class HashMap {

private:
	const int MODULO_VAL = 10;
	F hashFun;

	int size;
	Node<K, V>** tab;
	Node<K, V>* dummyNode;
	int capacity;

public:
	HashMap() {
		size = 0;
		capacity = 10;
		tab = new Node<K, V>*[capacity];
		fillNull();
		dummyNode = new Node<K, V>(-1);
	}

	HashMap(int capacity) {
		size = 0;
		this->capacity = capacity;
		tab = new Node<K, V>*[capacity];
		fillNull();
		dummyNode = new Node<K, V>(-1);
	}

	~HashMap() {
		if(tab != NULL) {
			for (int i = 0; i < capacity; i++) {
				if (tab[i] != NULL) {
					delete tab[i];
					tab[i] = NULL;
				}
			}

			delete tab;
		}
	}
	
	void put(K key, V value) {

		if (size == capacity) {
			increase();
		}

		int searchCount = 0;
		int hashIndex = computeHashIndex(key);
		int start = hashIndex;
		Node<K, V>* node = new Node<K, V>(hashIndex, key, value);

		while (tab[hashIndex] != NULL && tab[hashIndex]->getHash() != -1) {
			hashIndex++;

			if (hashIndex >= capacity) {
				hashIndex = 0;
			}
		}

		if (tab[hashIndex] == NULL || tab[hashIndex]->getHash() == -1) {
			size++;
			tab[hashIndex] = node;
		}
	}

	bool remove(K key) {
		int hashIndex = computeHashIndex(key);
		int start = hashIndex, searchCount = 0;

		if (tab[hashIndex] != NULL && tab[hashIndex]->getKey() == key) {
			removeOnIndex(hashIndex);
			realocate(capacity, capacity);
			return true;
		}

		while (tab[hashIndex] != NULL && tab[hashIndex]->getKey() != key && tab[hashIndex]->getHash() != -1) {
			hashIndex++;

			if (hashIndex == start) {
				return false;
			}

			if (hashIndex == capacity) {
				hashIndex = 0;
			}
		}

		removeOnIndex(hashIndex);
		tidy(hashIndex);

		return true;
	}

	V get(K key) {
		int hashIndex = computeHashIndex(key);
		int start = hashIndex, searchCount = 0;

		while ((tab[hashIndex] != NULL || tab[hashIndex]->getHash() != -1) && tab[hashIndex]->getKey() != key) {
			hashIndex++;
			if (hashIndex == start) {
				throw "Not found";
			}

			if (hashIndex == capacity) {
				hashIndex = 0;
			}
		}

		if (tab[hashIndex] == NULL) {
			throw "Not found element";
		}

		return tab[hashIndex]->getValue();
	}

	void clear() {
		for (int i = 0; i < capacity; i++) {
			if (tab[i] != NULL) {
				delete tab[i];
				tab[i] = NULL;
			}
		}
	}

	bool containsKey(K key) {
		return true;
	}

	bool containsValue(V value) {
		return true;
	}

	bool isEmpty() {
		return size == 0;
	}

	int getSize() {
		return size;
	}

	void print() {
		for (int i = 0; i < capacity; i++) {
			if (tab[i] != NULL && tab[i] -> getHash() != -1) {
				std::cout << i << ". " << tab[i]->getKey() << " " << tab[i]->getValue() << endl;
			}
		}
	}

private:
	int computeHashIndex(K key) {
		return hashFun(key) % capacity;
	}

	void removeOnIndex(int hashIndex) {
		delete tab[hashIndex];
		tab[hashIndex] = NULL;
		tab[hashIndex] = dummyNode;
		size--;
	}

	void fillNull() {
		for (int i = 0; i < capacity; i++) {
			tab[i] = NULL;
		}
	}

	void increase() {
		int oldCapacity = capacity;
		capacity = capacity << 1;
		realocate(capacity, oldCapacity);
	}

	void realocate(int newCapacity, int oldCapacity) {
		size = 0;
		Node<K, V>** tmpTab = tab;
		tab = new Node<K, V>*[newCapacity];
		fillNull();

		for (int i = 0; i < oldCapacity; i++) {
			Node<K, V>* tmpNode = tmpTab[i];
			if (tmpNode != NULL && tmpNode->getHash() != -1) {
				this->put(tmpNode->getKey(), tmpNode->getValue());
			}
		}

		delete tmpTab;
	}

	void tidy(int removedIndex) {
		int index = removedIndex + 1;
	
		while (tab[index] != NULL && tab[index]->getHash() != -1) {
			Node<K, V>* node = tab[index];
			tab[index] = NULL;
			size--;
			this->put(node->getKey(), node->getValue());
			delete node;
			index++;

			if (index >= capacity) {
				index = 0;
			}
		}
	}
};
