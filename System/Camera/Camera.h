#pragma once

class Camera
{
	static Camera* instance;

	TPoint*		pTarget;
	TPoint*		pCamera;

	TSize		rcClient;
	TSize		rcWorld;

	Camera() = default;
	~Camera();

	Camera(const Camera& other) = delete;
	Camera& operator=(const Camera& other) = delete;

public:

	static Camera* GetInstance();

	static void Create();
	static void Delete();

	bool Init(TPoint* const target, const TSize& client, const TSize& world);
	void Update();

	void SetTarget(TPoint* pt) { pTarget = pt; }
	void SetCamera(TPoint* pt) { pCamera = pt; }

	const TPoint* GetTarget() const { return pTarget; }
	const TPoint* GetCamera() const { return pCamera; }

	void SetClient(const TSize& rc) { rcClient = rc; }
	void SetWorld(const TSize& rc) { rcWorld = rc; }

	const TSize& GetClient() const { return rcClient; }
	const TSize& GetWorld() const { return rcWorld; }

	bool operator==(const TPoint* other) { return pTarget == other; }
	bool operator!=(const TPoint* other) { return pTarget != other; }
};