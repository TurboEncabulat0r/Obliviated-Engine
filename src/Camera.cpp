#include "Camera.h"
#include "Vector2.h"

namespace obvl
{
	Camera2D::Camera2D(GameObject* owner) : Component(owner)
	{
		name = "Camera2D";
	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::Update()
	{
	}

	void Camera2D::Start()
	{
	}

	void Camera2D::OnDraw()
	{
	}

	void Camera2D::OnGUI()
	{
	}

	void Camera2D::OnEnable()
	{
	}

	void Camera2D::OnDisable()
	{
	}

	void Camera2D::OnDestroy()
	{
	}

	Camera2D mainCamera = Camera2D(nullptr);

	void Camera2D::setMainCamera(Camera2D camera)
	{
		mainCamera = camera;
	}

	Camera2D Camera2D::getMainCamera()
	{
		return mainCamera;
	}
}