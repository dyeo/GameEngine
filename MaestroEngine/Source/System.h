#ifndef _MAESTRO_SYSTEM_H_
#define _MAESTRO_SYSTEM_H_

#include "Updatable.h"

#include <typeindex>

class Maestro;
class Component;
class Entity;

class System : public Updatable
{
// methods
public:
	
	/// <summary>
	/// Initializes a new instance of the <see cref="System"/> class.
	/// </summary>
	/// <param name="engine">The <see cref="Maestro"/> engine instance.</param>
	System(Maestro *const engine);
	
	/// <summary>
	/// Virtual destructor.
	/// </summary>
	virtual ~System() override {};
	
	/// <summary>
	/// Called when a new <see cref="Component"/> that has been claimed by this <see cref="System"/> (using <see cref="Maestro::SetManagingSystem" />) is requested by a Component or <see cref="Entity"/>.
	/// </summary>
	/// <param name="srcEnt">The source Entity.</param>
	/// <param name="cmpType">The Component's type_index.</param>
	/// <returns>A const pointer to the created Component, stored internally by the System.</returns>
	virtual Component*const OnComponentCreate(Entity *const srcEnt, std::type_index cmpType);
	virtual bool OnComponentDestroy(Entity *const srcEnt, Component *const srcCmp);

	virtual void OnCreate() override;
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnFinish() override;
	virtual void OnDestroy() override;

// members
protected:

	Maestro *const engine;

private:
};

#endif // !_MAESTRO_SYSTEM_H_
