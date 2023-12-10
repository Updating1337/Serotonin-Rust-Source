#include "Features.hpp"
#include "../../ConnectionManager/ConnectionManager.hpp"
#include "../Visuals/Visuals.hpp"
#include "../EyeHack/EyeHack.hpp"
#include <array>
#include "../../Hooking/WriteToStream/Prediction.hpp"


std::vector<Vector3> GenerateCircle(float radius, int points, bool BulletTP = false) {
	std::vector<Vector3> result;
	float step = (2.0f * M_PI) / points;
	float maxYValue = 1.5f;

	for (int i = 0; i < points; i++) {
		float angle = i * step;
		float x = radius * Math::cosf(angle);
		float z = radius * Math::sinf(angle);

		// Adjust the yValue to gradually increase to maxYValue
		float yValue = (i / static_cast<float>(points - 1)) * maxYValue;

		result.push_back(Vector3(x, yValue, z));//
		result.push_back(Vector3(-x, -yValue, -z));
		result.push_back(Vector3(-x, 0.f, 0.f));
		result.push_back(Vector3(x, 0.f, 0.f));

		result.push_back(Vector3(0.f, 0.f, z));
		result.push_back(Vector3(0.f, 0.f, -z));

		result.push_back(Vector3(x, 0.f, z));
		result.push_back(Vector3(x, -yValue, z));
		result.push_back(Vector3(0.f, -yValue, 0.f));
	}

	return result;
}

inline void BulletTPAnglesModeIntense(std::vector<Vector3>& re, int numPoints = 100)
{
	float radius = 2.5f; // Radius of the sphere
	//int numPoints = 100; // Number of points to generate

	for (int i = 0; i < numPoints; ++i) {
		float theta = 2.0 * M_PI * i / numPoints;
		float phi = Math::acosf(1.0 - 2.0 * (i + 0.5) / numPoints);

		float x = radius * Math::sinf(phi) * Math::cosf(theta);
		float y = radius * Math::sinf(phi) * Math::sinf(theta);
		float z = radius * Math::cosf(phi);

		re.emplace_back(x, y, z);
		re.emplace_back(-x, -y, -z);
		re.emplace_back(x, 0.f, z);

		re.emplace_back(0.f, y, 0.f);
		re.emplace_back(0.f, -y, 0.f);

		re.emplace_back(-x, 0.f, 0.f);
		re.emplace_back(x, 0.f, 0.f);

		re.emplace_back(0.f, 0.f, z);
		re.emplace_back(0.f, 0.f, -z);

	}
}


inline void DynamicManipAngles(std::vector<Vector3>& re, float max = 1.5f, float maxy = 1.5f, int numPoints = 100)
{
	float radius = max; // Radius of the sphere

	for (int i = 0; i < numPoints; ++i) {
		float theta = static_cast<float>(LI_FN(rand)()) / static_cast<float>(RAND_MAX) * 2 * M_PI; // Random angle
		float phi = static_cast<float>(LI_FN(rand)()) / static_cast<float>(RAND_MAX) * M_PI;     // Random inclination angle

		float x = radius * Math::sinf(phi) * Math::cosf(theta);
		float y = maxy * Math::sinf(phi) * Math::sinf(theta);
		float z = radius * Math::cosf(phi);

		re.emplace_back(x, y, z);
		re.emplace_back(-x, -y, -z);
		re.emplace_back(x, 0.f, z);

		re.emplace_back(0.f, y, 0.f);
		re.emplace_back(0.f, -y, 0.f);

		re.emplace_back(-x, 0.f, 0.f);
		re.emplace_back(x, 0.f, 0.f);

		re.emplace_back(0.f, 0.f, z);
		re.emplace_back(0.f, 0.f, -z);
	}
}

std::vector<Vector3> generatePointsInNonUniformSphere(float radiusX, float radiusY, float radiusZ, int baseNumPoints) {
	std::vector<Vector3> points;


	// Calculate the volume of the ellipsoid
	float volume = (4.0f / 3.0f) * M_PI * radiusX * radiusY * radiusZ;

	// Adjust the number of points based on the ellipsoid's volume
	int numPoints = static_cast<int>(baseNumPoints * (volume / (4.0f / 3.0f * M_PI * radiusX * radiusY * radiusZ))); // Adjust for a reference ellipsoid

	for (int i = 0; i < numPoints; i++) {
		float theta = static_cast<float>(LI_FN(rand)()) / static_cast<float>(RAND_MAX) * 2 * M_PI; // Random angle
		float phi = static_cast<float>(LI_FN(rand)()) / static_cast<float>(RAND_MAX) * M_PI;     // Random inclination angle


		float x = radiusX * Math::sinf(phi) * Math::cosf(theta);
		float y = radiusY * Math::sinf(phi) * Math::sinf(theta);
		float z = radiusZ * Math::cosf(phi);

		points.push_back(Vector3(x, y, z));
		points.push_back(Vector3(-x, -y, -z));
		points.push_back(Vector3(x, 0.f, z));

		points.push_back(Vector3(0.f, y, 0.f));
		points.push_back(Vector3(0.f, -y, 0.f));
	
		points.push_back(Vector3(-x, 0.f, 0.f));
		points.push_back(Vector3(x, 0.f, 0.f));
	
		points.push_back(Vector3(0.f, 0.f, z));
		points.push_back(Vector3(0.f, 0.f, -z));
	}

	return points;
}

