/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef WEAKREFERENCE_H_
#define WEAKREFERENCE_H_

#include "../Variable.h"

#include "../../thread/ReadWriteLock.h"
#include "system/thread/atomic/AtomicReference.h"
#include "../Object.h"

namespace sys {
  namespace lang {

   class WeakReferenceBase {
   public:
	   virtual ~WeakReferenceBase() {

	   }

	   int compareTo(WeakReferenceBase* base) {
		   if (this < base)
			   return 1;
		   else if (this > base)
			   return -1;
		   else return 0;
	   }

   protected:
	   virtual void clearObject() = 0;

	   friend class Object;
   };

	template<class O> class WeakReference : public Variable, public WeakReferenceBase {
	protected:
		AtomicReference<O> object;
		ReadWriteLock rwlock;

	public:
		WeakReference() : Variable() {
			object = NULL;
		}

		WeakReference(const WeakReference<O>& ref) : Variable(), WeakReferenceBase() {
			initializeObject(ref.object);
		}

		WeakReference(O obj) : Variable() {
			initializeObject(obj);
		}

		virtual ~WeakReference() {
			releaseObject();
		}

		virtual int compareTo(const WeakReference<O>& val) const {
			if (object < val.object)
				return 1;
			else if (object > val.object)
				return -1;
			else
				return 0;
		}

		WeakReference<O>& operator=(const WeakReference<O>& ref) {
			if (this == &ref)
				return *this;

			updateObject(ref.object);

			return *this;
		}

		O operator=(O obj) {
			updateObject(obj);

			return object;
		}

		O operator->() const {
			return object;
		}

		operator O() const {
			return object;
		}

		inline O get() {
			rwlock.wlock();

			O copy = object;

			if (object != NULL && ((Object*)object.get())->_isGettingDestroyed()) {
				rwlock.unlock();
				return NULL;
			}

			rwlock.unlock();

			return copy;
		}

		bool toBinaryStream(ObjectOutputStream* stream) {
			return false;
		}

		bool parseFromBinaryStream(ObjectInputStream* stream) {
			return false;
		}

	protected:

		inline void updateObject(O obj) {
			if (obj == object.get())
				return;

			//This needs to be an atomic operation, 2 threads updating/reading this messes shit up
			//Thread A reading while thread B updating, thread A reads NULL cause it releases and then acquires
			/*releaseObject();

						setObject(obj);*/

			if (obj != NULL)
				((Object*)obj)->acquireWeak(this);

			while (true) {
				O oldobj = object.get();

				if (object.compareAndSet(oldobj, obj)) {
					if (oldobj != NULL)
						((Object*)oldobj)->releaseWeak(this);

					return;
				}
			}

		}

		inline void setObject(O obj) {
			if (obj == object)
				return;

			initializeObject(obj);
		}

		inline void initializeObject(O obj) {
			object = obj;

			acquireObject();
		}

		inline void acquireObject() {
			if (object != NULL) {
				((Object*)object.get())->acquireWeak(this);
			}
		}

		void releaseObject() {
			if (object != NULL) {
				((Object*)object.get())->releaseWeak(this);
				clearObject();
			}
		}

		void clearObject() {
			rwlock.wlock();

			if (object != NULL) {
				object = NULL;
			}

			rwlock.unlock();
		}

		friend class Object;
	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;

#endif /* WEAKREFERENCE_H_ */
