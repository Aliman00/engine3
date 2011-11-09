/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef ENGINE_STM_TRANSACTIONALOBJECTHANDLE_H_
#define ENGINE_STM_TRANSACTIONALOBJECTHANDLE_H_

#include "mm/KernelCall.h"

namespace engine {
  namespace stm {

	class Transaction;

	template<class O> class TransactionalObjectHeader;

	class HandleCounter {
	public:
		static AtomicInteger createdHandles;
		static AtomicInteger deletedHandles;
	};

	template<class O> class TransactionalObjectHandle : public Object {
		TransactionalObjectHeader<O>* header;

		Reference<Object*> object;
		Reference<Object*> objectCopy;

		//Reference<TransactionalObjectHandle<O>*> next;

	public:
		TransactionalObjectHandle();

		enum {CREATE, READ, WRITE};

		void initialize(TransactionalObjectHeader<O>* hdr, int accessType, Transaction* trans);

		virtual ~TransactionalObjectHandle();

		void upgradeToWrite();

		Transaction* acquireHeader(Transaction* transaction);

		void releaseHeader();

		void discardHeader(Transaction* transaction);

		void setPrevious(TransactionalObjectHandle<O>* n);

		Transaction* getCompetingTransaction();

		TransactionalObjectHeader<O>* getObjectHeader() {
			return header;
		}

		Reference<TransactionalObjectHandle<Object*>*> getLastHandle() {
			Reference<TransactionalObjectHandle<Object*>*> ref = (TransactionalObjectHandle<Object*>*) header->getLastHandle().get();

			return ref;
		}

		bool hasObjectChanged();
		bool hasObjectContentChanged();

		bool isCopyEqualToObject() {
			return objectCopy == object;
		}

		int compareTo(TransactionalObjectHandle* handle) {
			if ((TransactionalObjectHandle*) this == handle)
				return 0;
			else if ((TransactionalObjectHandle*) this < handle)
				return 1;
			else
				return -1;
		}

		int compareToHeaders(TransactionalObjectHandle<O>* handle);

		uint64 getHeaderID();

		Object* getObject() {
			return object;
		}

		Object* getObjectLocalCopy() {
			return objectCopy;
		}

		inline void resetObjects() {
			object = NULL;

			objectCopy = NULL;
		}
	};

	template<class O> TransactionalObjectHandle<O>::TransactionalObjectHandle() {
		header = NULL;
		//transaction = NULL;

		object = NULL;

		objectCopy = NULL;

//		HandleCounter::createdHandles.increment();
	}

	template<class O> void TransactionalObjectHandle<O>::initialize(TransactionalObjectHeader<O>* hdr, int accessType, Transaction* trans) {
		header = hdr;

		assert((uintptr_t) trans > 0x1000);
		//transaction = trans;

		if (accessType == WRITE) {
			//KernelCall kernelCall;

			//System::out.println("[" + Thread::getCurrentThread()->getName() +"] cloning " + String::valueOf((uint64) object));
			object = header->getObjectForWrite(this);

			assert(object != NULL);

			objectCopy = dynamic_cast<O>(object->clone());

#ifdef MEMORY_PROTECTION
			ptrdiff_t rel = (ptrdiff_t)objectCopy.get() - (ptrdiff_t)0x8000000000;
			
			assert(!(rel > 0 && rel <= (ptrdiff_t) 0x7e800000));
#endif

			//System::out.println("[" + Thread::getCurrentThread()->getName() +"] cloning " + String::valueOf((uint64) object) + " finished");
		} else if (accessType == READ){
			object = header->getObjectForRead(this);
			
			assert(object != NULL);

			objectCopy = NULL;
		} else {
			object = header->getObjectForWrite(this);
			
			assert(object != NULL);

			objectCopy = object;
			
#ifdef MEMORY_PROTECTION
			ptrdiff_t rel = (ptrdiff_t)objectCopy.get() - (ptrdiff_t)0x8000000000;
			
			assert(!(rel > 0 && rel <= (ptrdiff_t) 0x7e800000));
#endif
		}
	}

	template<class O> TransactionalObjectHandle<O>::~TransactionalObjectHandle() {
		header = NULL;

		object = NULL;
		objectCopy = NULL;

	//	HandleCounter::deletedHandles.increment();

		/*printf("TransactionHandle %p deleted at\n", this);
		StackTrace::printStackTrace();*/
	}

	template<class O> void TransactionalObjectHandle<O>::upgradeToWrite() {
		header->add(this);

		objectCopy = object->clone();
		/*
	        assert(object != NULL);
	        
		objectCopy = dynamic_cast<O>(object->clone());
		
		ptrdiff_t rel = (ptrdiff_t)objectCopy.get() - (ptrdiff_t)0x8000000000;
		
		assert(!(rel > 0 && rel <= (ptrdiff_t) 0x7e800000));*/
	}

	template<class O> Transaction* TransactionalObjectHandle<O>::acquireHeader(Transaction* transaction) {
		return header->acquireObject(transaction);
	}

	template<class O> void TransactionalObjectHandle<O>::releaseHeader() {
		Reference<Object*> obj = objectCopy.get();

		if (obj != NULL && objectCopy.compareAndSet(obj, NULL)) { // this is to avoid several threads releasing it*/
			header->releaseObject(this, obj);

			resetObjects();
		}

	}

	template<class O> void TransactionalObjectHandle<O>::discardHeader(Transaction* transaction) {
		header->discardObject(transaction);

		resetObjects();

		//this->transaction = NULL; <---------- this is wrong its the param
	}

	template<class O> Transaction* TransactionalObjectHandle<O>::getCompetingTransaction() {
		return header->getTransaction();
	}

	template<class O> bool TransactionalObjectHandle<O>::hasObjectChanged() {
		return !header->hasObject(object);
	}

	template<class O> bool TransactionalObjectHandle<O>::hasObjectContentChanged() {
		return memcmp(object, objectCopy, sizeof(O)) != 0;
	}

	/*template<class O> void TransactionalObjectHandle<O>::setPrevious(TransactionalObjectHandle<O>* n) {
		next = n;
	}*/

	template<class O> uint64 TransactionalObjectHandle<O>::getHeaderID() {
		return header->getHeaderID();
	}


	template<class O> int TransactionalObjectHandle<O>::compareToHeaders(TransactionalObjectHandle<O>* handle) {
		//printf("blia\n");

		uint64 headerID = handle->getHeaderID();

		if (header->getHeaderID() == headerID)
			return 0;
		else if (header->getHeaderID() < headerID)
			return 1;
		else
			return -1;
	}

  } // namespace stm
} // namespace engine


#endif /* ENGINE_STM_TRANSACTIONALOBJECTHANDLE_H_ */