//inline void BulletTPAnglesModeCrazy(std::vector<Vector3>& re, float step = 0.4)
//{
//	for (float x = -2.2; x <= 2.2; x += step) {
//		for (float y = -2.3f; y <= 2.3f; y += step) {
//			for (float z = -2.2; z <= 2.2; z += step) {
//				re.emplace_back(x, y, z);
//			}
//		}
//	}
//}

bool can_manipulate(AssemblyCSharp::BasePlayer* ply, Vector3 pos, float mm_eye = 7.f) //7m only check rn
{
	if (!InGame || !IsAddressValid(ply))
		return false;

	auto camera = UnityEngine::Camera::get_main();
	if (!IsAddressValid(camera))
		return false;

	auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz());
	if (!IsAddressValid(AimbotTarget.m_player))
		return false;

	if (AimbotTarget.m_heli)
		return false;

	auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();

	if (m_settings::BulletTP)
	{
		Vector3 re_p = ply->eyes()->get_position();

		if (AssemblyCSharp::IsVisible(re_p, pos)) {
			Features().CachedManipPoint = re_p;
			Features().ManipulationAngle = re_p;
			Features().PositionVisible = true;
			return true;
		}
		else
			Features().PositionVisible = false;

		auto do_check = [&](Vector3 a) {

			Vector3 p;
			Vector3 ManipAngle;
			if (Features().PointVisible) {
				p = a;
				ManipAngle = a;
			}
			else {
				p = re_p + a;
				ManipAngle = a;
			}

			if (!AssemblyCSharp::IsVisible(p, re_p))
				return false;

			if (!EyeHack().ValidateEyePos(Features().LocalPlayer, p))
				return false;

			//if (!EyeHack().ValidateEyePos(Features().LocalPlayer, re_p + a))
			//	return false;

			if (!m_settings::BehindWall) {
				if (!AssemblyCSharp::IsVisible(p, Features().CachedBulletTPPosition))
					return false;
			}

			if (m_settings::DrawManipPoints)
				UnityEngine::DDraw().Sphere(p, 0.05f, Color::Red(), 0.02f, 10);

			Features().ManipulationAngle = a;
			return true;
		};

		if (m_settings::ManipMode == 0) {
			if (!Features().BulletTPPointVisible && !Features().PointVisible && !Features().PositionVisible || Features().CachedManipPoint.IsZero()) {

				for (float y = 1.5f; y > -1.5f; y -= 0.3f) {
					int points = m_settings::ManipPoints;
					float step = (M_PI_2) / points;
					float x, z, current = 0;
					for (size_t i = 0; i < points; i++)
					{
						x = Math::sinf(current) * mm_eye;
						z = Math::cosf(current) * mm_eye;

						Vector3 p1 = Vector3(x, y, z);
						Vector3 p2 = Vector3(-x, y, z);
						Vector3 p3 = Vector3(x, y, -z);
						Vector3 p4 = Vector3(-x, y, -z);

						Vector3 re_p = ply->eyes()->get_position();

						Vector3 p = re_p + p1;

						if (do_check(p1)) {
							Features().CachedManipPoint = p1 + re_p;
							Features().PointVisible = true;
							return true;
						}
						else if (do_check(p2)) {
							Features().CachedManipPoint = p2 + re_p;
							Features().PointVisible = true;
							return true;
						}
						else if (do_check(p3)) {
							Features().CachedManipPoint = p3 + re_p;
							Features().PointVisible = true;
							return true;
						}
						else if (do_check(p4)) {
							Features().CachedManipPoint = p4 + re_p;
							Features().PointVisible = true;
							return true;
						}
						else
							Features().ManipulationAngle = re_p;

						current += step;
					}
				}
			}
			else if (Features().PointVisible && !Features().CachedManipPoint.IsZero() || Features().CachedManipPoint == re_p) {
				if (do_check(Features().CachedManipPoint)) {
					return true;
				}
				else
					Features().ManipulationAngle = re_p;
			}
		}
		else if (m_settings::ManipMode == 1) {
			if (!Features().BulletTPPointVisible && !Features().PointVisible && !Features().PositionVisible || Features().CachedManipPoint.IsZero()) {
				std::vector<Vector3> generatedPoints;
				DynamicManipAngles(generatedPoints, mm_eye, 1.5, m_settings::ManipPoints);

				for (const Vector3& point : generatedPoints) {
					if (do_check(point)) {
						Features().CachedManipPoint = point + re_p;
						Features().PointVisible = true;
						return true;
					}
					else
						Features().ManipulationAngle = re_p;
				}
			}
			else if (Features().PointVisible && !Features().CachedManipPoint.IsZero() && !Features().PositionVisible) {
				if (do_check(Features().CachedManipPoint)) {
					return true;
				}
				else
					Features().ManipulationAngle = re_p;
			}
			else if (Features().PositionVisible) {
				return true;
			}
		}
		else if (m_settings::ManipMode == 2) {
			if (!Features().BulletTPPointVisible && !Features().PointVisible && !Features().PositionVisible || Features().CachedManipPoint.IsZero()) {
				std::vector<Vector3> generatedPoints = generatePointsInNonUniformSphere(mm_eye, 1.5, mm_eye, m_settings::ManipPoints);

				for (const Vector3& point : generatedPoints) {
					if (do_check(point)) {
						Features().CachedManipPoint = point + re_p;
						Features().PointVisible = true;
						return true;
					}
					else
						Features().ManipulationAngle = re_p;
				}
			}
			else if (Features().PointVisible && !Features().CachedManipPoint.IsZero() && !Features().PositionVisible) {
				if (do_check(Features().CachedManipPoint)) {
					return true;
				}
				else
					Features().ManipulationAngle = re_p;
			}
			else if (Features().PositionVisible)
				return true;
		}

		//Features().ManipulationAngle = Vector3(0, 0, 0);
		return false;
	}
	else
	{
		Vector3 re_p = ply->eyes()->get_position();

		if (AssemblyCSharp::IsVisible(re_p, pos)) {
			Features().ManipulationAngle = re_p;
			Features().CachedManipPoint = re_p;
			return true;
		}

		auto do_check = [&](Vector3 a) {

			Vector3 p;
			Vector3 ManipAngle;
			if (Features().PointVisible) {
				p = a;
				ManipAngle = a - re_p;
			}
			else {
				p = re_p + a;
				ManipAngle = a;
			}

			if (!AssemblyCSharp::IsVisible(p, re_p))
				return false;

			if (!EyeHack().ValidateEyePos(Features().LocalPlayer, p))
				return false;

			if (m_settings::DrawManipPoints)
				UnityEngine::DDraw().Sphere(p, 0.05f, Color::Red(), 0.02f, 10);

			auto tick_time = Features().LocalPlayer->lastSentTickTime();
			float desyncTime = (UnityEngine::Time::get_realtimeSinceStartup() - tick_time) - 0.03125 * 3;
			float mm_max_eye = (0.1f + ((desyncTime + 2.f / 60.f + 0.125f) * 1.5f) * Features().LocalPlayer->MaxVelocity()) - 0.05f;
			float max_v_multicplier = 4.5f;
			float v_mm_max_eye = 1.5f;

			if (!AssemblyCSharp::IsVisible(p, pos)) {
				bool t = false;
				auto right = Features().LocalPlayer->eyes()->BodyRight();
				auto forward = Features().LocalPlayer->eyes()->BodyForward();
				auto _forward = Features().LocalPlayer->eyes()->HeadForward();

				Vector3 z = pos;
				if (m_settings::ManipMode == 0 || m_settings::ManipMode == 1 || m_settings::ManipMode == 2) {
					std::array < Vector3, 41 >positions = {
					z + Vector3(0.f, (v_mm_max_eye / 5), 0.f), // small up

					z + Vector3(0.f, v_mm_max_eye / 2, 0.f), // medium up

					z + Vector3(0.f, v_mm_max_eye, 0.f), // big up

					z + Vector3(0.f, -(1.4f / 2), 0.f), // small down

					z + Vector3(0.f, -1.4f, 0.f), // big down

					z + Vector3(right.x * (mm_max_eye / 2), 0.f, right.z * (mm_max_eye / 2)), // small right

					z + Vector3(right.x * mm_max_eye, 0.f, right.z * mm_max_eye), // big right

					z + Vector3(right.x * (mm_max_eye / 2), (1.4f / 2), right.z * (mm_max_eye / 2)), // small right up

					z + Vector3(right.x * mm_max_eye, 1.4f, right.z * mm_max_eye), // big right up

					z + Vector3(right.x * (mm_max_eye / 2), -(1.4f / 2), right.z * (4.f / 2)), // small right down

					z + Vector3(right.x * mm_max_eye, -1.4f, right.z * mm_max_eye), // big right down

					z + Vector3(-(right.x * (mm_max_eye / 2)), 0.f, -(right.z * (mm_max_eye / 2))), // small left

					z + Vector3(-(right.x * mm_max_eye), 0.f, -(right.z * mm_max_eye)), // big left

					z + Vector3(-(right.x * (mm_max_eye / 2)), (1.4f / 2), -(right.z * (mm_max_eye / 2))), // small left up

					z + Vector3(-(right.x * mm_max_eye), 1.4f, -(right.z * mm_max_eye)), // big left up

					z + Vector3(-(right.x * (mm_max_eye / 2)), -(1.4f / 2), -(right.z * (mm_max_eye / 2))), // small left down

					z + Vector3(-(right.x * mm_max_eye), -1.4f, -(right.z * mm_max_eye)), // big left down 

					z + Vector3(forward.x * (mm_max_eye / 2), 0.f, forward.z * (mm_max_eye / 2)),// small forward

					z + Vector3(forward.x * mm_max_eye, 0.f, forward.z * mm_max_eye), // big forward

					z + Vector3(-(forward.x * (mm_max_eye / 2)), 0.f, -(forward.z * (mm_max_eye / 2))), // small backward

					z + Vector3(-(forward.x * mm_max_eye), 0.f, -(forward.z * mm_max_eye)), // big backward

					z + Vector3(forward.x * (mm_max_eye / 2), (1.4f / 2), forward.z * (mm_max_eye / 2)),// small forward up

					z + Vector3(forward.x * mm_max_eye, 1.4f, forward.z * mm_max_eye), // big forward up

					z + Vector3(forward.x * (mm_max_eye / 2), -(1.4f / 2), forward.z * (mm_max_eye / 2)),// small forward down

					z + Vector3(forward.x * mm_max_eye, -1.4f, forward.z * mm_max_eye), // big forward down

					z + Vector3(-(forward.x * (mm_max_eye / 2)), 0.f, -(forward.z * (mm_max_eye / 2))),// small reverse

					z + Vector3(-(forward.x * mm_max_eye), 0.f, -(forward.z * mm_max_eye)), // big reverse 

					z + Vector3(-(forward.x * (mm_max_eye / 2)), (1.4f / 2), -(forward.z * (mm_max_eye / 2))),// small reverse up

					z + Vector3(-(forward.x * 4.f), 1.4f, -(forward.z * 4.f)), // big reverse up

					z + Vector3(-(forward.x * (mm_max_eye / 2)), -(1.4f / 2), -(forward.z * (mm_max_eye / 2))),// small reverse down

					z + Vector3(-(forward.x * mm_max_eye), -1.4f, -(forward.z * mm_max_eye)), // big reverse down

					z + Vector3(right.x * mm_max_eye, v_mm_max_eye, right.z * (mm_max_eye)) * 0.9f, // big diag-up-right

					z + Vector3(-right.x * (mm_max_eye), (v_mm_max_eye), -right.z * (mm_max_eye)) * 0.9f, // big diag-up-left

					z + Vector3(right.x * mm_max_eye, -v_mm_max_eye, right.z * (mm_max_eye)) * 0.9f, // big diag-down-right

					z + Vector3(-right.x * (mm_max_eye), (-v_mm_max_eye), -right.z * (mm_max_eye)) * 0.9f, // big diag-up-left

					z + Vector3((right.x / 2) * mm_max_eye, v_mm_max_eye, (right.z / 2) * (mm_max_eye)), // big diag-up-right

					z + Vector3(-(right.x / 2) * (mm_max_eye), (v_mm_max_eye), -(right.z / 2) * (mm_max_eye)), // big diag-up-left

					z + Vector3((right.x / 2) * mm_max_eye, -v_mm_max_eye, (right.z / 2) * (mm_max_eye)), // big diag-down-right

					z + Vector3(-(right.x / 2) * (mm_max_eye), (-v_mm_max_eye), -(right.z / 2) * (mm_max_eye)), // big diag-up-left

					z + Vector3((forward.x / 2) * (mm_max_eye / 2), (v_mm_max_eye / 1), (forward.z / 2) * (mm_max_eye / 2)), // big diag-up-forward

					z + Vector3(-((forward.x / 2) * (mm_max_eye / 2)), (v_mm_max_eye / 1), -((forward.z / 2) * mm_max_eye / 2)), // big diag-up-backward
					};

					for (auto v : positions) {

						if (v.y > 1.5f)
							continue;

						if (v.y > -1.5f)
							continue;

						if (v.x > 9.f)
							continue;

						if (v.x > -9.f)
							continue;

						if (v.z > 9.f)
							continue;

						if (v.z > -9.f)
							continue;


						if (!EyeHack().ValidateEyePos(Features().LocalPlayer, v))
							break;

						if (!EyeHack().ValidateEyePos(Features().LocalPlayer, z))
							break;

						if (AssemblyCSharp::IsVisible(p, v)) {
							if (AssemblyCSharp::IsVisible(z, v)) {
								t = true;
								break;
							}
						}

					}
				}

				if (!t) return false;
			}
			Features().ManipulationAngle = ManipAngle;
			return true;
		};

		if (m_settings::ManipMode == 0) {
			if (!Features().PointVisible || Features().CachedManipPoint.IsZero()) {
				for (float y = 1.5f; y > -1.5f; y -= 0.3f) {
					int points = m_settings::ManipPoints;
					float step = (M_PI_2) / points;
					float x, z, current = 0;
					for (size_t i = 0; i < points; i++)
					{
						x = Math::sinf(current) * mm_eye;
						z = Math::cosf(current) * mm_eye;

						Vector3 p1 = Vector3(x, y, z);
						Vector3 p2 = Vector3(-x, y, z);
						Vector3 p3 = Vector3(x, y, -z);
						Vector3 p4 = Vector3(-x, y, -z);

						Vector3 re_p = ply->eyes()->get_position();

						Vector3 p = re_p + p1;

						if (do_check(p1)) {
							Features().CachedManipPoint = p1 + re_p;
							Features().PointVisible = true;
							return true;
						}
						else if (do_check(p2)) {
							Features().CachedManipPoint = p2 + re_p;
							Features().PointVisible = true;
							return true;
						}
						else if (do_check(p3)) {
							Features().CachedManipPoint = p3 + re_p;
							Features().PointVisible = true;
							return true;
						}
						else if (do_check(p4)) {
							Features().CachedManipPoint = p4 + re_p;
							Features().PointVisible = true;
							return true;
						}
						else
							Features().ManipulationAngle = re_p;

						current += step;
					}
				}
			}
			else if (Features().PointVisible && !Features().CachedManipPoint.IsZero() || Features().CachedManipPoint == re_p) {
				if (do_check(Features().CachedManipPoint)) {
					return true;
				}
				else
					Features().ManipulationAngle = re_p;
			}
		}
		else if (m_settings::ManipMode == 1) {
			if (!Features().PointVisible || Features().CachedManipPoint.IsZero()) {
				std::vector<Vector3> generatedPoints;
				DynamicManipAngles(generatedPoints, mm_eye, 1.5, m_settings::ManipPoints);

				for (const Vector3& point : generatedPoints) {
					if (do_check(point)) {
						Features().CachedManipPoint = point + re_p;
						Features().PointVisible = true;
						return true;
					}
					else
						Features().ManipulationAngle = re_p;
				}
			}
			else if (Features().PointVisible && !Features().CachedManipPoint.IsZero() || Features().CachedManipPoint == re_p) {
				if (do_check(Features().CachedManipPoint)) {
					return true;
				}
				else
					Features().ManipulationAngle = re_p;
			}
		}
		else if (m_settings::ManipMode == 2) {
			if (!Features().PointVisible || Features().CachedManipPoint.IsZero()) {
				std::vector<Vector3> generatedPoints = generatePointsInNonUniformSphere(mm_eye, 1.5, mm_eye, m_settings::ManipPoints);

				for (const Vector3& point : generatedPoints) {
					if (do_check(point)) {
						Features().CachedManipPoint = point + re_p;
						Features().PointVisible = true;
						return true;
					}
					else
						Features().ManipulationAngle = re_p;
				}
			}
			else if (Features().PointVisible && !Features().CachedManipPoint.IsZero() || Features().CachedManipPoint == re_p) {
				if (do_check(Features().CachedManipPoint)) {
					return true;
				}
				else
					Features().ManipulationAngle = re_p;
			}
		}

		//Features().ManipulationAngle = Vector3(0, 0, 0);
		return false;

	}
}

