#include "Transform.h"

namespace mae
{

	Transform::Transform(System * const sys, Entity * const ent)
		: Component(sys, ent)
		, parent(nullptr)
	{
	}

	Transform::~Transform()
	{
		while (children.size() > 0)
		{
			delete children.back();
			children.pop_back();
		}
		children.clear();
	}

	void Transform::SetParent(Transform *const parent)
	{
		if (parent == this->parent || IsChild(parent) || parent == this) return;
		this->parent = parent;
	}

	Transform *const Transform::GetParent() const
	{
		return parent;
	}

	void Transform::AddChild(Transform *const child)
	{
		if (parent == child || IsChild(child) || child == this) return;
		children.push_back(child);
	}

	void Transform::RemoveChild(size_t index)
	{
		auto it = children.begin() + index;

		if (it < children.end())
		{
			(*it)->SetParent(nullptr);
			std::swap(*it, children.back());
			children.pop_back();
		}
	}

	void Transform::RemoveChild(Transform *const child)
	{
		ptrdiff_t pos = std::find(children.begin(), children.end(), child) - children.begin();

		RemoveChild((size_t)pos);
	}

	Transform *const Transform::GetChild(size_t index) const
	{
		if (index < children.size())
		{
			return children[index];
		}
	}

	bool Transform::IsChild(Transform *const child) const
	{
		auto it = std::find(children.begin(), children.end(), child);
		return it < children.end();
	}

	//

	void Transform::OnUpdate()
	{
		for (auto ch = children.begin(); ch != children.end(); ++ch)
		{
			(*ch)->global_position = global_position + local_position;
			(*ch)->global_scale = global_scale + local_scale;
			(*ch)->global_rotation = local_rotation * global_rotation; // dan: doing it backwards, may cause rotation transformation errors (i forget how i implemented my gm::quat mult)
		}
	}

	//

	void Transform::Translate(gm::vec3 & pos)
	{
		local_position += pos;
	}

	const gm::vec3 & Transform::GetPosition() const
	{
		return global_position + local_position;
	}

	void Transform::SetPosition(gm::vec3 & pos)
	{
		local_position = pos - GetPosition();
	}

	const gm::vec3 & Transform::GetLocalPosition() const
	{
		return local_position;
	}

	void Transform::SetLocalPosition(gm::vec3 & pos)
	{
		local_position = pos;
	}

	//

	void Transform::Rotate(gm::quat & rot)
	{
		local_rotation += rot;
	}

	const gm::quat & Transform::GetRotation() const
	{
		return global_rotation;
	}

	void Transform::SetRotation(gm::quat & rot)
	{
		gm::quat lr = rot * global_rotation;
		local_rotation = rot * GetRotation();
	}

	const gm::quat & Transform::GetLocalRotation() const
	{
		return local_rotation;
	}

	void Transform::SetLocalRotation(gm::quat & rot)
	{
		local_rotation = rot;
	}

	//

	void Transform::Scale(gm::vec3 & scl)
	{
		local_scale.x *= scl.y;
		local_scale.y *= scl.y;
	}

	const gm::vec3 & Transform::GetScale() const
	{
		return global_scale + local_scale;
	}

	void Transform::SetScale(gm::vec3 & scl)
	{
		local_scale = scl - GetScale();
	}

	const gm::vec3 & Transform::GetLocalScale() const
	{
		return local_scale;
	}

	void Transform::SetLocalScale(gm::vec3 & scl)
	{
		local_scale = scl;
	}

}