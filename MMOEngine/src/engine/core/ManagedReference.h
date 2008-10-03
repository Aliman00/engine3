/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef MANAGEDREFERENCE_H_
#define MANAGEDREFERENCE_H_

#include "../../system/lang.h"

#include "ManagedObject.h"

namespace engine {
  namespace core {

	template<class O> class ManagedReference : public ReferenceSlot<O> {
	public:
		ManagedReference() : ReferenceSlot<O>() {
		}
		
		ManagedReference(const ManagedReference& ref) : ReferenceSlot<O>(ref) {
		}
		
		ManagedReference(O* obj) : ReferenceSlot<O>(obj) {
		}
	
		void operator=(const ManagedReference& ref) {
			ReferenceSlot<O>::setObject(ref.object);
		}
	
		void operator=(O* obj) {
			ReferenceSlot<O>::updateObject(obj);
		}
	
	};

  } // namespace core
} // namespace engine

using namespace engine::core;
	
#endif /*MANAGEDREFERENCE_H_*/