auto Features::FindBulletTPAngles(float maxDesyncValue) -> void
{
	if (!InGame)
		return;

	if (!IsAddressValid(Features().Instance()->LocalPlayer))
		return;

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return;

	if (!IsAddressValid(LocalPlayer))
		return;

	if (!LocalPlayer->IsAlive())
		return;

	auto camera = UnityEngine::Camera::get_main();
	if (!IsAddressValid(camera))
		return;

	auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz());
	if (!IsAddressValid(AimbotTarget.m_player))
	{
		this->BulletTPAngle = Vector3();

		if (m_settings::CacheBulletTP)
			this->CachedBulletTPPosition = this->LOSPoint;
		else
			this->CachedBulletTPPosition = AimbotTarget.m_position;

		m_settings::Thickbullet_AutoShoot = false;
		m_settings::Thickbullet_Indicator = false;
		this->BulletTPPointVisible = false;
		return;
	}

	if (AimbotTarget.m_heli)
		return;

	Vector3 targetPosition = AimbotTarget.m_position;
	if (Vector3().IsNaNOrInfinity(targetPosition))
		return;

	Vector3 pos = targetPosition;
	if (AssemblyCSharp::IsVisible(LocalPlayer->eyes()->get_position(), pos)) {
		this->BulletTPAngle = targetPosition;

		if (m_settings::CacheBulletTP)
			this->CachedBulletTPPosition = this->LOSPoint;
		else
			this->CachedBulletTPPosition = targetPosition;

		return;
	}

	float maxDist = 2.f;

	std::vector<Vector3> arrz;

	static bool LOS = false;
	static Vector3 Point;

	if (!AssemblyCSharp::IsVisible(this->CachedManipPoint, AimbotTarget.m_position))
		LOS = false;
	else
		LOS = true;

	if (m_settings::CacheBulletTP) {
		if (!AimbotTarget.m_player || this->CachedBulletTPPosition != this->LOSPoint || AimbotTarget.m_player->userID() != Features().TargetID) {
			//LOG(XS("[DEBUG] VerifiedCachedPoint Invisible 0"));
			m_settings::Thickbullet_AutoShoot = false;
			m_settings::Thickbullet_Indicator = false;
			this->BulletTPAngle = this->LOSPoint;
			this->CachedBulletTPPosition = this->LOSPoint;
			this->BulletTPPointVisible = false;
		}
	}
	else {
		if (!AimbotTarget.m_player || this->CachedBulletTPPosition != Point || AimbotTarget.m_player->userID() != Features().TargetID) {
			//LOG(XS("[DEBUG] VerifiedCachedPoint Invisible 0"));
			m_settings::Thickbullet_AutoShoot = false;
			m_settings::Thickbullet_Indicator = false;
			this->BulletTPAngle = targetPosition;
			this->CachedBulletTPPosition = targetPosition;
			this->BulletTPPointVisible = false;
		}
	}

	if (!AssemblyCSharp::IsVisible(this->CachedManipPoint, this->CachedBulletTPPosition) || this->CachedBulletTPPosition.IsZero() || AimbotTarget.m_player->userID() != Features().TargetID) {
		//LOG(XS("[DEBUG] VerifiedCachedPoint Invisible 1"));
		m_settings::Thickbullet_Indicator = false;
		m_settings::Thickbullet_AutoShoot = false;
		this->BulletTPPointVisible = false;
	}

	if (AssemblyCSharp::IsVisible(this->CachedManipPoint, this->CachedBulletTPPosition) &&
		EyeHack().ValidateEyePos(AimbotTarget.m_player, this->CachedBulletTPPosition, true)) {
		//LOG(XS("[DEBUG] VerifiedCachedPoint Visible"));
		this->BulletTPAngle = this->CachedBulletTPPosition;
		m_settings::Thickbullet_AutoShoot = true;
		m_settings::Thickbullet_Indicator = true;
		if (m_settings::ShowBulletTPAngle)
		{
			UnityEngine::DDraw().Sphere(this->CachedBulletTPPosition, 0.1f, Color::Blue(), 0.05f, 0);
		}
		this->BulletTPPointVisible = true;
	}

	if (!this->BulletTPPointVisible && !LOS || this->CachedBulletTPPosition.IsZero() && IsAddressValid(AimbotTarget.m_player)) {

		if (m_settings::BulletTPIntensity == 0)
			BulletTPAnglesModeIntense(arrz, 100);
		else if (m_settings::BulletTPIntensity == 1)
			BulletTPAnglesModeIntense(arrz, 250);
		else if (m_settings::BulletTPIntensity == 2)
			arrz = generatePointsInNonUniformSphere(2.3, 2.2, 2.2, 100);

		for (const auto& s : arrz)
		{
			Point = targetPosition + s;
			this->BTPSeperator = targetPosition + s;

			if (AssemblyCSharp::IsVisible(this->CachedManipPoint, Point) &&
				EyeHack().ValidateEyePos(AimbotTarget.m_player, Point, true))
			{
				if (m_settings::ShowBulletTPAngle)
				{
					UnityEngine::DDraw().Sphere(Point, 0.1f, Color::Orange(), 0.05f, 0);
				}
			//	LOG(XS("[DEBUG] VerifiedCachedPoint Visible 2"));
				this->CachedBulletTPPosition = Point;
				this->BulletTPPointVisible = false;
				m_settings::Thickbullet_AutoShoot = true;
				m_settings::Thickbullet_Indicator = true;
				this->BulletTPAngle = targetPosition + s;
				return;
			}
		}
	} 

	//this->BulletTPAngle = targetPosition;
	//m_settings::StartShooting = false;
	//m_settings::Thickbullet_Indicator = false;
}


