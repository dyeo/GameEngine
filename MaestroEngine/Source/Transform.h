#ifndef _MAESTRO_TRANSFORM_H_
#define _MAESTRO_TRANSFORM_H_

#include "Component.h"

#include <gmtk/gmtk.h>

namespace mae
{
	
	/// <summary>
	/// The Transform class is the scene graph node responsible for allowing objects to manipulate their children spatially.
	/// </summary>
	class Transform : public Component
	{
		friend class SceneGraph;

		// methods
	public:

		Transform(System * const sys, EntityHandle ent);

		virtual ~Transform();

		//

		void SetParent(Transform *const parent);

		Transform *const GetParent() const;

		void AddChild(Transform *const child);

		void RemoveChild(size_t index);

		void RemoveChild(Transform *const child);

		Transform *const GetChild(size_t index) const;

		bool IsChild(Transform *const child) const;

		size_t GetChildren() const { return children.size(); }

		//

		virtual void OnUpdate() override;

		//

		void Translate(gm::vec3 & dsp);

		const gm::vec3 & GetPosition() const;

		void SetPosition(gm::vec3 & pos);

		const gm::vec3 & GetLocalPosition() const;

		void SetLocalPosition(gm::vec3 & pos);

		//

		void Rotate(gm::quat & rot);

		const gm::quat & GetRotation() const;

		void SetRotation(gm::quat & rot);

		const gm::quat & GetLocalRotation() const;

		void SetLocalRotation(gm::quat & rot);

		//

		void Scale(gm::vec3 & scl);

		const gm::vec3 & GetScale() const;

		void SetScale(gm::vec3 & scl);

		const gm::vec3 & GetLocalScale() const;

		void SetLocalScale(gm::vec3 & scl);

		// members
	private:

		Transform *parent;

		std::vector<Transform *> children;

		gm::vec3 local_position;
		gm::quat local_rotation;
		gm::vec3 local_scale;

		gm::vec3 global_position;
		gm::quat global_rotation;
		gm::vec3 global_scale;

	};

}

#endif // !_MAESTRO_TRANSFORM_H_