/*
 *	engine/core/ManagedService.cpp generated by engine3 IDL compiler 0.70
 */

#include "ManagedService.h"

/*
 *	ManagedServiceStub
 */

ManagedService::ManagedService(DummyConstructorParameter* param) : ManagedObject(param) {
	_setClassName("ManagedService");
}

ManagedService::~ManagedService() {
}



DistributedObjectServant* ManagedService::_getImplementation() {

	 if (!_updated) _updated = true;
	return _impl;
}

DistributedObjectServant* ManagedService::_getImplementationForRead() const {
	return _impl;
}

void ManagedService::_setImplementation(DistributedObjectServant* servant) {
	_impl = servant;
}

/*
 *	ManagedServiceImplementation
 */

ManagedServiceImplementation::ManagedServiceImplementation() : ManagedObjectImplementation() {
	_initializeImplementation();
}

ManagedServiceImplementation::ManagedServiceImplementation(DummyConstructorParameter* param) : ManagedObjectImplementation(param) {
	_initializeImplementation();
}


ManagedServiceImplementation::~ManagedServiceImplementation() {
}


void ManagedServiceImplementation::finalize() {
}

void ManagedServiceImplementation::_initializeImplementation() {
	_setClassHelper(ManagedServiceHelper::instance());

	_this = nullptr;

	_serializationHelperMethod();
}

void ManagedServiceImplementation::_setStub(DistributedObjectStub* stub) {
	_this = static_cast<ManagedService*>(stub);
	ManagedObjectImplementation::_setStub(stub);
}

DistributedObjectStub* ManagedServiceImplementation::_getStub() {
	return _this.get();
}

ManagedServiceImplementation::operator const ManagedService*() {
	return _this.get();
}

void ManagedServiceImplementation::lock(bool doLock) {
	_this.getReferenceUnsafeStaticCast()->lock(doLock);
}

void ManagedServiceImplementation::lock(ManagedObject* obj) {
	_this.getReferenceUnsafeStaticCast()->lock(obj);
}

void ManagedServiceImplementation::rlock(bool doLock) {
	_this.getReferenceUnsafeStaticCast()->rlock(doLock);
}

void ManagedServiceImplementation::wlock(bool doLock) {
	_this.getReferenceUnsafeStaticCast()->wlock(doLock);
}

void ManagedServiceImplementation::wlock(ManagedObject* obj) {
	_this.getReferenceUnsafeStaticCast()->wlock(obj);
}

void ManagedServiceImplementation::unlock(bool doLock) {
	_this.getReferenceUnsafeStaticCast()->unlock(doLock);
}

void ManagedServiceImplementation::runlock(bool doLock) {
	_this.getReferenceUnsafeStaticCast()->runlock(doLock);
}

void ManagedServiceImplementation::_serializationHelperMethod() {
	ManagedObjectImplementation::_serializationHelperMethod();

	_setClassName("ManagedService");

}

void ManagedServiceImplementation::readObject(ObjectInputStream* stream) {
	uint16 _varCount = stream->readShort();
	for (int i = 0; i < _varCount; ++i) {
		uint32 _nameHashCode;
		TypeInfo<uint32>::parseFromBinaryStream(&_nameHashCode, stream);

		uint32 _varSize = stream->readInt();

		int _currentOffset = stream->getOffset();

		if(ManagedServiceImplementation::readObjectMember(stream, _nameHashCode)) {
		}

		stream->setOffset(_currentOffset + _varSize);
	}

	initializeTransientMembers();
}

bool ManagedServiceImplementation::readObjectMember(ObjectInputStream* stream, const uint32& nameHashCode) {
	if (ManagedObjectImplementation::readObjectMember(stream, nameHashCode))
		return true;

	switch(nameHashCode) {
	}

	return false;
}