auto Features::FindManipulationAngles(float MaxDesyncValue) -> void
{
	if (!InGame)
		return;

	if (!IsAddressValid(Features().Instance()->LocalPlayer))
		return;

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return;

	if (!IsAddressValid(LocalPlayer))
		return;

	if (!LocalPlayer->IsAlive())
		return;

	auto camera = UnityEngine::Camera::get_main();
	if (!IsAddressValid(camera))
		return;

	auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz());
	if (!IsAddressValid(AimbotTarget.m_player))
		return;

	Vector3 targetPosition = AimbotTarget.m_position;
	if (Vector3().IsNaNOrInfinity(targetPosition))
		return;

	auto eyes = LocalPlayer->eyes();
	if (!IsAddressValid(eyes))
		return;
	
	if (can_manipulate(LocalPlayer, Features().CachedBulletTPPosition, m_settings::max_spoofed_eye_distance))
	{
		m_settings::StartShooting = true;
		m_settings::Manipulation_Indicator = true;
	}
	else
	{
		m_settings::StartShooting = false;
		m_settings::Manipulation_Indicator = false;
	}

}

auto Features::GetManipulationAngle() -> Vector3 {
	if (Vector3().IsNaNOrInfinity(this->ManipulationAngle))
		return Vector3();

	return this->ManipulationAngle;
}

