/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include "../platform.h"

#include "../lang/Exception.h"

namespace sys {
  namespace util {

	/*class PriorityQueue;

	class PriorityQueueEntry {
		PriorityQueueEntry* parentNode;

		PriorityQueueEntry* leftNode;
		PriorityQueueEntry* rightNode;

		int	npl;

	public:
		PriorityQueueEntry(PriorityQueueEntry* parent = NULL, PriorityQueueEntry* lnode = NULL,
				PriorityQueueEntry* rnode = NULL, int np = 0);

		virtual ~PriorityQueueEntry() {
		}

		virtual int compareTo(PriorityQueueEntry* node) = 0;

		friend class PriorityQueue;

	};

	class PriorityQueue {
	private:
		PriorityQueueEntry* root;

		int count;

	public:
		PriorityQueue();
		PriorityQueue(const PriorityQueue& heap);

		virtual ~PriorityQueue();

		void add(PriorityQueueEntry* node);

		const PriorityQueueEntry* peak() const;
		const PriorityQueueEntry* poll();

		const bool remove(PriorityQueueEntry* node);

		void clear();

		inline bool isEmpty() const {
			return root == NULL;
		}

		inline bool isFull() const {
			return false;
		}

		inline int size() {
			return count;
		}

	private:
		void merge(PriorityQueue& heap);


		PriorityQueueEntry* merge(PriorityQueueEntry* h1, PriorityQueueEntry* h2) const;
		PriorityQueueEntry* merge1(PriorityQueueEntry* h1, PriorityQueueEntry* h2) const;

		void swapChildren(PriorityQueueEntry* node) const;

		void reclaimMemory(PriorityQueueEntry* node) const;
	};

	PriorityQueueEntry::PriorityQueueEntry(PriorityQueueEntry* parent,
			PriorityQueueEntry* lnode, PriorityQueueEntry* rnode, int np) {
		parentNode = parent;
		leftNode = lnode;
		rightNode = rnode;

		npl = np;
	}

	PriorityQueue::PriorityQueue() {
		root = NULL;
		count = 0;
	}

	PriorityQueue::PriorityQueue(const PriorityQueue& heap) {
		root = NULL;

		*this = heap;
	}

	PriorityQueue::~PriorityQueue() {
		clear();
	}

	void PriorityQueue::add(PriorityQueueEntry* node) {
		root = merge(node, root);

		++count;
	}

	const PriorityQueueEntry* PriorityQueue::peak() const {
		return root;
	}

	const PriorityQueueEntry* PriorityQueue::poll() {
		if (isEmpty())
			return NULL;

		PriorityQueueEntry* oldRoot = root;
		root = merge(root->leftNode, root->rightNode);

		if (root != NULL)
			root->parentNode = NULL;

		oldRoot->parentNode = NULL;
		oldRoot->leftNode = NULL;
		oldRoot->rightNode = NULL;

		--count;
		return oldRoot;
	}

	const bool PriorityQueue::remove(PriorityQueueEntry* node) {
		if (isEmpty())
			return false;

		PriorityQueueEntry* oldNode = node;
		PriorityQueueEntry* parent = oldNode->parentNode;

		node = merge(node->leftNode, node->rightNode);

		if (parent != NULL) {
			if (parent->leftNode == oldNode)
				parent->leftNode = node;
			else
				parent->rightNode = node;

			if (node != NULL)
				node->parentNode = parent;
		} else {
			root = node;

			if (node != NULL)
				node->parentNode = NULL;
		}

		oldNode->parentNode = NULL;
		oldNode->leftNode = NULL;
		oldNode->rightNode = NULL;

		--count;
		return true;
	}

	void PriorityQueue::clear() {
		reclaimMemory(root);

		root = NULL;
		count = 0;
	}

	void PriorityQueue::merge(PriorityQueue& heap) {
		if (this == &heap)
			return;

		root = merge(root, heap.root);
		heap.root = NULL;
	}

	PriorityQueueEntry* PriorityQueue::merge(PriorityQueueEntry* h1, PriorityQueueEntry* h2) const {
		if (h1 == NULL)
			return h2;

		if (h2 == NULL)
			return h1;

		if (h1 == h2) {
			int i = 2 * 2;
		}

		if (h1->compareTo(h2) > 0)
			return merge1(h1, h2);
		else
			return merge1(h2, h1);
	}

	PriorityQueueEntry* PriorityQueue::merge1(PriorityQueueEntry* h1, PriorityQueueEntry* h2) const {
		if (h1->leftNode == NULL) {
			h1->leftNode = h2;
			h2->parentNode = h1;
		} else {
			h1->rightNode = merge(h1->rightNode, h2);
			h1->rightNode->parentNode = h1;

			if (h1->leftNode->npl < h1->rightNode->npl)
				swapChildren(h1);

			h1->npl = h1->rightNode->npl + 1;
		}

		return h1;
	}

	void PriorityQueue::swapChildren(PriorityQueueEntry* node) const {
		PriorityQueueEntry* tmp = node->leftNode;

		node->leftNode = node->rightNode;
		node->rightNode = tmp;
	}

	void PriorityQueue::reclaimMemory(PriorityQueueEntry* node) const {
		if (node != NULL) {
			reclaimMemory(node->leftNode);
			reclaimMemory(node->rightNode);

			delete node;
		}
	}*/

  } // namespace util
} // namespace sys;

using namespace sys::util;

#endif /* PRIORITYQUEUE_H_ */