void ManagedServiceImplementation::writeObject(ObjectOutputStream* stream) {
	int _currentOffset = stream->getOffset();
	stream->writeShort(0);
	int _varCount = ManagedServiceImplementation::writeObjectMembers(stream);
	stream->writeShort(_currentOffset, _varCount);
}

int ManagedServiceImplementation::writeObjectMembers(ObjectOutputStream* stream) {
	int _count = ManagedObjectImplementation::writeObjectMembers(stream);

	uint32 _nameHashCode;
	int _offset;
	uint32 _totalSize;

	return _count;
}

/*
 *	ManagedServiceAdapter
 */


#include "engine/orb/messages/InvokeMethodMessage.h"


ManagedServiceAdapter::ManagedServiceAdapter(ManagedService* obj) : ManagedObjectAdapter(obj) {
}

void ManagedServiceAdapter::invokeMethod(uint32 methid, DistributedMethod* inv) {
	DOBMessage* resp = inv->getInvocationMessage();

	switch (methid) {
	default:
		ManagedObjectAdapter::invokeMethod(methid, inv);
	}
}

/*
 *	ManagedServiceHelper
 */

ManagedServiceHelper* ManagedServiceHelper::staticInitializer = ManagedServiceHelper::instance();

ManagedServiceHelper::ManagedServiceHelper() {
	className = "ManagedService";

	Core::getObjectBroker()->registerClass(className, this);
}

void ManagedServiceHelper::finalizeHelper() {
	ManagedServiceHelper::finalize();
}

DistributedObject* ManagedServiceHelper::instantiateObject() {
	return new ManagedService(DummyConstructorParameter::instance());
}

DistributedObjectServant* ManagedServiceHelper::instantiateServant() {
	return new ManagedServiceImplementation(DummyConstructorParameter::instance());
}

DistributedObjectPOD* ManagedServiceHelper::instantiatePOD() {
	return new ManagedServicePOD();
}

DistributedObjectAdapter* ManagedServiceHelper::createAdapter(DistributedObjectStub* obj) {
	DistributedObjectAdapter* adapter = new ManagedServiceAdapter(static_cast<ManagedService*>(obj));

	obj->_setClassName(className);
	obj->_setClassHelper(this);

	adapter->setStub(obj);

	return adapter;
}

/*
 *	ManagedServicePOD
 */

ManagedServicePOD::~ManagedServicePOD() {
}

ManagedServicePOD::ManagedServicePOD(void) {
	_className = "ManagedService";
}


void ManagedServicePOD::writeObject(ObjectOutputStream* stream) {
	int _currentOffset = stream->getOffset();
	stream->writeShort(0);
	int _varCount = ManagedServicePOD::writeObjectMembers(stream);
	stream->writeShort(_currentOffset, _varCount);
}

int ManagedServicePOD::writeObjectMembers(ObjectOutputStream* stream) {
	int _count = ManagedObjectPOD::writeObjectMembers(stream);

	uint32 _nameHashCode;
	int _offset;
	uint32 _totalSize;

	return _count;
}

bool ManagedServicePOD::readObjectMember(ObjectInputStream* stream, const uint32& nameHashCode) {
	if (ManagedObjectPOD::readObjectMember(stream, nameHashCode))
		return true;

	switch(nameHashCode) {
	}

	return false;
}

void ManagedServicePOD::readObject(ObjectInputStream* stream) {
	uint16 _varCount = stream->readShort();
	for (int i = 0; i < _varCount; ++i) {
		uint32 _nameHashCode;
		TypeInfo<uint32>::parseFromBinaryStream(&_nameHashCode, stream);

		uint32 _varSize = stream->readInt();

		int _currentOffset = stream->getOffset();

		if(ManagedServicePOD::readObjectMember(stream, _nameHashCode)) {
		}

		stream->setOffset(_currentOffset + _varSize);
	}

}

void ManagedServicePOD::writeObjectCompact(ObjectOutputStream* stream) {
	ManagedObjectPOD::writeObjectCompact(stream);


}