auto Features::BulletQueue(AssemblyCSharp::BaseProjectile* BaseProjectile) -> void
{
	if (!InGame)
		return;

	if (!IsAddressValid(Features().Instance()->LocalPlayer))
		return;

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return;

	if (!IsAddressValid(BaseProjectile))
		return;

	auto camera = UnityEngine::Camera::get_main();
	if (!IsAddressValid(camera))
		return;

	auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz());
	if (!IsAddressValid(m_target.m_player))
		return;

	if (m_settings::InstantKill && m_target.m_player->IsAlive())
	{
		if (m_settings::WaitForInstantHit)
		{
			if (InstantHitReady)
			{
				if (!BaseProjectile->IsA(AssemblyCSharp::BaseMelee::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::MedicalTool::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::BaseLauncher::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::BowWeapon::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::CompoundBowWeapon::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::CrossbowWeapon::StaticClass()))
				{
					if (BaseProjectile->primaryMagazine()->contents() > 0)
					{

						if (m_settings::WaitForBulletTP)
						{

							Vector3 pos = m_target.m_position;

							if (this->BulletTPAngle.IsZero())
								this->BulletTPAngle = m_target.m_position;

							if (AssemblyCSharp::IsVisible(AssemblyCSharp::LocalPlayer::get_Entity()->eyes()->get_position() + this->ManipulationAngle, this->BulletTPAngle))
							{
								//auto presetKey = displayName->c_str();
									//auto it = std::find(wideKeys.begin(), wideKeys.end(), presetKey);

									//if (it != wideKeys.end() && !m_settings::TargetFriendList) { // if target is a friend return
									//	return;
									//}

								float maxpacketsperSECOND = 1;
								if (RPC_Counter3.Calculate() <= maxpacketsperSECOND)
								{
									CalledLaunchFromHook = true;
									for (int i = 0; i < 4; i++)
									{
										BaseProjectile->primaryMagazine()->contents()--;

										BaseProjectile->LaunchProjectile();
										BaseProjectile->UpdateAmmoDisplay();
										BaseProjectile->ShotFired();
										BaseProjectile->DidAttackClientside();
										break;
									}
									//a1->SendClientTick();
									RPC_Counter3.Increment();
									CalledLaunchFromHook = false;
								}
							}
						}
						else
						{
							if (this->BulletTPAngle.IsZero())
								this->BulletTPAngle = m_target.m_position;

							if (AssemblyCSharp::IsVisible(AssemblyCSharp::LocalPlayer::get_Entity()->eyes()->get_position() + this->ManipulationAngle, this->BulletTPAngle))
							{
								float maxpacketsperSECOND = 1;
								if (RPC_Counter3.Calculate() <= maxpacketsperSECOND)
								{
									CalledLaunchFromHook = true;

									int magazineContents = BaseProjectile->primaryMagazine()->contents();
									for (int i = 0; i < 4; i++)
									{
										BaseProjectile->primaryMagazine()->contents()--;

										BaseProjectile->LaunchProjectile();
										BaseProjectile->UpdateAmmoDisplay();
										BaseProjectile->ShotFired();
										BaseProjectile->DidAttackClientside();
										break;
									}
									RPC_Counter3.Increment();
									CalledLaunchFromHook = false;

								}

							}

						}

					}
				}
			}
		}
		else
		{
			if (!BaseProjectile->IsA(AssemblyCSharp::BaseMelee::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::MedicalTool::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::BaseLauncher::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::BowWeapon::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::CompoundBowWeapon::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::CrossbowWeapon::StaticClass()))
			{
				if (BaseProjectile->primaryMagazine()->contents() > 0)
				{

					if (m_settings::WaitForBulletTP)
					{

						Vector3 pos = m_target.m_position;

						if (this->BulletTPAngle.IsZero())
							this->BulletTPAngle = m_target.m_position;

						if (AssemblyCSharp::IsVisible(AssemblyCSharp::LocalPlayer::get_Entity()->eyes()->get_position() + this->ManipulationAngle, this->BulletTPAngle))
						{

							float maxpacketsperSECOND = 1;
							if (RPC_Counter3.Calculate() <= maxpacketsperSECOND)
							{
								CalledLaunchFromHook = true;
								for (int i = 0; i < 4; i++)
								{
									BaseProjectile->primaryMagazine()->contents()--;

									BaseProjectile->LaunchProjectile();
									BaseProjectile->UpdateAmmoDisplay();
									BaseProjectile->ShotFired();
									BaseProjectile->DidAttackClientside();
									break;
								}
								//a1->SendClientTick();
								RPC_Counter3.Increment();
								CalledLaunchFromHook = false;
							}

						}
					}
					else
					{
						if (this->BulletTPAngle.IsZero())
							this->BulletTPAngle = m_target.m_position;

						if (AssemblyCSharp::IsVisible(AssemblyCSharp::LocalPlayer::get_Entity()->eyes()->get_position() + this->CachedManipPoint, this->CachedBulletTPPosition))
						{
							float maxpacketsperSECOND = 1;
							if (RPC_Counter3.Calculate() <= maxpacketsperSECOND)
							{
								CalledLaunchFromHook = true;

								int magazineContents = BaseProjectile->primaryMagazine()->contents();
								for (int i = 0; i < 4; i++)
								{
									BaseProjectile->primaryMagazine()->contents()--;

									BaseProjectile->LaunchProjectile();
									BaseProjectile->UpdateAmmoDisplay();
									BaseProjectile->ShotFired();
									BaseProjectile->DidAttackClientside();
									break;
								}
								RPC_Counter3.Increment();
								CalledLaunchFromHook = false;

							}
						}
					}
				}
			}
		}
	}
}

