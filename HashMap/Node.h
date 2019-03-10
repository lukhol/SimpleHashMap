#pragma once

template <class K, class V>
class Node {
private:
	const int hash;
	K key;
	V value;

public:

	Node(int hash) : hash(hash) {}
	Node(int hash, K key, V value) : hash(hash), key(key), value(value) {}

	bool operator=(const Node<K, V>& node) {
		if (node == NULL) {
			return false;
		}

		return node.key == this->key && node.value == this->value;
	}

	int getHash() {
		return hash;
	}

	K getKey() {
		return key;
	}

	V getValue() {
		return value;
	}
};