auto Features::FastBullet(AssemblyCSharp::BaseProjectile* BaseProjectile) -> void
{
	if (!InGame)
		return;

	if (!IsAddressValid(Features().Instance()->LocalPlayer))
		return;

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return;

	if (!IsAddressValid(BaseProjectile))
		return;

	if (m_settings::NormalFastBullet) {
		auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
		auto ActiveItem = LocalPlayer->ActiveItem();
		auto HeldItem = ActiveItem->GetHeldEntity();
		auto PrefabID = HeldItem->prefabID();

		if (ActiveItem) {
			static float orig[10];

			if (PrefabID == 1978739833 || PrefabID == 1537401592 || PrefabID == 3474489095 || PrefabID == 3243900999 || //ak, compound, doublebarrel, tommy
				PrefabID == 2696589892 || PrefabID == 1877401463 || PrefabID == 4231282088 || PrefabID == 563371667 || //waterpipe, spas-12, semi-rifle, semi-pistol
				PrefabID == 2477536592 || PrefabID == 554582418 || PrefabID == 3305012504 || PrefabID == 636374895 ||  //revolver, pump, python, prototype-17
				PrefabID == 4279856314 || PrefabID == 2293870814 || PrefabID == 844375121 || PrefabID == 2836331625 || //nailgun, m92-pistol, lr-300, hunting-bow
				PrefabID == 2176761593) { //eoka
				orig[0] = 1.f;
			}
			else if (PrefabID == 2545523575 || PrefabID == 3759841439) { //mp4a5, custom-smg
				orig[0] = 0.8f;
			}
			else if (PrefabID == 3459133190) { //hmlmg
				orig[0] = 1.2f;
			}
			else if (PrefabID == 1440914039) {//m249
				orig[0] = 1.3f;
			}
			else if (PrefabID == 1517089664) { //m39 rifle
				orig[0] = 1.25f;
			}
			else if (PrefabID == 2620171289) {//l96
				orig[0] = 3.f;
			}
			else if (PrefabID == 1665481300) { //bolty
				orig[0] = 1.75f;
			}
			else if (PrefabID == 2727391082) { //crossbow
				orig[0] = 1.5f;
			}
			else {
				orig[0] = 1.f;
			}

			BaseProjectile->projectileVelocityScale() = orig[0] + 0.39f;
		}
	}
}

auto Features::AutoReload(AssemblyCSharp::BaseProjectile* BaseProjectile) -> void {

	if (!InGame)
		return;

	if (!IsAddressValid(Features().Instance()->LocalPlayer))
		return;

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return;

	if (!IsAddressValid(BaseProjectile))
		return;

	m_settings::reload_time = BaseProjectile->reloadTime();

	if (m_settings::AutoReload)
	{
		if (BaseProjectile->IsA(AssemblyCSharp::BaseProjectile::StaticClass()) && !BaseProjectile->HasReloadCooldown() && !BaseProjectile->IsA(AssemblyCSharp::FlintStrikeWeapon::StaticClass()))
		{
			
			if (!m_settings::did_reload)
				m_settings::time_since_last_shot = (UnityEngine::Time::get_fixedTime() - m_settings::fixed_time_last_shot);

			if (m_settings::just_shot && (m_settings::time_since_last_shot > 0.2f))
			{
				BaseProjectile->ServerRPC(XS("StartReload"));
				BaseProjectile->SendSignalBroadcast(RustStructs::Signal::Reload, XS(""));

				m_settings::reload_reset_2 = false;
				m_settings::just_shot = false;
				//CanReload = false;
			}
			if (m_settings::time_since_last_shot > (BaseProjectile->reloadTime() - (BaseProjectile->reloadTime() / 10)) && !m_settings::did_reload)
			{
				BaseProjectile->ServerRPC(XS("Reload"));
				m_settings::did_reload = true;
				m_settings::time_since_last_shot = 0;
				m_settings::reload_reset = false;
				//CanReload = BaseProjectile->primaryMagazine()->contents() < BaseProjectile->primaryMagazine()->capacity();

			}
		}
		else
		{
			m_settings::reload_reset = false;
			m_settings::reload_reset_2 = false;
			m_settings::did_reload = false;
			m_settings::just_shot = false;
			m_settings::fixed_time_last_shot = 0;
			m_settings::time_since_last_shot = 0;
		}
	}
	else
	{
		m_settings::reload_reset = false;
		m_settings::reload_reset_2 = false;
		m_settings::did_reload = false;
		m_settings::just_shot = false;
		m_settings::fixed_time_last_shot = 0;
		m_settings::time_since_last_shot = 0;
	}
}

auto Features::AutoShoot(AssemblyCSharp::BaseProjectile* BaseProjectile) -> void
{
	if (!InGame)
		return;

	if (!IsAddressValid(Features().Instance()->LocalPlayer))
		return;

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return;

	if (!IsAddressValid(BaseProjectile))
		return;

	auto camera = UnityEngine::Camera::get_main();
	if (!IsAddressValid(camera))
		return;

	auto AimbotTarget = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz());
	if (!IsAddressValid(AimbotTarget.m_player))
		return;

	if (this->BulletTPAngle.IsZero())
		this->BulletTPAngle = AimbotTarget.m_position;

	if (m_settings::Autoshoot && !BaseProjectile->IsA(AssemblyCSharp::FlintStrikeWeapon::StaticClass()) && !BaseProjectile->IsA(AssemblyCSharp::MedicalTool::StaticClass()))
	{
		if (m_settings::WaitForInstantHit)
		{
			if (InstantHitReady)
			{
				if (AssemblyCSharp::IsVisible(AssemblyCSharp::LocalPlayer::get_Entity()->eyes()->get_position() + this->ManipulationAngle, this->BulletTPAngle))
				{
					CalledLaunchFromHook = true;
					BaseProjectile->DoAttackRecreation();
					CalledLaunchFromHook = false;

				}
			}
		}
		else
		{
			if (!m_settings::AlwaysAutoshoot && UnityEngine::Input::GetKey(m_settings::AutoshootKey))
			{
				if (AssemblyCSharp::IsVisible(AssemblyCSharp::LocalPlayer::get_Entity()->eyes()->get_position() + this->ManipulationAngle, this->BulletTPAngle))
				{
					CalledLaunchFromHook = true;
					BaseProjectile->DoAttackRecreation();
					CalledLaunchFromHook = false;
				}
			}
			else if (m_settings::AlwaysAutoshoot)
			{
				if (AssemblyCSharp::IsVisible(AssemblyCSharp::LocalPlayer::get_Entity()->eyes()->get_position() + this->CachedManipPoint, this->CachedBulletTPPosition))
				{
					CalledLaunchFromHook = true;
					BaseProjectile->DoAttackRecreation();
					CalledLaunchFromHook = false;

				}
			}

		}
	}
}

auto Features::RemoveCollision() -> void
{
	if (!InGame)
		return;

	if (!IsAddressValid(Features().LocalPlayer))
		return;

	UnityEngine::Physics::IgnoreLayerCollision(30, 12, m_settings::IgnoreTrees);
	UnityEngine::Physics::IgnoreLayerCollision(11, 12, m_settings::IgnorePlayers);
}