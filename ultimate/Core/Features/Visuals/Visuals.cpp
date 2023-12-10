#include "Visuals.hpp"
#include "../../Hooking/Hooks.hpp"
#include "../../ConnectionManager/ConnectionManager.hpp"
#include "../Features/Features.hpp"
#include "../../Includes/colorsettings.hpp"

#include <array>
#include <algorithm>
inline std::array<int, 20> valid_bones = {
		1, 2, 3, 5, 6, 14, 15, 17, 18, 21, 23, 24, 25, 26, 27, 48, 55, 56, 57, 76
};

//OOF FOV Function
float normalize_angle(float angle) {
	while (angle > 360.0f) {
		angle -= 360.0f;
	}
	while (angle < 0.0f) {
		angle += 360.0f;
	}
	return angle;
}

Vector3 normalize_angles(Vector3 angles) {
	angles.x = normalize_angle(angles.x);
	angles.y = normalize_angle(angles.y);
	angles.z = normalize_angle(angles.z);
	return angles;
}

Vector3 to_euler_angles(Vector4 q1) {
	float num = q1.w * q1.w;
	float num2 = q1.x * q1.x;
	float num3 = q1.y * q1.y;
	float num4 = q1.z * q1.z;
	float num5 = num2 + num3 + num4 + num;
	float num6 = q1.x * q1.w - q1.y * q1.z;
	Vector3 vector = Vector3();
	if (num6 > 0.4995f * num5) {
		vector.y = 2.0f * Math::my_atan2(q1.y, q1.x);
		vector.x = 1.57079637f;
		vector.z = 0.0f;
		return normalize_angles(vector * 57.2958f);
	}
	if (num6 < -0.4995f * num5) {
		vector.y = -2.0f * Math::my_atan2(q1.y, q1.x);
		vector.x = -1.57079637f;
		vector.z = 0.0f;
		return normalize_angles(vector * 57.2958f);
	}
	Vector4 quaternion = Vector4(q1.w, q1.z, q1.x, q1.y); 
	vector.y = Math::my_atan2(2.0f * quaternion.x * quaternion.w + 2.0f * quaternion.y * quaternion.z, 1.0f - 2.0f * (quaternion.z * quaternion.z + quaternion.w * quaternion.w));
	vector.x = Math::my_asin(2.0f * (quaternion.x * quaternion.z - quaternion.w * quaternion.y));
	vector.z = Math::my_atan2(2.0f * quaternion.x * quaternion.y + 2.0f * quaternion.z * quaternion.w, 1.0f - 2.0f * (quaternion.y * quaternion.y + quaternion.z * quaternion.z));
	return normalize_angles(vector * 57.2958f);
}

Vector2 cos_tan_horizontal(float angle, float range, float x, float y, int length) {
	float our_angle = (angle + 45.f);

	float yaw = our_angle * (M_PI / 180.0);

	float view_cosinus = Math::cosf(yaw);
	float view_sinus = Math::sinf(yaw);

	float x2 = range * (-view_cosinus) + range * view_sinus;
	float y2 = range * (-view_cosinus) - range * view_sinus;

	int screen_x = x + static_cast<int>(x2 / range * length);
	int screen_y = y + static_cast<int>(y2 / range * length);

	return Vector2(screen_x, screen_y);
}

//Radar Function
Vector2 WorldToRadar(Vector3 origin, Vector2 position, INT size, FLOAT rotation)
{
	Vector2 clampRotation
	((float)Math::cosf((rotation * (M_PI / 180.f)) + M_PI),
		-(float)Math::sinf((rotation * (M_PI / 180.f)) + M_PI));

	Vector2 clampCoords
	((origin.x * clampRotation.x + origin.z * clampRotation.y),
		(origin.x * clampRotation.y - origin.z * clampRotation.x));

	INT clampSize
	(size / 2.0f);

	Vector2 bVec
	(-clampCoords.x + position.x + clampSize,
		-clampCoords.y + position.y + clampSize);

	bVec.x = -clampCoords.x + position.x + clampSize;
	bVec.y = -clampCoords.y + position.y + clampSize;

	if (bVec.x > (position.x + size)) bVec.x = (position.x + size);
	else if (bVec.x < (position.x)) bVec.x = position.x;

	if (bVec.y > (position.y + size)) bVec.y = (position.y + size);
	else if (bVec.y < (position.y)) bVec.y = position.y;

	return bVec;
}

box_bounds Visuals::get_bounds(AssemblyCSharp::BasePlayer* player, float expand) {
	if (!player)
		return box_bounds::null();

	if (!IsAddressValid(Features().LocalPlayer))
		return box_bounds::null();

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return box_bounds::null();


	box_bounds ret = { FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN };


	const auto bone_transforms = player->model()->boneTransforms();
	if (!bone_transforms)
		return ret;

	for (auto j : valid_bones) {

		const auto bone = bone_transforms->m_Items[j];

		if (!bone)
			continue;

		auto transform = bone;
		if (IsAddressValid(transform)) {
			Vector2 sc;
			auto world_pos = transform->get_position();

			if (j == 48)
				world_pos.y += 0.2f;

			if (UnityEngine::WorldToScreen(world_pos, sc))
			{
				Vector2 bone_screen = sc;

				if (bone_screen.x < ret.left)
					ret.left = bone_screen.x;
				if (bone_screen.x > ret.right)
					ret.right = bone_screen.x;
				if (bone_screen.y < ret.top)
					ret.top = bone_screen.y;
				if (bone_screen.y > ret.bottom)
					ret.bottom = bone_screen.y;
			}
		}
	}

	if (ret.left == FLT_MAX)
		return box_bounds::null();
	if (ret.right == FLT_MIN)
		return box_bounds::null();
	if (ret.top == FLT_MAX)
		return box_bounds::null();
	if (ret.bottom == FLT_MIN)
		return box_bounds::null();

	ret.left -= expand;
	ret.right += expand;
	ret.top -= expand;
	ret.bottom += expand;

	return ret;
};

inline void DrawCornerBox(float x, float y, float x2, float y2, Color col)
{
	float box_width = x2 - x;
	float box_height = y2 - y;

	//top 
	UnityEngine::GL::Line(Vector2(x, y), Vector2(x + box_width / 4, y), col);
	UnityEngine::GL::Line(Vector2(x2, y), Vector2(x2 - box_width / 4, y), col);

	//left
	UnityEngine::GL::Line(Vector2(x, y), Vector2(x, y + box_height / 4), col);
	UnityEngine::GL::Line(Vector2(x, y2), Vector2(x, y2 - box_height / 4), col);

	//right
	UnityEngine::GL::Line(Vector2(x2, y), Vector2(x2, y + box_height / 4), col);
	UnityEngine::GL::Line(Vector2(x2, y2), Vector2(x2, y2 - box_height / 4), col);

	//bottom
	UnityEngine::GL::Line(Vector2(x, y2), Vector2(x + box_width / 4, y2), col);
	UnityEngine::GL::Line(Vector2(x2, y2), Vector2(x2 - box_width / 4, y2), col);

	return;
}

void Visuals::DrawPlayers()
{
	if (!InGame)
		return;

	if (!IsAddressValid(Features().LocalPlayer))
		return;

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return;

	auto camera = UnityEngine::Camera::get_main();
	if (!IsAddressValid(camera))
		return;

	auto LocalPlayer = Features().LocalPlayer;
	if (!IsAddressValid(LocalPlayer))
		return;

	for (const auto EntityList : VisualsArray)
	{
		const auto BasePlayer = EntityList.BasePlayer;
		if (!IsAddressValid(BasePlayer))
			continue;

		float distance = LocalPlayer->get_transform()->get_position().Distance(BasePlayer->get_transform()->get_position());
		bool npc = false;

		if (BasePlayer->IsA(AssemblyCSharp::ScientistNPC::StaticClass()) || BasePlayer->IsA(AssemblyCSharp::GingerbreadNPC::StaticClass()) || BasePlayer->IsA(AssemblyCSharp::NPCPlayer::StaticClass()) || BasePlayer->IsA(AssemblyCSharp::TunnelDweller::StaticClass()) || BasePlayer->IsA(AssemblyCSharp::UnderwaterDweller::StaticClass()) || BasePlayer->IsA(AssemblyCSharp::HTNPlayer::StaticClass()))
		{
			if (!m_settings::DrawNPC)
				continue;
			else if (m_settings::DrawNPC)
			{
				if (distance > m_settings::NPCDistance)
					continue;
			}

			npc = true;
		}

		if (BasePlayer->IsLocalPlayer())
			continue;

		if (BasePlayer->wasDead())
			continue;

		if (BasePlayer->IsDead())
		{
			if (!m_settings::DrawDead)
				continue;
		}

		if (BasePlayer->IsReceivingSnapshot())
			continue;

		if (BasePlayer->IsSleeper())
		{
			if (!m_settings::DrawSleepers)
				continue;
		}

		if (BasePlayer->playerFlags() & RustStructs::PlayerFlags::Wounded && !m_settings::DrawWounded)
			continue;

		if (BasePlayer->playerFlags() & RustStructs::PlayerFlags::SafeZone && !m_settings::DrawSafezone)
			continue;

		if (!IsAddressValid(BasePlayer->model()))
			continue;

		if (!IsAddressValid(BasePlayer->get_transform()))
			continue;


		const auto playerDistance = Features().LocalPlayer->get_transform()->get_position().Distance(BasePlayer->get_transform()->get_position());
		Vector2 RadarPoint;

		if (m_settings::Radar) {
			const auto bodyAngles = AssemblyCSharp::LocalPlayer::get_Entity()->input()->bodyAngles();
			const auto LocalPos = AssemblyCSharp::LocalPlayer::get_Entity()->get_transform()->get_position();
			const auto PlayerPos = BasePlayer->get_transform()->get_position();

			RadarPoint = WorldToRadar(PlayerPos - LocalPos, Vector2(m_settings::RadarPosX, m_settings::RadarPosY), m_settings::RadarSize, bodyAngles.y);
		}

		if (playerDistance <= m_settings::PlayerESPDistance)
		{
			box_bounds bo = get_bounds(BasePlayer, 0.f);
			if (!bo.empty())
			{
				int yoffset = 8;
				int yoffsethead = 0;
				float box_width = bo.right - bo.left;
				float box_height = bo.bottom - bo.top;
				Vector2 footPos = { bo.left + (box_width / 2), bo.bottom };
				Vector2 headPos = { bo.left + (box_width / 2), bo.top - 9.54f };

				auto IsVisible = [&](Vector3 from) {
					Vector3 head_pos_ = BasePlayer->get_bone_transform(48)->get_position();

					for (auto bone : { 48, 2, 3, 4, 15, 14, 26, 57 }) {
						Vector3 TargetPosition;
						if (bone == 48) TargetPosition = head_pos_;
						else TargetPosition = BasePlayer->get_bone_transform(bone)->get_position();
						if (AssemblyCSharp::IsVisible(from, TargetPosition)) {
							return true;
						}
					}
					return false;
					};

				auto is_Visible = IsVisible(camera->get_positionz());
				bool IsWounded = BasePlayer->playerFlags() & RustStructs::PlayerFlags::Wounded;
				auto VisibleColor = Color{ ColorSettings::Visible_Color.r, ColorSettings::Visible_Color.g, ColorSettings::Visible_Color.b, ColorSettings::Visible_Color.a };

				auto DrawBox_Color = Color{ ColorSettings::BoxEsp_Color.r, ColorSettings::BoxEsp_Color.g, ColorSettings::BoxEsp_Color.b, ColorSettings::BoxEsp_Color.a };
				auto VisCheckColor = is_Visible ? VisibleColor : DrawBox_Color;
				auto NameTag_Color = Color{ ColorSettings::Username_Color.r, ColorSettings::Username_Color.g, ColorSettings::Username_Color.b, ColorSettings::Username_Color.a };
				auto Sleeper_Color = Color{ ColorSettings::Sleeper_Color.r, ColorSettings::Sleeper_Color.g, ColorSettings::Sleeper_Color.b, ColorSettings::Sleeper_Color.a };
				auto Wounded_Color = Color{ ColorSettings::Wounded_Color.r, ColorSettings::Wounded_Color.g, ColorSettings::Wounded_Color.b, ColorSettings::Wounded_Color.a };
				auto Scientist_Color = Color{ ColorSettings::NPC_Color.r, ColorSettings::NPC_Color.g, ColorSettings::NPC_Color.b, ColorSettings::NPC_Color.a };
				auto Dead_Color = Color{ m_settings::Dead_Color[0], m_settings::Dead_Color[1], m_settings::Dead_Color[2], m_settings::Dead_Color[3] };
				auto Safezone_Color = Color{ ColorSettings::Safezone_Color.r, ColorSettings::Safezone_Color.g, ColorSettings::Safezone_Color.b, ColorSettings::Safezone_Color.a };
				auto HeldItem_Color = Color{ ColorSettings::Helditem_Color.r, ColorSettings::Helditem_Color.g, ColorSettings::Helditem_Color.b, ColorSettings::Helditem_Color.a };

				auto Friend_Color = Color{ m_settings::Friend_Color[0], m_settings::Friend_Color[1], m_settings::Friend_Color[2], m_settings::Friend_Color[3] };
				auto Target_Color = Color{ ColorSettings::Target_Color.r, ColorSettings::Target_Color.g, ColorSettings::Target_Color.b, ColorSettings::Target_Color.a };

				bool isFriend = false;
				auto camera = UnityEngine::Camera::get_main();
				if (!IsAddressValid(camera))
					return;

				auto m_target = AssemblyCSharp::BasePlayer::GetAimbotTarget(camera->get_positionz(), 500);
				/*if (!IsAddressValid(m_target.m_player))
					return;*/

				Color BoxColor;

				if (isFriend)
					BoxColor = Friend_Color;
				else if (npc)
					BoxColor = Scientist_Color;
				else if (BasePlayer == m_target.m_player && m_settings::DrawTarget)
					BoxColor = Target_Color;
				else if (BasePlayer->IsSleeper() && m_settings::DrawSleepers)
					BoxColor = Sleeper_Color;
				else if (BasePlayer->playerFlags() & RustStructs::PlayerFlags::Wounded && m_settings::DrawWounded)
					BoxColor = Wounded_Color;
				else if (BasePlayer->playerFlags() & RustStructs::PlayerFlags::SafeZone && m_settings::DrawSafezone)
					BoxColor = Safezone_Color;
				else if (BasePlayer->IsDead() && m_settings::DrawDead)
					BoxColor = Dead_Color;
				else
					BoxColor = m_settings::EspVisCheck ? VisCheckColor : DrawBox_Color;

				if (m_settings::Radar)
				{
					UnityEngine::GL().CircleFilled(Vector2(RadarPoint), 3.f, BoxColor, 25);
				}

				if (m_settings::SelectedBoxESP == 1)
				{
					UnityEngine::GL::Rectangle(Vector2(bo.left, bo.top), Vector2(bo.right, bo.bottom), BoxColor);
				}

				if (m_settings::SelectedBoxESP == 2)
				{
					DrawCornerBox(bo.left, bo.top, bo.right, bo.bottom, BoxColor);
				}

				if (m_settings::Target_Indicator)
				{
					if (BasePlayer == m_target.m_player)
					{
						UnityEngine::GL::TextCenter(Vector2(headPos.x, headPos.y - yoffsethead), XS("Target"), BoxColor, Color::Black(ColorSettings::BoxEsp_Color.a), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
						yoffsethead += 12.f;
					}
				}

				if (m_settings::Skeleton)
				{
					
					auto SkeletonColor = BoxColor;

					auto HeadBone = BasePlayer->get_bone_transform(RustStructs::bones::head)->get_position();
					auto NeckBone = BasePlayer->get_bone_transform(RustStructs::bones::neck)->get_position();
					auto Spine = BasePlayer->get_bone_transform(RustStructs::bones::spine1)->get_position();
					Vector2 HeadLoc;
					Vector2 NeckLoc;
					Vector2 SpineLoc;

					auto LShoulder = BasePlayer->get_bone_transform(RustStructs::bones::l_upperarm)->get_position();
					auto RShoulder = BasePlayer->get_bone_transform(RustStructs::bones::r_upperarm)->get_position();
					Vector2 LShoulderLoc;
					Vector2 RShoulderLoc;

					auto LElbow = BasePlayer->get_bone_transform(RustStructs::bones::l_forearm)->get_position();
					auto RElbow = BasePlayer->get_bone_transform(RustStructs::bones::r_forearm)->get_position();
					Vector2 LElbowLoc;
					Vector2 RElbowLoc;

					auto LWrist = BasePlayer->get_bone_transform(RustStructs::bones::l_hand)->get_position();
					auto RWrist = BasePlayer->get_bone_transform(RustStructs::bones::r_hand)->get_position();
					Vector2 LWristLoc;
					Vector2 RWristLoc;

					auto LHip = BasePlayer->get_bone_transform(RustStructs::bones::l_hip)->get_position();
					auto RHip = BasePlayer->get_bone_transform(RustStructs::bones::r_hip)->get_position();
					Vector2 LHipLoc;
					Vector2 RHipLoc;

					auto LKnee = BasePlayer->get_bone_transform(RustStructs::bones::l_knee)->get_position();
					auto RKnee = BasePlayer->get_bone_transform(RustStructs::bones::r_knee)->get_position();
					Vector2 LKneeLoc;
					Vector2 RKneeLoc;

					auto LAnkle = BasePlayer->get_bone_transform(RustStructs::bones::l_ankle_scale)->get_position();
					auto RAnkle = BasePlayer->get_bone_transform(RustStructs::bones::r_ankle_scale)->get_position();
					Vector2 LAnkleLoc;
					Vector2 RAnkleLoc;

					UnityEngine::WorldToScreen(HeadBone, HeadLoc);
					UnityEngine::WorldToScreen(NeckBone, NeckLoc);
					UnityEngine::WorldToScreen(Spine, SpineLoc);

					UnityEngine::WorldToScreen(LShoulder, LShoulderLoc);
					UnityEngine::WorldToScreen(RShoulder, RShoulderLoc);

					UnityEngine::WorldToScreen(LElbow, LElbowLoc);
					UnityEngine::WorldToScreen(RElbow, RElbowLoc);

					UnityEngine::WorldToScreen(LWrist, LWristLoc);
					UnityEngine::WorldToScreen(RWrist, RWristLoc);

					UnityEngine::WorldToScreen(LHip, LHipLoc);
					UnityEngine::WorldToScreen(RHip, RHipLoc);

					UnityEngine::WorldToScreen(LKnee, LKneeLoc);
					UnityEngine::WorldToScreen(RKnee, RKneeLoc);

					UnityEngine::WorldToScreen(LAnkle, LAnkleLoc);
					UnityEngine::WorldToScreen(RAnkle, RAnkleLoc);

					//Draw Skeleton
					if (!HeadLoc.IsZero() && !NeckLoc.IsZero() && !SpineLoc.IsZero() && !LShoulderLoc.IsZero() && !RShoulderLoc.IsZero() && !LElbowLoc.IsZero() && !RElbowLoc.IsZero() && !LWristLoc.IsZero() && !RWristLoc.IsZero() && !LHipLoc.IsZero() && !RHipLoc.IsZero() && !LKneeLoc.IsZero() && !RKneeLoc.IsZero() && !LAnkleLoc.IsZero() && !RAnkleLoc.IsZero()) {
						/* connector */
						UnityEngine::GL::Line(Vector2(HeadLoc.x, HeadLoc.y), Vector2(NeckLoc.x, NeckLoc.y), SkeletonColor);
						UnityEngine::GL::Line(Vector2(NeckLoc.x, NeckLoc.y), Vector2(SpineLoc.x, SpineLoc.y), SkeletonColor);

						/* upper left */
						/* upper spine -> left shoulder */
						UnityEngine::GL::Line(Vector2(NeckLoc.x, NeckLoc.y), Vector2(LShoulderLoc.x, LShoulderLoc.y), SkeletonColor);

						/* left shoulder -> left elbow */
						UnityEngine::GL::Line(Vector2(LShoulderLoc.x, LShoulderLoc.y), Vector2(LElbowLoc.x, LElbowLoc.y), SkeletonColor);

						/* left elbow -> left wrist*/
						UnityEngine::GL::Line(Vector2(LElbowLoc.x, LElbowLoc.y), Vector2(LWristLoc.x, LWristLoc.y), SkeletonColor);

						/* upper right */
						/* upper spine -> right shoulder */
						UnityEngine::GL::Line(Vector2(NeckLoc.x, NeckLoc.y), Vector2(RShoulderLoc.x, RShoulderLoc.y), SkeletonColor);

						/* right shoulder -> right elbow */
						UnityEngine::GL::Line(Vector2(RShoulderLoc.x, RShoulderLoc.y), Vector2(RElbowLoc.x, RElbowLoc.y), SkeletonColor);

						/* right elbow -> right wrist*/
						UnityEngine::GL::Line(Vector2(RElbowLoc.x, RElbowLoc.y), Vector2(RWristLoc.x, RWristLoc.y), SkeletonColor);

						/* lower left */
						/* lower spine -> left hip */
						UnityEngine::GL::Line(Vector2(SpineLoc.x, SpineLoc.y), Vector2(LHipLoc.x, LHipLoc.y), SkeletonColor);

						/* left hip -> left knee */
						UnityEngine::GL::Line(Vector2(LHipLoc.x, LHipLoc.y), Vector2(LKneeLoc.x, LKneeLoc.y), SkeletonColor);

						/* left knee -> left ankle */
						UnityEngine::GL::Line(Vector2(LKneeLoc.x, LKneeLoc.y), Vector2(LAnkleLoc.x, LAnkleLoc.y), SkeletonColor);

						/* lower right */
						/* lower spine -> right hip */
						UnityEngine::GL::Line(Vector2(SpineLoc.x, SpineLoc.y), Vector2(RHipLoc.x, RHipLoc.y), SkeletonColor);

						/* right hip -> right knee */
						UnityEngine::GL::Line(Vector2(RHipLoc.x, RHipLoc.y), Vector2(RKneeLoc.x, RKneeLoc.y), SkeletonColor);

						/* right knee -> right ankle */
						UnityEngine::GL::Line(Vector2(RKneeLoc.x, RKneeLoc.y), Vector2(RAnkleLoc.x, RAnkleLoc.y), SkeletonColor);
					}
				}

				if (m_settings::Skeleton)
				{
					auto HeadBone = BasePlayer->get_bone_transform(RustStructs::bones::head)->get_position();
					Vector2 HeadLocation;
					UnityEngine::WorldToScreen(HeadBone, HeadLocation);
					auto eyes = BasePlayer->eyes()->HeadForward();
					Vector2 Forwards;
					UnityEngine::WorldToScreen(HeadBone + eyes / 2, Forwards);

					if (!HeadLocation.IsZero() && !Forwards.IsZero())
						UnityEngine::GL::Line(Vector2(HeadLocation.x, HeadLocation.y), Vector2(Forwards.x, Forwards.y), Color::White());
				}

				//{
				//	auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
				//	auto LocalPos = LocalPlayer->model()->get_positionz();
				//	auto LocalEyes = LocalPlayer->eyes();

				//	auto PlayerPos = BasePlayer->model()->get_positionz();

				//	float center_x = (float)(UnityEngine::screen_size.x) / 2, center_y = (float)(UnityEngine::screen_size.y) / 2;

				//	Vector3 euler_angles = to_euler_angles(LocalEyes->get_rotation());

				//	const Vector2 position = Vector2(LocalPos.x - PlayerPos.x, LocalPos.z - PlayerPos.z).normalize();

				//	float angle = Math::my_atan2( position.x, position.y ) * 57.29578f - 180.f - euler_angles.y;

				//	Vector2 pos_0 = cos_tan_horizontal(angle, 10.f, center_x, center_y, 140);
				//	Vector2 pos_1 = cos_tan_horizontal(angle + 2.f, 10.f, center_x, center_y, 130);
				//	Vector2 pos_2 = cos_tan_horizontal(angle - 2.f, 10.f, center_x, center_y, 130);

				//	UnityEngine::GL().Triangle(Vector2(pos_0.x + 1, pos_0.y + 1), Vector2(pos_1.x + 1, pos_1.y + 1), Vector2(pos_2.x + 1, pos_2.y + 1), Color(0, 0, 0, 150.f));
				//	UnityEngine::GL().Triangle(Vector2(pos_0.x, pos_0.y), Vector2(pos_1.x, pos_1.y), Vector2(pos_2.x, pos_2.y), BoxColor);
				//}

				if (m_settings::SelectedHealthBar == 1)
				{
					float bar_health = 0;
					auto health = BasePlayer->_health();
					//auto max_health = base_player->_maxHealth();
					float max_health = 100.f;
					float draw_health = health;

					if (health > max_health)
					{
						draw_health = max_health;
					}

					const auto bar_width = 30;
					bar_health = (bar_width / max_health) * draw_health;

					auto bar_color = Color::Green();
					if (health > 50.f)
					{
						bar_color = Color::Green();
					}
					else if (health > 20.f && health < 40.f)
					{
						bar_color = Color::Orange();
					}
					else if (health < 20.f)
					{
						bar_color = Color::Red();
					}

					UnityEngine::GL::RectangleFilled(Vector2(footPos.x - (bar_width / 2), bo.bottom + yoffset), Vector2(footPos.x + (bar_width / 2), bo.bottom + yoffset + 3.f), Color::Black());

					UnityEngine::GL::RectangleFilled(Vector2(footPos.x - (bar_width / 2), bo.bottom + yoffset), Vector2((footPos.x - (bar_width / 2)) + bar_health, bo.bottom + yoffset + 3.f), bar_color);
					UnityEngine::GL::Rectangle(Vector2(footPos.x - (bar_width / 2), bo.bottom + yoffset), Vector2(footPos.x + (bar_width / 2), bo.bottom + yoffset + 4.f), Color::Black());
					yoffset += 13;
				}

				if (m_settings::SelectedHealthBar == 2) {
					float bar_health = 0;
					auto health = BasePlayer->_health();
					//auto max_health = base_player->_maxHealth();
					float max_health = 100.f;
					float draw_health = health;

					if (health > max_health)
					{
						draw_health = max_health;
					}

					bar_health = (box_height / max_health) * draw_health;

					auto bar_color = Color::Green();
					if (health > 50.f)
					{
						bar_color = Color::Green();
					}
					else if (health > 20.f && health < 40.f)
					{
						bar_color = Color::Orange();
					}
					else if (health < 20.f)
					{
						bar_color = Color::Red();
					}

					//fill_box_({ bo.left - 5.0f, bo.top , 2.f, box_height }, Color::Black());
					//fill_box_({ bo.left - 5.0f, bo.bottom , 2.f, -current_health_y }, Color::Green());

					int width = 2.f;
					UnityEngine::GL::RectangleFilled(Vector2(bo.left - 5.0f, bo.top), Vector2(bo.left - 5.0f + width, bo.top + box_height), Color::Black());
					UnityEngine::GL::RectangleFilled(Vector2(bo.left - 5.0f, bo.bottom), Vector2(bo.left - 5.0f + width, bo.bottom + -bar_health), bar_color);
					UnityEngine::GL::Rectangle(Vector2(bo.left - 5.0f, bo.top), Vector2(bo.left - 5.0f + width, bo.top + box_height), Color::Black());
				}

				if (m_settings::nameEsp)
				{
					if (m_settings::TagsVisCheck)
					{
						if (npc)
						{
							std::string player_name = XS("Scientist");
							char str[256];
							sprintf(str, XS("[%dm]"), (int)distance);
							player_name = player_name + " " + str;

							UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), player_name.c_str(), BoxColor, Color::Black(ColorSettings::BoxEsp_Color.a), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
						}
						else
						{
							if (IsAddressValid(BasePlayer->get_displayName())) //decrypted
							{
								std::string player_name = utf16_to_utf8(BasePlayer->get_displayName()->c_str());
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), player_name.c_str(), BoxColor, Color::Black(ColorSettings::BoxEsp_Color.a), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
							}

						}
						yoffset += 13;
					}
					else
					{
						if (npc)
						{
							std::string player_name = XS("Scientist");
							char str[256];
							sprintf(str, XS("[%dm]"), (int)distance);
							player_name = player_name + " " + str;

							UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), player_name.c_str(), NameTag_Color, Color::Black(ColorSettings::Username_Color.a), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
						}
						else
						{
							if (IsAddressValid(BasePlayer->get_displayName())) //decrypted
							{
								std::string player_name = utf16_to_utf8(BasePlayer->get_displayName()->c_str());
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), player_name.c_str(), NameTag_Color, Color::Black(ColorSettings::Username_Color.a), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
							}
						}

						yoffset += 13;
					}
				}

				if (m_settings::ShowAlerts)
				{
					auto playerpos = BasePlayer->get_bone_transform(48)->get_position();
					auto localpos = LocalPlayer->get_bone_transform(48)->get_position();
					auto distance = playerpos.Distance(localpos);
					auto fwd = playerpos + (BasePlayer->eyes()->BodyForward() * distance);

					auto dist = fwd.Distance(localpos);
					auto r = (distance / 50.f); r = (r < 1.f ? 1.f : r);
					if (dist < r)
					{
						std::string name = utf16_to_utf8(BasePlayer->get_displayName()->c_str());
						std::string player_name = XS("");
						char str[256];
						sprintf(str, XS("[Warning] %s is looking at you!"), name);
						player_name = player_name + " " + str;
						float center_x = (float)(UnityEngine::screen_size.x) / 2, center_y = (float)(UnityEngine::screen_size.y) / 2;
						UnityEngine::GL().TextCenter(Vector2(center_x, center_y - 425), player_name.c_str(), Color::Red(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

					}
				}


				if (m_settings::helditem)
				{
					const auto item = BasePlayer->ActiveItem();
					if (IsAddressValid(item))
					{
						auto info = item->info();

						if (IsAddressValid(info))
						{
							auto display_name = info->GetDisplayName(item);
							if (IsAddressValid(display_name))
							{
								auto held_item = utf16_to_utf8(display_name->c_str());
								auto ItemID = info->itemid();

								if (m_settings::TagsVisCheck)
								{
									UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), held_item.c_str(), BoxColor, Color::Black(ColorSettings::BoxEsp_Color.a), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
									yoffset += 13;
								}
								else
								{
									UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), held_item.c_str(), HeldItem_Color, Color::Black(ColorSettings::Helditem_Color.a), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
									yoffset += 13;
								}

								//switch (m_settings::HeldItemType)
								//{
								//case 0: //name
								//{
								//	if (m_settings::TagsVisCheck)
								//	{
								//		UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), held_item.c_str(), BoxColor, Color::Black(ColorSettings::BoxEsp_Color.a), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
								//		yoffset += 13;
								//	}
								//	else
								//	{
								//		UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), held_item.c_str(), HeldItem_Color, Color::Black(ColorSettings::Helditem_Color.a), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
								//		yoffset += 13;
								//	}
								//}
								//	break;
								//case 1://unity icon
								//{
								//	auto IconSprite = info->FindIconSprite(info->itemid());

								//	if (IconSprite) {
								//		auto IconTexture = IconSprite->get_texture();

								//		yoffset += 4;
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - 12, footPos.y + yoffset - 12), Vector2(24, 24), IconTexture, Color::White());
								//		yoffset += 24;
								//	}
								//}
								//break;
								//case 2:// custom icon
								//{
								//	if (ItemID == 1545779598 || ItemID == 4155929904 || ItemID == 2959469637) {
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (26 / 2), footPos.y + yoffset - (10 / 2)), Vector2(26, 10), AK47Icon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 1588298435 || ItemID == 3516600001)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (26 / 2), footPos.y + yoffset - (8 / 2)), Vector2(26, 8), BoltyIcon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 884424049)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (32 / 2), footPos.y + yoffset - (10 / 2)), Vector2(32, 10), CompoundBowIcon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 1965232394)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (23 / 2), footPos.y + yoffset - (8 / 2)), Vector2(23, 8), CrossbowIcon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 1796682209)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (21 / 2), footPos.y + yoffset - (12 / 2)), Vector2(21, 12), CustomSMGIcon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 3529783679)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (24 / 2), footPos.y + yoffset - (6 / 2)), Vector2(24, 6), DoubleBarrelIcon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 4219022635)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (14 / 2), footPos.y + yoffset - (8 / 2)), Vector2(14, 8), EokaIcon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 3080424799)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (22 / 2), footPos.y + yoffset - (8 / 2)), Vector2(22, 8), HMLmgIcon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 1443579727)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (31 / 2), footPos.y + yoffset - (8 / 2)), Vector2(31, 8), HuntingBowIcon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 2482412119)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (21 / 2), footPos.y + yoffset - (10 / 2)), Vector2(21, 10), LR300Icon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 28201841)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (28 / 2), footPos.y + yoffset - (10 / 2)), Vector2(28, 10), M39Icon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 3442404277)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (18 / 2), footPos.y + yoffset - (12 / 2)), Vector2(18, 12), M92Icon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 2225388408)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (32 / 2), footPos.y + yoffset - (10 / 2)), Vector2(32, 10), M249Icon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 1318558775)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (21 / 2), footPos.y + yoffset - (9 / 2)), Vector2(21, 9), Mp4a4Icon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 818877484 || ItemID == 1914691295)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (15 / 2), footPos.y + yoffset - (12 / 2)), Vector2(15, 12), PistolIcon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 795371088 || ItemID == 2927685355)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (26 / 2), footPos.y + yoffset - (7 / 2)), Vector2(26, 7), PumpShotgunIcon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 1373971859)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (21 / 2), footPos.y + yoffset - (11 / 2)), Vector2(21, 11), PythonIcon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 649912614)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (18 / 2), footPos.y + yoffset - (12 / 2)), Vector2(18, 12), RevolverIcon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 3390104151)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (26 / 2), footPos.y + yoffset - (9 / 2)), Vector2(26, 9), SarIcon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 4253526834)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (25 / 2), footPos.y + yoffset - (6 / 2)), Vector2(25, 6), Spas12Icon, Color::White());
								//		yoffset += 13;
								//	}
								//	else if (ItemID == 2536594571)
								//	{
								//		UnityEngine::GL().DrawIcon(Vector2(footPos.x - (28 / 2), footPos.y + yoffset - (10 / 2)), Vector2(28, 10), ThompsonIcon, Color::White());
								//		yoffset += 13;
								//	}
								//}
								//	break;
								//}
								
							}
						}
					}
				}

				if (m_settings::ammoESP) {
					const auto item = BasePlayer->ActiveItem();
					if (IsAddressValid(item))
					{
						auto info = item->info();

						if (IsAddressValid(info))
						{
							auto display_name = info->GetDisplayName(item);
							if (IsAddressValid(display_name))
							{
								auto BaseProjectile = BasePlayer->GetHeldEntityCast<AssemblyCSharp::BaseProjectile>();
								if (IsAddressValid(BaseProjectile))
								{
									auto Magazine = BaseProjectile->primaryMagazine();
									if (IsAddressValid(Magazine))
									{
										std::string AmmoType;
										auto ammoType = Magazine->ammoType();
										auto AmmoID = ammoType->itemid();

										if (Magazine->contents() <= 0)
											AmmoType = XS("Empty");
										else if (AmmoID == -1211166256)
											AmmoType = XS("5.56 Ammo");
										else if (AmmoID == -1321651331)
											AmmoType = XS("Explosive 5.56 Ammo");
										else if (AmmoID == 1712070256)
											AmmoType = XS("HV 5.56 Ammo");
										else if (AmmoID == 605467368)
											AmmoType = XS("Incendiary 5.56 Ammo");
										else if (AmmoID == 785728077)
											AmmoType = XS("Pistol Bullet");
										else if (AmmoID == -1691396643)
											AmmoType = XS("HV Pistol Bullet");
										else if (AmmoID == 51984655)
											AmmoType = XS("Incendiary Pistol Bullet");
										else if (AmmoID == -2097376851)
											AmmoType = XS("Nailgun Nails");
										else if (AmmoID == 550753330)
											AmmoType = XS("SnowBalls");
										else if (AmmoID == -1685290200)
											AmmoType = XS("12 Gauge Buckshot");
										else if (AmmoID == -1036635990)
											AmmoType = XS("12 Gauge Incendiary Shell");
										else if (AmmoID == -727717969)
											AmmoType = XS("12 Gauge Slug");
										else if (AmmoID == 588596902)
											AmmoType = XS("Handmade Shell");
										else if (AmmoID == 1055319033)
											AmmoType = XS("40mm Shotgun Round");
										else if (AmmoID == 349762871)
											AmmoType = XS("40mm HE Grenade");
										else if (AmmoID == 915408809)
											AmmoType = XS("40mm Smoke Grenade");
										else if (AmmoID == -1841918730)
											AmmoType = XS("High Velocity Rocket");
										else if (AmmoID == 1296788329)
											AmmoType = XS("Homing Missile");
										else if (AmmoID == -17123659)
											AmmoType = XS("Smoke Rocket WIP!!!!");
										else if (AmmoID == 1638322904)
											AmmoType = XS("Incendiary Rocket");
										else if (AmmoID == -1843426638)
											AmmoType = XS("MLRS Rocket");
										else if (AmmoID == -742865266)
											AmmoType = XS("Rocket");
										else if (AmmoID == -384243979)
											AmmoType = XS("SAM Ammo");
										else
											AmmoType = XS("Unknown");

										UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), AmmoType.c_str(), HeldItem_Color, Color::Black(), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
										yoffset += 13;
									}
								}
							}
						}
					}
				}

				if (m_settings::ShowOutside || m_settings::ShowInside)
				{
					Vector3 position = BasePlayer->get_bone_transform(47)->get_position() + Vector3(0.f, 500.f, 0.f);
					UnityEngine::RaycastHit hitInfo;
					if (AssemblyCSharp::GamePhysics::Trace(UnityEngine::Ray(BasePlayer->get_bone_transform(47)->get_position(), position), 0.f, hitInfo, 500.f, 2097152, RustStructs::QueryTriggerInteraction::Ignore, nullptr))
					{
						if (m_settings::ShowInside) {
							auto Inside_Color = Color{ ColorSettings::Inside_Color.r, ColorSettings::Inside_Color.g, ColorSettings::Inside_Color.b, ColorSettings::Inside_Color.a };
							UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), XS("Inside"), Inside_Color, Color::Black(ColorSettings::Inside_Color.a), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
							yoffset += 13;
						}
					}
					else
					{
						if (m_settings::ShowOutside) {
							auto Outside_Color = Color{ ColorSettings::Outside_Color.r, ColorSettings::Outside_Color.g, ColorSettings::Outside_Color.b, ColorSettings::Outside_Color.a };
							UnityEngine::GL().TextCenter(Vector2(footPos.x, footPos.y + yoffset), XS("Outside"), Outside_Color, Color::Black(ColorSettings::Outside_Color.a), m_settings::fontsize, m_settings::OutlinedText, m_settings::ShadedText);
							yoffset += 13;
						}
					}
				}



				if (m_settings::PlayerChams)
				{

						auto playerModel = BasePlayer->playerModel();
						if (IsAddressValid(playerModel))
						{
							auto _multiMesh = playerModel->_multiMesh();
							if (IsAddressValid(_multiMesh))
							{
								auto Renderers = _multiMesh->get_Renderers();
								if (IsAddressValid(Renderers))
								{
									auto Renderers_Items = Renderers->_items;
									if (Renderers_Items)
									{
										auto Renderers_Size = Renderers->_size;
										if (Renderers_Size) {

											for (int i = 0; i < Renderers_Size; i++) {
												auto MainRenderer = Renderers_Items->m_Items[i];

												if (IsAddressValid(MainRenderer))
												{
													auto material = MainRenderer->material();

													if (!IsAddressValid(material))
														continue;

													int selectedChams = m_settings::SelectedChams;

													switch (selectedChams) {
													case 1:
														if (FireBundleA) {
															if (!FireShaderA) //Blue Fire
																FireShaderA = FireBundleA->LoadAsset<UnityEngine::Shader>(XS("new amplifyshader.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

															if (!FireMaterialA)
																FireMaterialA = FireBundleA->LoadAsset<UnityEngine::Material>(XS("fire.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

															if (material->shader() != FireShaderA)
															{
																MainRenderer->set_material(FireMaterialA);
																FireMaterialA->set_shader(FireShaderA);
															}
														}
														break;
													case 2:
														if (FireBundleB) {
															if (!FireShaderB) //Red Fire
																FireShaderB = FireBundleB->LoadAsset<UnityEngine::Shader>(XS("new amplifyshader.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

															if (!FireMaterialB)
																FireMaterialB = FireBundleB->LoadAsset<UnityEngine::Material>(XS("fire2.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

															if (material->shader() != FireShaderB)
															{
																MainRenderer->set_material(FireMaterialB);
																FireMaterialB->set_shader(FireShaderB);
															}
														}
														break;
													case 3:
														if (LightningBundle) {
															if (!LightningShader) //Lightning
																LightningShader = LightningBundle->LoadAsset<UnityEngine::Shader>(XS("poiyomi pro.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

															if (!LightningMaterial)
																LightningMaterial = LightningBundle->LoadAsset<UnityEngine::Material>(XS("lightning.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

															if (material->shader() != LightningShader)
															{
																MainRenderer->set_material(LightningMaterial);
																LightningMaterial->set_shader(LightningShader);
															}
														}
														break;
													case 4:
														if (GeometricBundle) {
															if (!GeometricShader) //Geometric Disolve
																GeometricShader = GeometricBundle->LoadAsset<UnityEngine::Shader>(XS("poiyomi pro geometric dissolve.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

															if (!GeometricMaterial)
																GeometricMaterial = GeometricBundle->LoadAsset<UnityEngine::Material>(XS("galaxy.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

															if (material->shader() != GeometricShader)
															{
																MainRenderer->set_material(GeometricMaterial);
																GeometricMaterial->set_shader(GeometricShader);
															}
														}
														break;
													case 5:
														if (GalaxyBundle) {
															if (!GalaxyShader) //Galaxy
																GalaxyShader = GalaxyBundle->LoadAsset<UnityEngine::Shader>(XS("galaxymaterial.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

															if (!GalaxyMaterial)
																GalaxyMaterial = GalaxyBundle->LoadAsset<UnityEngine::Material>(XS("galaxymaterial_12.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

															if (material->shader() != GalaxyShader)
															{
																MainRenderer->set_material(GalaxyMaterial);
																GalaxyMaterial->set_shader(GalaxyShader);
															}
														}
														break;
													case 6:
														if (WireFrameBundle) {
															if (!WireFrameShader) //Galaxy
																WireFrameShader = WireFrameBundle->LoadAsset<UnityEngine::Shader>(XS("poiyomi pro wireframe.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

															if (!WireFrameMaterial)
																WireFrameMaterial = WireFrameBundle->LoadAsset<UnityEngine::Material>(XS("wireframe.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

															if (material->shader() != WireFrameShader)
															{
																MainRenderer->set_material(WireFrameMaterial);
																WireFrameMaterial->set_shader(WireFrameShader);
																//WireFrameMaterial->SetColor("_Color", Color::Red());
															}
														}
														break;
													case 7:
														if (ColorBundle) {
															auto VisibleChams_Color = Color{ ColorSettings::VisibleChams_Color.r, ColorSettings::VisibleChams_Color.g, ColorSettings::VisibleChams_Color.b, ColorSettings::VisibleChams_Color.a };
															auto InvisibleChams_Color = Color{ ColorSettings::InvisibleChams_Color.r, ColorSettings::InvisibleChams_Color.g, ColorSettings::InvisibleChams_Color.b, ColorSettings::InvisibleChams_Color.a };
															auto ScientistChams_Color = Color{ ColorSettings::ScientistChams_Color.r, ColorSettings::ScientistChams_Color.g, ColorSettings::ScientistChams_Color.b, ColorSettings::ScientistChams_Color.a };

															if (!ColorShader) //Galaxy
																ColorShader = ColorBundle->LoadAsset<UnityEngine::Shader>(XS("chams.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

															if (material->shader() != ColorShader)
															{
																material->set_shader(ColorShader);
																material->SetColor(XS("_ColorVisible"), VisibleChams_Color);
																material->SetColor(XS("_ColorBehind"), InvisibleChams_Color);

																if (npc)
																{
																	material->SetColor(XS("_ColorVisible"), ScientistChams_Color);
																	material->SetColor(XS("_ColorBehind"), ScientistChams_Color);
																}
															}
														}
														break;
													case 8:
														if (RPBGalaxyBundle) {
															if (!RPBGalaxyShader) //Galaxy
																RPBGalaxyShader = RPBGalaxyBundle->LoadAsset<UnityEngine::Shader>(XS("galaxymaterial.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

															if (!RPBGalaxyMaterial)
																RPBGalaxyMaterial = RPBGalaxyBundle->LoadAsset<UnityEngine::Material>(XS("galaxymaterial_03.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

															if (material->shader() != RPBGalaxyShader)
															{
																MainRenderer->set_material(RPBGalaxyMaterial);
																RPBGalaxyMaterial->set_shader(RPBGalaxyShader);
															}
														}
														break;
													case 9:
														if (GlitterBundle) {
															auto GChams_GlitterColor = Color{ ColorSettings::GChams_GlitterColor.r, ColorSettings::GChams_GlitterColor.g, ColorSettings::GChams_GlitterColor.b, ColorSettings::GChams_GlitterColor.a };

															if (!GlitterShader) //Glitter
																GlitterShader = GlitterBundle->LoadAsset<UnityEngine::Shader>(XS("el_glitter.shader"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Shader"))));

															if (!GlitterMaterial)
																GlitterMaterial = GlitterBundle->LoadAsset<UnityEngine::Material>(XS("el_glitter.mat"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Material"))));

															if (material->shader() != GlitterShader)
															{
																MainRenderer->set_material(GlitterMaterial);
																GlitterMaterial->set_shader(GlitterShader);
																GlitterMaterial->SetColor("_FresnelColor", GChams_GlitterColor);
																GlitterMaterial->SetColor("_GlitterColor", GChams_GlitterColor);
																GlitterMaterial->SetColor("_ExteriorDesignColor", GChams_GlitterColor);
															}
														}
														break;
													}
												}

											}
										}
									}
								}
							}
					}
				}
			}
		}	
	}
}


inline void DoMeleeAttack(AssemblyCSharp::BasePlayer* target, AssemblyCSharp::BaseMelee* baseprojectile, bool is_player = false) {
	if (!IsAddressValid(target))
		return;

	Vector3 local_position = UnityEngine::Camera::get_main()->get_positionz();

	if (baseprojectile->nextAttackTime() <= UnityEngine::Time::get_time())
	{
		if (baseprojectile->timeSinceDeploy() > baseprojectile->deployDelay())
		{
			auto g_hit_test_class = CIl2Cpp::FindClass(XS(""), XS("HitTest"));
			auto g_hit_test = CIl2Cpp::il2cpp_object_new((void*)g_hit_test_class);

			if (IsAddressValid(g_hit_test))
			{
				auto hit_test = (AssemblyCSharp::HitTest*)g_hit_test;
				if (IsAddressValid(hit_test))
				{
					UnityEngine::Ray ray = UnityEngine::Ray(local_position, (target->get_bone_transform(47)->get_position() - local_position).Normalized());

					UnityEngine::Transform* trans = is_player ? target->get_bone_transform(47) : target->get_transform();
					if (!trans)
						return;

					hit_test->MaxDistance() = 1000;
					hit_test->HitTransform() = trans;
					hit_test->AttackRay() = ray;
					hit_test->DidHit() = true;
					hit_test->HitEntity() = target;
					hit_test->HitPoint() = trans->InverseTransformPoint(target->get_bone_transform(47)->get_position());
					hit_test->HitNormal() = Vector3(0, 0, 0);
					hit_test->damageProperties() = baseprojectile->damageProperties();

					baseprojectile->StartAttackCooldown(baseprojectile->repeatDelay());
					return baseprojectile->ProcessAttack(hit_test);
				}
			}

		}
	}
};

void Visuals::CachePlayers()
{
	if (!InGame)
		return;

	if (!IsAddressValid(Features().LocalPlayer))
		return;

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping())
		return;

	if (!this->VisiblePlayerList)
		this->VisiblePlayerList = AssemblyCSharp::BasePlayer::visiblePlayerList();

	auto Vals = VisiblePlayerList->vals;
	auto size = Vals->count;
	auto buffer = Vals->buffer;
	

	for (std::int32_t index = 0; index < size; index++)
	{
		auto BasePlayer = buffer->m_Items[index];
		if (!IsAddressValid(BasePlayer))
			continue;

		if (BasePlayer->IsLocalPlayer())
			continue;

		if (m_settings::SilentMelee)
		{
			auto BaseProjectile = Features().LocalPlayer->GetHeldEntityCast<AssemblyCSharp::BaseProjectile>();

			if (IsAddressValid(BaseProjectile))
			{


				if (BaseProjectile->IsA(AssemblyCSharp::BaseMelee::StaticClass())
					|| BaseProjectile->IsA(AssemblyCSharp::JackHammer::StaticClass())
					&& !BaseProjectile->IsA(AssemblyCSharp::Planner::StaticClass()))
				{
					
					if (AssemblyCSharp::IsVisible(AssemblyCSharp::LocalPlayer::get_Entity()->eyes()->get_position(), BasePlayer->get_bone_transform(48)->get_position()))
					{
						auto world_position = BasePlayer->get_bone_transform(48)->get_position();
						auto local = AssemblyCSharp::LocalPlayer::get_Entity()->ClosestPoint(world_position);
						auto camera = AssemblyCSharp::LocalPlayer::get_Entity()->get_bone_transform(48)->get_position();

						if (camera.get_3d_dist(world_position) <= 4.5f)
						{
							DoMeleeAttack(BasePlayer, (AssemblyCSharp::BaseMelee*)BaseProjectile, true);
						}
					}
				}
			}
		}
	
		VisualsArrayTemp.push_back(VisualsVector(BasePlayer));
	}

	VisualsArray = VisualsArrayTemp;
	VisualsArrayTemp.clear();
}



bool ComputeBox(AssemblyCSharp::BasePlayer* base_player, Vector4& box)
{

	const auto transform = base_player->get_transform();

	if (!IsAddressValid(transform))
	{
		return false;
	}

	const auto& bounds = base_player->bounds();

	const auto center = bounds.m_Center;
	const auto extents = bounds.m_Extents;

	const auto mins = -extents;
	const auto maxs = extents;

	Vector3 corners[8] =
	{
		{ mins[0], mins[1], mins[2] },
		{ mins[0], maxs[1], mins[2] },
		{ maxs[0], maxs[1], mins[2] },
		{ maxs[0], mins[1], mins[2] },
		{ maxs[0], maxs[1], maxs[2] },
		{ mins[0], maxs[1], maxs[2] },
		{ mins[0], mins[1], maxs[2] },
		{ maxs[0], mins[1], maxs[2] },
	};

	const auto position = transform->get_position();
	const auto angles = transform->get_eulerAngles();

	box.x = UnityEngine::Screen::get_width();
	box.y = UnityEngine::Screen::get_height();
	box.z = -1.f;
	box.w = -1.f;

	const auto yaw = UnityEngine::ToRadians(angles[1]);

	const auto sine = -Math::sinf(yaw);
	const auto cosine = Math::cosf(yaw);

	for (const auto& corner : corners)
	{
		Vector3 world =
		{
			(position[0] + center[0] + (corner[0] * cosine - corner[2] * sine)),
			(position[1] + center[1] + (corner[1])),
			(position[2] + center[2] + (corner[0] * sine + corner[2] * cosine)),
		};

		Vector3 screen = { };

		if (UnityEngine::WorldToScreen2(world, screen))
		{
			box.x = minm(box.x, screen.x);
			box.y = minm(box.y, screen.y);
			box.z = maxx(box.z, screen.x);
			box.w = maxx(box.w, screen.y);
		}
	}

	return true;
}

void Visuals::RenderEntities()
{
	if (!InGame)
		return;

	if (!IsAddressValid(Features().LocalPlayer))
		return;

	for (auto CachedEntity : PrefabVectorList)
	{
		auto BaseEntity = CachedEntity.CachedEntity;
		if (!BaseEntity)
			continue;

		const auto prefab_name = BaseEntity->get_ShortPrefabName();

		Vector2 screen = { };

		if (!IsAddressValid(prefab_name))
			continue;


		auto name = prefab_name->c_str();

		if (UnityEngine::WorldToScreen(BaseEntity->get_positionz(), screen))
		{
			auto test_plr = static_cast<AssemblyCSharp::BasePlayer*>(BaseEntity);

			Vector2 render_pad(0.f, 0.f);
			Vector4 box = { };
			if (ComputeBox(test_plr, box))
			{
				if (box.z < 180.f || box.z < -180.f)
					continue;

				//Vector2 screen(box.x, box.y);
				Vector2 ScreenBox(box.x, box.y);

				const auto width = box.z - box.x;
				const auto height = box.w - box.y;

				float half = (box.z - box.x) / 2;

				auto distance = Features().LocalPlayer->get_transform()->get_position().Distance(BaseEntity->get_transform()->get_position());
				//float distance = 500;

				if (distance <= m_settings::MaxDroppedDistance)
				{
					if (m_settings::DroppedItems)
					{
						if (BaseEntity->IsA(AssemblyCSharp::WorldItem::StaticClass()))
						{
							auto world_item = static_cast<AssemblyCSharp::WorldItem*>(BaseEntity);

							if (world_item)
							{
								auto item = world_item->item();
								if (item)
								{
									auto name = item->GetItemName();

									if (name->c_str())
									{
										if (name->Contains("Muzzle") || name->Contains("Scope") ||
											name->Contains("Magazine") || name->Contains("flashlight") ||
											name->Contains("Holosight") || name->Contains("Lasersight") ||
											name->Contains("Sight") || name->Contains("Silencer") ||
											name->Contains("Front") || name->Contains("embrasure") ||
											name->Contains("Bars") || name->Contains("Netting") ||
											name->Contains("Prison") || name->Contains("Quarry") ||
											name->Contains("Building") || name->Contains("Chainlink") ||
											name->Contains("Lock") || name->Contains("Floor") ||
											name->Contains("Gate") || name->Contains("Wall") ||
											name->Contains("Barricade") || name->Contains("Door") ||
											name->Contains("Hatch") || name->Contains("Shutters") ||
											name->Contains("Pump Jack") || name->Contains("Ladder") ||
											name->Contains("Tower") || name->Contains("Window") ||
											name->Contains("Cupboard") || name->Contains("Knife") ||
											name->Contains("Club") || name->Contains("Mace") ||
											name->Contains("Machete") || name->Contains("Cleaver") ||
											name->Contains("sword") || name->Contains("fork") ||
											name->Contains("Paddle") || name->Contains("Spear") ||
											name->Contains("Bat") || name->Contains("Water") ||
											name->Contains("Snowball") || name->Contains("Bow") ||
											name->Contains("Eoka") || name->Contains("Flame") ||
											name->Contains("Nailgun") || name->Contains("bow") ||
											name->Contains("Revolver") || name->Contains("Shotgun") ||
											name->Contains("Homing Missile") || name->Contains("Pistol") ||
											name->Contains("Grenade Launcher") || name->Contains("Prototype") ||
											name->Contains("Custom SMG") || name->Contains("Thompson") ||
											name->Contains("M39 Rifle") || name->Contains("Semi-Automatic") ||
											name->Contains("MP5A4") || name->Contains("HMLMG") ||
											name->Contains("Bolt Action") || name->Contains("Launcher") ||
											name->Contains("Assault Rifle") || name->Contains("L96") ||
											name->Contains("LR-300") || name->Contains("M249") ||
											name->Contains("Workbench") || name->Contains("Animal Fat") ||
											name->Contains("Charcoal") || name->Contains("Cloth") ||
											name->Contains("Coal") || name->Contains("Crude Oil") ||
											name->Contains("Leather") || name->Contains("High Quality") ||
											name->Contains("Sulfur") || name->Contains("Wood") ||
											name->Contains("Metal Fragments") || name->Contains("Explosives") ||
											name->Contains("Gun Powder") || name->Contains("Metal Ore") ||
											name->Contains("Sulfur") || name->Contains("Stones") ||
											name->Contains("Scrap") || name->Contains("Fuel") ||
											name->Contains("Suit") || name->Contains("Gear") ||
											name->Contains("Pants") || name->Contains("Jacket") ||
											name->Contains("Gloves") || name->Contains("Facemask") ||
											name->Contains("Chest Plate") || name->Contains("Helmet") ||
											name->Contains("Kilt") || name->Contains("IcePick") ||
											name->Contains("Chainsaw") || name->Contains("Jackhammer") ||
											name->Contains("Icepick") || name->Contains("Pickaxe") ||
											name->Contains("Rocket") || name->Contains("Explosive") ||
											name->Contains("Satchel") || name->Contains("Grenade") ||
											name->Contains("Supply Signal") || name->Contains("Large Medkit") ||
											name->Contains("Medical") || name->Contains("Bandage") ||
											name->Contains("Torpedo") || name->Contains("12 Gauge") ||
											name->Contains("Rifle Ammo") || name->Contains("Shell") ||
											name->Contains("Road Signs") || name->Contains("Electric Fuse") ||
											name->Contains("Sewing Kit") || name->Contains("Sheet Metal") ||
											name->Contains("Rifle Body") || name->Contains("Rope") ||
											name->Contains("SMG Body") || name->Contains("Spring") ||
											name->Contains("Pipe") || name->Contains("Blade") ||
											name->Contains("Semi Automatic Body") || name->Contains("Tech Trash") ||
											name->Contains("Tarp") || name->Contains("Targeting Computer"))
										{

											//Weapon mods
											if (m_settings::HideWeaponMods)
											{
												if (name->Contains("Muzzle") || name->Contains("Scope") ||
													name->Contains("Magazine") || name->Contains("flashlight") ||
													name->Contains("Holosight") || name->Contains("Lasersight") ||
													name->Contains("Sight") || name->Contains("Silencer"))
													continue;
											}

											//Melee Items
											if (m_settings::HideMeleeItems)
											{
												if (name->Contains("Knife") || name->Contains("Club") ||
													name->Contains("Mace") || name->Contains("Machete") ||
													name->Contains("Cleaver") || name->Contains("sword") ||
													name->Contains("fork") || name->Contains("Paddle") ||
													name->Contains("Spear") || name->Contains("Bat"))
													continue;
											}

											//Tier 1 Weapons
											if (m_settings::HideTier1Weapons)
											{
												if (name->Contains("Water") || name->Contains("Shotgun") ||
													name->Contains("Snowball") || name->Contains("Bow") ||
													name->Contains("Eoka") || name->Contains("Flame") ||
													name->Contains("Nailgun") || name->Contains("bow") ||
													name->Contains("Revolver"))
													continue;
											}

											//Tier 2 Weapons
											if (m_settings::HideTier2Weapons)
											{
												if (name->Contains("Homing Missile") || name->Contains("Pistol") ||
													name->Contains("Grenade Launcher") || name->Contains("Prototype") ||
													name->Contains("Custom SMG") || name->Contains("Thompson") ||
													name->Contains("M39 Rifle") || name->Contains("Semi-Automatic") ||
													name->Contains("MP5A4"))
													continue;
											}

											//Tier 3 Weapons
											if (m_settings::HideTier3Weapons)
											{
												if (name->Contains("HMLMG") || name->Contains("Bolt Action") ||
													name->Contains("Launcher") || name->Contains("Assault Rifle") ||
													name->Contains("L96") || name->Contains("LR-300") ||
													name->Contains("M249"))
													continue;
											}

											//Workbench
											if (m_settings::HideWorkbenches)
											{
												if (name->Contains("Workbench"))
													continue;
											}

											//Resources
											if (m_settings::HideResources)
											{
												if (name->Contains("Animal Fat") || name->Contains("Charcoal") ||
													name->Contains("Cloth") || name->Contains("Coal") ||
													name->Contains("Crude Oil") || name->Contains("Fuel") ||
													name->Contains("Leather") || name->Contains("High Quality") ||
													name->Contains("Sulfur") || name->Contains("Wood") ||
													name->Contains("Metal Fragments") || name->Contains("Explosives") ||
													name->Contains("Gun Powder") || name->Contains("Metal Ore") || 
													name->Contains("Sulfur") || name->Contains("Stones") || 
													name->Contains("Scrap"))
													continue;
											}

											//Armor
											if (m_settings::HideArmor)
											{
												if (name->Contains("Suit") || name->Contains("Gear") ||
													name->Contains("Pants") || name->Contains("Jacket") ||
													name->Contains("Gloves") || name->Contains("Facemask") ||
													name->Contains("Chest Plate") || name->Contains("Helmet") ||
													name->Contains("Kilt"))
													continue;
											}

											//Tools
											if (m_settings::HideTools)
											{
												if (name->Contains("IcePick") || name->Contains("Pickaxe") ||
													name->Contains("Chainsaw") || name->Contains("Jackhammer") ||
													name->Contains("Icepick"))
													continue;
											}

											//Explosive
											if (m_settings::HideExplosive)
											{
												if (name->Contains("Rocket") || name->Contains("Explosive") ||
													name->Contains("Satchel") || name->Contains("Grenade") ||
													name->Contains("Supply Signal"))
													continue;
											}

											//Medical
											if (m_settings::HideMedical)
											{
												if (name->Contains("Large Medkit") || name->Contains("Medical") ||
													name->Contains("Bandage"))
													continue;
											}

											//Ammo
											if (m_settings::HideAmmo)
											{
												if (name->Contains("Torpedo") || name->Contains("12 Gauge") ||
													name->Contains("Rifle Ammo") || name->Contains("Shell"))
													continue;
											}

											//Component
											if (m_settings::HideComponents)
											{
												if (name->Contains("Road Signs") || name->Contains("Electric Fuse") ||
													name->Contains("Sewing Kit") || name->Contains("Sheet Metal") ||
													name->Contains("Rifle Body") || name->Contains("Rope") ||
													name->Contains("SMG Body") || name->Contains("Spring") ||
													name->Contains("Pipe") || name->Contains("Blade") ||
													name->Contains("Semi Automatic Body") || name->Contains("Tech Trash") ||
													name->Contains("Tarp") || name->Contains("Targeting Computer"))
													continue;
											}

											//LOG(XS("[DEBUG] %ls"), name->c_str());

											auto DroppedColor = Color{ ColorSettings::DroppedItems_Color.r, ColorSettings::DroppedItems_Color.g, ColorSettings::DroppedItems_Color.b, ColorSettings::DroppedItems_Color.a };

											std::string player_name = utf16_to_utf8(name->c_str());
											char str[256];
											sprintf(str, XS("[%dm]"), (int)distance);
											player_name = player_name + " " + str;

											UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), DroppedColor, Color::Black(ColorSettings::DroppedItems_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

											if (m_settings::DroppedItemsChams) {
												auto ChamsColor = Color{ ColorSettings::DroppedChams_Color.r, ColorSettings::DroppedChams_Color.g, ColorSettings::DroppedChams_Color.b, ColorSettings::DroppedChams_Color.a };

												auto g_render = BaseEntity->GetComponentsInChildren(FPSystem::Type::Renderer());
												if (IsAddressValid(g_render))
												{
													auto size = g_render->max_length;
													for (int i = 0; i < size; i++)
													{
														auto main_renderer = g_render->m_Items[i];
														if (!(main_renderer))
															continue;

														auto material = main_renderer->material();

														if (!IsAddressValid(material))
															continue;

														auto g_shader = UnityEngine::Shader::Find(XS("Hidden/Internal-Colored"));

														if (!IsAddressValid(g_shader))
															continue;

														if (g_shader != material->shader())
														{
															material->set_shader(g_shader);
														}
														material->SetInt(XS("_ZTest"), 8);
														material->SetColor(XS("_Color"), ChamsColor);

													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
		
				if (BaseEntity->IsA(AssemblyCSharp::CollectibleEntity::StaticClass()))
				{
					if (distance <= m_settings::MaxCollectableDistance)
					{
						if (m_settings::Hemp)
						{
							if (HASH("hemp-collectable") == Hash(name, false))
							{
								auto HempColor = Color{ ColorSettings::Hemp_Color.r, ColorSettings::Hemp_Color.g, ColorSettings::Hemp_Color.b, ColorSettings::Hemp_Color.a };

								std::string player_name = XS("Hemp");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), HempColor, Color::Black(ColorSettings::Hemp_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

								if (m_settings::CollectablesIcon)
								{
									UnityEngine::Texture2D* texture = nullptr;
									if (!texture)
									{
										texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(XS("clone.hemp.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
									}

									UnityEngine::GUI::SetColor(Color::White());
									UnityEngine::GUI::DrawTexture({ screen.x - 15, screen.y - m_settings::IconsScale, m_settings::IconsScale, m_settings::IconsScale }, texture);
								}
							}
						}

						if (HASH("diesel_collectable") == Hash(name, false))
						{
							if (m_settings::DieselBarrel)
							{
								auto DieselColor = Color{ ColorSettings::DieselBarrel_Color.r, ColorSettings::DieselBarrel_Color.g, ColorSettings::DieselBarrel_Color.b, ColorSettings::DieselBarrel_Color.a };

								std::string player_name = XS("Diesel");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), DieselColor, Color::Black(ColorSettings::DieselBarrel_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

								if (m_settings::CollectablesIcon)
								{
									UnityEngine::Texture2D* texture = nullptr;
									if (!texture)
									{
										texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(XS("diesel_barrel.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
									}

									UnityEngine::GUI::SetColor(Color::White());
									UnityEngine::GUI::DrawTexture({ screen.x - 15, screen.y - m_settings::IconsScale, m_settings::IconsScale, m_settings::IconsScale }, texture);
								}
							}
						}
					}
				}

				if (distance <= m_settings::MaxTCDistance)
				{
					if (m_settings::cupboard)
					{
						float half = (box.z - box.x) / 2;
						if (BaseEntity->IsA(AssemblyCSharp::BuildingPrivlidge::StaticClass()))
						{
							auto building_priv = reinterpret_cast<AssemblyCSharp::BuildingPrivlidge*>(BaseEntity);

							if (IsAddressValid(building_priv))
							{
								float yoffset = 0;

								auto DeployableColor = Color{ ColorSettings::Cupboard_Color.r, ColorSettings::Cupboard_Color.g, ColorSettings::Cupboard_Color.b, ColorSettings::Cupboard_Color.a };
								auto UpkeepColor = Color{ ColorSettings::CUpKeep_Color.r, ColorSettings::CUpKeep_Color.g, ColorSettings::CUpKeep_Color.b, ColorSettings::CUpKeep_Color.a };
								auto AuthListColor = Color{ ColorSettings::CAuthedPlayers_Color.r, ColorSettings::CAuthedPlayers_Color.g, ColorSettings::CAuthedPlayers_Color.b, ColorSettings::CAuthedPlayers_Color.a };

								int cachedUpkeepPeriodMinutes = building_priv->UpKeep();
								int days = cachedUpkeepPeriodMinutes / 1440;
								int hours = cachedUpkeepPeriodMinutes / 60;

								auto _health = reinterpret_cast<AssemblyCSharp::BaseCombatEntity*>(building_priv)->_health();
								auto _maxhealth = reinterpret_cast<AssemblyCSharp::BaseCombatEntity*>(building_priv)->_maxHealth();

								std::string player_name = XS("Tool Cupboard");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), DeployableColor, Color::Black(ColorSettings::Cupboard_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								yoffset += 12.f;

								if (m_settings::TC_Upkeep) {
									std::string upkeep = XS("Upkeep: ");
									char str2[256];
									sprintf(str2, XS("[%dh]"), (int)hours);
									upkeep = upkeep + " " + str2;

									UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), upkeep.c_str(), UpkeepColor, Color::Black(ColorSettings::CUpKeep_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
									yoffset += 12;
								}
								if (m_settings::TC_Health)
								{
									float draw_health = _health;
									float yoffsethealth = 7.f;
									if (_health > _maxhealth) {
										draw_health = _maxhealth;
									}

									const auto bar_width = 30;
									const auto bar_health = (bar_width / _maxhealth) * draw_health;
									auto bar_color = Color::Green();

									if (_health > 50.f) {
										bar_color = Color::Green();
									}
									else if (_health > 20.f && _health < 40.f) {
										bar_color = Color::Orange();
									}
									else if (_health < 20.f) {
										bar_color = Color::Red();
									}


									UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffset - 2.f), Vector2(screen.x + (bar_width / 2), screen.y + yoffset + 2.f), Color::Black());
									UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffset - 2.f), Vector2((screen.x - (bar_width / 2)) + bar_health, screen.y + yoffset + 2.f), bar_color);
									UnityEngine::GL::Rectangle(Vector2(screen.x - (bar_width / 2), screen.y + yoffset - 2.f), Vector2(screen.x + (bar_width / 2), screen.y + yoffset + 2.f), Color::Black());
									yoffset += 8.f;
								}

								if (m_settings::AuthorizedPlayers)
								{
									const auto authorized_players = building_priv->authorizedPlayers();
									if (IsAddressValid(authorized_players))
									{
										for (auto it = 0; it < authorized_players->_size; it++)
										{
											const auto current = authorized_players->_items->m_Items[it];
											if (IsAddressValid(current))
											{
												const auto str = current->username();
												if (IsAddressValid(str))
												{
													auto camera = UnityEngine::Camera::get_main();

													if (IsAddressValid(camera))
													{
														auto distance = camera->get_positionz().get_3d_dist(BaseEntity->get_positionz());

														if (distance <= m_settings::AuthorizedPlayersDistance)
														{
															char retstr[256];
															sprintf(retstr, XS("%s"), str->string_safe().c_str());

															UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), retstr, AuthListColor, Color::Black(ColorSettings::CAuthedPlayers_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
															yoffset += 12.f;
														}
													}

												}
											}
										}
									}
								}
							}

						}
					}
				}

				if (distance <= m_settings::MaxCrateDistance)
				{
					if (m_settings::BasicCrate)
					{
						if (BaseEntity->IsA(AssemblyCSharp::LootContainer::StaticClass()))
						{
							if (HASH("crate_basic") == Hash(name, false))
							{
								auto BasicCrate_Color = Color{ ColorSettings::BasicCrate_Color.r, ColorSettings::BasicCrate_Color.g, ColorSettings::BasicCrate_Color.b, ColorSettings::BasicCrate_Color.a };
								std::string player_name = XS("Basic Crate");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), BasicCrate_Color, Color::Black(ColorSettings::BasicCrate_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}

					if (m_settings::NormalCrate)
					{
						if (BaseEntity->IsA(AssemblyCSharp::LootContainer::StaticClass()))
						{
							if (HASH("crate_normal_2") == Hash(name, false) || HASH("crate_normal_2_food") == Hash(name, false) || HASH("crate_normal_2_medical") == Hash(name, false))
							{
								auto NormalCrate_Color = Color{ ColorSettings::NormalCrate_Color.r, ColorSettings::NormalCrate_Color.g, ColorSettings::NormalCrate_Color.b, ColorSettings::NormalCrate_Color.a };
								std::string player_name = XS("Normal Crate");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), NormalCrate_Color, Color::Black(ColorSettings::NormalCrate_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}

					if (m_settings::MilitaryCrate)
					{
						if (BaseEntity->IsA(AssemblyCSharp::LootContainer::StaticClass()))
						{
							if (HASH("crate_normal") == Hash(name, false))
							{
								auto MilitaryCrate_Color = Color{ ColorSettings::MilitaryCrate_Color.r, ColorSettings::MilitaryCrate_Color.g, ColorSettings::MilitaryCrate_Color.b, ColorSettings::MilitaryCrate_Color.a };
								std::string player_name = XS("Military Crate");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), MilitaryCrate_Color, Color::Black(ColorSettings::MilitaryCrate_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}

					if (m_settings::EliteCrate)
					{
						if (BaseEntity->IsA(AssemblyCSharp::LootContainer::StaticClass()))
						{
							if (HASH("crate_elite") == Hash(name, false))
							{
								auto EliteCrate_Color = Color{ ColorSettings::EliteCrate_Color.r, ColorSettings::EliteCrate_Color.g, ColorSettings::EliteCrate_Color.b, ColorSettings::EliteCrate_Color.a };

								std::string player_name = XS("Elite Crate");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), EliteCrate_Color, Color::Black(ColorSettings::EliteCrate_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}
				
				if (distance <= m_settings::MaxSupplyDropDistance)
				{
					if (m_settings::SupplyDrop)
					{
						if (BaseEntity->IsA(AssemblyCSharp::LootContainer::StaticClass()))
						{
							if (HASH("supply_drop") == Hash(name, false))
							{
								auto Airdrop_Color = Color{ ColorSettings::Airdrop_Color.r, ColorSettings::Airdrop_Color.g, ColorSettings::Airdrop_Color.b, ColorSettings::Airdrop_Color.a };

								std::string player_name = XS("Airdrop");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), Airdrop_Color, Color::Black(ColorSettings::Airdrop_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::CollectibleEntity::StaticClass()))
				{
					if (distance <= m_settings::MaxFoodDistance)
					{
						if (m_settings::Mushroom)
						{
							if (HASH("mushroom-cluster-6") == Hash(name, false) || HASH("mushroom-cluster-5") == Hash(name, false))
							{
								auto FoodColor = Color{ ColorSettings::Mushroom_Color.r, ColorSettings::Mushroom_Color.g, ColorSettings::Mushroom_Color.b, ColorSettings::Mushroom_Color.a };

								std::string player_name = XS("Mushroom");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), FoodColor, Color::Black(ColorSettings::Mushroom_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

								if (m_settings::FoodIcons)
								{
									UnityEngine::Texture2D* texture = nullptr;
									if (!texture)
									{
										texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(XS("mushroom.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
									}

									UnityEngine::GUI::SetColor(Color::White());
									UnityEngine::GUI::DrawTexture({ screen.x - 15, screen.y - m_settings::IconsScale, m_settings::IconsScale, m_settings::IconsScale }, texture);
								}
							}
						}

						if (m_settings::Pumpkin)
						{
							float half = (box.z - box.x) / 2;
							if (BaseEntity->IsA(AssemblyCSharp::CollectibleEntity::StaticClass()))
							{
								if (HASH("pumpkin-collectable") == Hash(name, false))
								{
									auto FoodColor = Color{ ColorSettings::Pumpkin_Color.r, ColorSettings::Pumpkin_Color.g, ColorSettings::Pumpkin_Color.b, ColorSettings::Pumpkin_Color.a };

									std::string player_name = XS("Pumpkin");
									char str[256];
									sprintf(str, XS("[%dm]"), (int)distance);
									player_name = player_name + " " + str;

									UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), FoodColor, Color::Black(ColorSettings::Pumpkin_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

									if (m_settings::FoodIcons)
									{
										UnityEngine::Texture2D* texture = nullptr;
										if (!texture)
										{
											texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(XS("pumpkin.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
										}

										UnityEngine::GUI::SetColor(Color::White());
										UnityEngine::GUI::DrawTexture({ screen.x - 15, screen.y - m_settings::IconsScale, m_settings::IconsScale, m_settings::IconsScale }, texture);
									}
								}
							}
						}
						
						if (m_settings::Corn)
						{
							float half = (box.z - box.x) / 2;
							if (BaseEntity->IsA(AssemblyCSharp::CollectibleEntity::StaticClass()))
							{
								if (HASH("corn-collectable") == Hash(name, false))
								{
									auto FoodColor = Color{ ColorSettings::Corn_Color.r, ColorSettings::Corn_Color.g, ColorSettings::Corn_Color.b, ColorSettings::Corn_Color.a };

									std::string player_name = XS("Corn");
									char str[256];
									sprintf(str, XS("[%dm]"), (int)distance);
									player_name = player_name + " " + str;

									UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), FoodColor, Color::Black(ColorSettings::Corn_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

									if (m_settings::FoodIcons)
									{
										UnityEngine::Texture2D* texture = nullptr;
										if (!texture)
										{
											texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(XS("corn.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
										}

										UnityEngine::GUI::SetColor(Color::White());
										UnityEngine::GUI::DrawTexture({ screen.x - 15, screen.y - m_settings::IconsScale, m_settings::IconsScale, m_settings::IconsScale }, texture);
									}
								}
							}
						}

						if (m_settings::Potato)
						{
							float half = (box.z - box.x) / 2;
							if (BaseEntity->IsA(AssemblyCSharp::CollectibleEntity::StaticClass()))
							{
								if (HASH("potato-collectable") == Hash(name, false))
								{
									auto FoodColor = Color{ ColorSettings::Potato_Color.r, ColorSettings::Potato_Color.g, ColorSettings::Potato_Color.b, ColorSettings::Potato_Color.a };

									std::string player_name = XS("Potato");
									char str[256];
									sprintf(str, XS("[%dm]"), (int)distance);
									player_name = player_name + " " + str;
									UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), FoodColor, Color::Black(ColorSettings::Potato_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

									if (m_settings::FoodIcons)
									{
										UnityEngine::Texture2D* texture = nullptr;
										if (!texture)
										{
											texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(XS("potato.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
										}

										UnityEngine::GUI::SetColor(Color::White());
										UnityEngine::GUI::DrawTexture({ screen.x - 15, screen.y - m_settings::IconsScale, m_settings::IconsScale, m_settings::IconsScale }, texture);
									}
								}
							}
						}
					}

					if (distance <= m_settings::MaxCollectableDistance) {

						if (m_settings::StoneCollectable)
						{
							if (HASH("stone-collectable") == Hash(name, false))
							{
								auto StoneColor = Color{ ColorSettings::StoneCollectable_Color.r, ColorSettings::StoneCollectable_Color.g, ColorSettings::StoneCollectable_Color.b, ColorSettings::StoneCollectable_Color.a };

								std::string player_name = XS("Stone Collectable");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), StoneColor, Color::Black(ColorSettings::StoneCollectable_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

						if (m_settings::MetalCollectable)
						{
							if (HASH("metal-collectable") == Hash(name, false))
							{
								auto MetalColor = Color{ ColorSettings::MetalCollectable_Color.r, ColorSettings::MetalCollectable_Color.g, ColorSettings::MetalCollectable_Color.b, ColorSettings::MetalCollectable_Color.a };

								std::string player_name = XS("Metal Collectable");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), MetalColor, Color::Black(ColorSettings::MetalCollectable_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

							}
						}

						if (m_settings::SulfurCollectable)
						{
							if (HASH("sulfur-collectable") == Hash(name, false))
							{
								auto SulfurColor = Color{ ColorSettings::SulfurCollectable_Color.r, ColorSettings::SulfurCollectable_Color.g, ColorSettings::SulfurCollectable_Color.b, ColorSettings::SulfurCollectable_Color.a };

								std::string player_name = XS("Sulfur Collectable");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), SulfurColor, Color::Black(ColorSettings::SulfurCollectable_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::ResourceEntity::StaticClass()))
				{
					if (distance <= m_settings::MaxOreDistance)
					{
						if (m_settings::StoneOre)
						{
							if (HASH("stone-ore") == Hash(name, false) || HASH("ore_stone") == Hash(name, false))
							{
								auto StoneColor = Color{ ColorSettings::StoneOre_Color.r, ColorSettings::StoneOre_Color.g, ColorSettings::StoneOre_Color.b, ColorSettings::StoneOre_Color.a };

								std::string player_name = XS("StoneOre");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), StoneColor, Color::Black(ColorSettings::StoneOre_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								if (m_settings::OreIcons)
								{
									
									UnityEngine::Texture2D* texture = nullptr;
									if (!texture)
									{
										texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(XS("stones.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
									}

									UnityEngine::GUI::SetColor(Color::White());
									UnityEngine::GUI::DrawTexture({ screen.x - 15, screen.y - m_settings::IconsScale - 2, m_settings::IconsScale, m_settings::IconsScale }, texture);
								}
							}
						}

						if (m_settings::MetalOre)
						{
							if (HASH("metal-ore") == Hash(name, false) || HASH("ore_metal") == Hash(name, false))
							{
								auto MetalColor = Color{ ColorSettings::MetalOre_Color.r, ColorSettings::MetalOre_Color.g, ColorSettings::MetalOre_Color.b, ColorSettings::MetalOre_Color.a };

								std::string player_name = XS("MetalOre");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), MetalColor, Color::Black(ColorSettings::MetalOre_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								if (m_settings::OreIcons)
								{
									UnityEngine::Texture2D* texture = nullptr;
									if (!texture)
									{
										texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(XS("metal.ore.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
									}

									UnityEngine::GUI::SetColor(Color::White());
									UnityEngine::GUI::DrawTexture({ screen.x - 15, screen.y - m_settings::IconsScale - 2, m_settings::IconsScale, m_settings::IconsScale }, texture);
								}
							}
						}

						if (m_settings::SulfurOre)
						{
							if (HASH("sulfur-ore") == Hash(name, false) || HASH("ore_sulfur") == Hash(name, false))
							{
								auto SulfurColor = Color{ ColorSettings::SulfurOre_Color.r, ColorSettings::SulfurOre_Color.g, ColorSettings::SulfurOre_Color.b, ColorSettings::SulfurOre_Color.a };

								std::string player_name = XS("SulfurOre");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), SulfurColor, Color::Black(ColorSettings::SulfurOre_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								if (m_settings::OreIcons)
								{
									UnityEngine::Texture2D* texture = nullptr;
									if (!texture)
									{
										texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(XS("sulfur.ore.png"), (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));
									}

									UnityEngine::GUI::SetColor(Color::White());
									UnityEngine::GUI::DrawTexture({ screen.x - 15, screen.y - m_settings::IconsScale - 2, m_settings::IconsScale, m_settings::IconsScale }, texture);
								}
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::DroppedItemContainer::StaticClass()) || BaseEntity->IsA(AssemblyCSharp::PlayerCorpse::StaticClass()))
				{
					if (distance <= m_settings::MaxPlayerDropsDistance)
					{
						if (m_settings::BackPack)
						{
							if (HASH("item_drop_backpack") == Hash(name, false))
							{
								auto BackpackColor = Color{ ColorSettings::Backpack_Color.r, ColorSettings::Backpack_Color.g, ColorSettings::Backpack_Color.b, ColorSettings::Backpack_Color.a };
								std::string player_name = XS("Backpack");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), BackpackColor, Color::Black(ColorSettings::Backpack_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

						if (m_settings::Corpse)
						{
							if (HASH("player_corpse") == Hash(name, false))
							{
								auto CorpseColor = Color{ ColorSettings::Corpse_Color.r, ColorSettings::Corpse_Color.g, ColorSettings::Corpse_Color.b, ColorSettings::Corpse_Color.a };
								std::string player_name = XS("Corpse");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), CorpseColor, Color::Black(ColorSettings::Corpse_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::StashContainer::StaticClass()))
				{
					if (distance <= m_settings::MaxDeployableDistance)
					{
						if (m_settings::Stash)
						{
							auto entity = static_cast<AssemblyCSharp::BaseEntity*>(BaseEntity);
							{
								auto flags = entity->flags();
								auto StashColor = Color{ ColorSettings::Stash_Color.r, ColorSettings::Stash_Color.g, ColorSettings::Stash_Color.b, ColorSettings::Stash_Color.a };

								if (flags & 2048)
								{
									std::string player_name = XS("Stash");
									char str[256];
									sprintf(str, XS("[%dm]"), (int)distance);
									player_name = player_name + " " + str;

									UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), StashColor, Color::Black(ColorSettings::Stash_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								}
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::AutoTurret::StaticClass()))
				{
					if (distance <= m_settings::MaxTurretDistance)
					{
						if (m_settings::AutoTurret)
						{
							if (HASH("autoturret_deployed") == Hash(name, false))
							{
								float yoffset = 0;
								auto turret_entity = static_cast<AssemblyCSharp::AutoTurret*>(BaseEntity);
								auto turret_baseentity = static_cast<AssemblyCSharp::BaseCombatEntity*>(BaseEntity);

								auto TurretColor = Color{ ColorSettings::Turret_Color.r, ColorSettings::Turret_Color.g, ColorSettings::Turret_Color.b, ColorSettings::Turret_Color.a };
								auto TAuthedPlayers_Color = Color{ ColorSettings::TAuthedPlayers_Color.r, ColorSettings::TAuthedPlayers_Color.g, ColorSettings::TAuthedPlayers_Color.b, ColorSettings::TAuthedPlayers_Color.a };
								auto TEquipedFlag_Color = Color{ ColorSettings::TEquipedFlag_Color.r, ColorSettings::TEquipedFlag_Color.g, ColorSettings::TEquipedFlag_Color.b, ColorSettings::TEquipedFlag_Color.a };
								auto ShowOnline_Color = Color{ ColorSettings::ShowOnline_Color.r, ColorSettings::ShowOnline_Color.g, ColorSettings::ShowOnline_Color.b, ColorSettings::ShowOnline_Color.a };
								auto TurningFlags_Color = Color{ ColorSettings::TurningFlags_Color.r, ColorSettings::TurningFlags_Color.g, ColorSettings::TurningFlags_Color.b, ColorSettings::TurningFlags_Color.a };
								auto Range_Color = Color{ ColorSettings::Range_Color.r, ColorSettings::Range_Color.g, ColorSettings::Range_Color.b, ColorSettings::Range_Color.a };

								auto flags = turret_entity->flags();
								/*if (flags & 2) {
									TurretColor = Color{ m_settings::TurretColor[0], m_settings::TurretColor[1], m_settings::TurretColor[2], m_settings::TurretColor[3] };
								}
								else
								{
									TurretColor = Color(0, 255, 0, 255.f);
								}*/
								
								
								std::string player_name = XS("Turret");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;

								UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), TurretColor, Color::Black(ColorSettings::Turret_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								yoffset += 12.f;

								auto aimDir = turret_entity->aimDir();
								auto muzzlePos = turret_entity->muzzlePos()->get_position();
								auto sightRange = turret_entity->sightRange();
								auto authorizedPlayers = turret_entity->authorizedPlayers();
								

								auto _health = turret_baseentity->_health();
								auto _maxhealth = turret_baseentity->_maxHealth();

								Vector2 W2SmuzzlePos;
								Vector2 W2SairDir;

								if (m_settings::TurretHealth) {
									float draw_health = _health;
									float yoffsethealth = 7.f;
									if (_health > _maxhealth) {
										draw_health = _maxhealth;
									}

									const auto bar_width = 30;
									const auto bar_health = (bar_width / _maxhealth) * draw_health;
									auto bar_color = Color::Green();

									if (_health > 50.f) {
										bar_color = Color::Green();
									}
									else if (_health > 20.f && _health < 40.f) {
										bar_color = Color::Orange();
									}
									else if (_health < 20.f) {
										bar_color = Color::Red();
									}


									UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffsethealth), Vector2(screen.x + (bar_width / 2), screen.y + yoffsethealth + 4.f), Color::Black());
									UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffsethealth), Vector2((screen.x - (bar_width / 2)) + bar_health, screen.y + yoffsethealth + 4.f), bar_color);
									UnityEngine::GL::Rectangle(Vector2(screen.x - (bar_width / 2), screen.y + yoffsethealth), Vector2(screen.x + (bar_width / 2), screen.y + yoffsethealth + 4.f), Color::Black());
									yoffset += 8.f;
								}

								if (m_settings::TurretEquippedFlags) {
									if (flags & 512) {
										UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), XS("Equipped"), TEquipedFlag_Color, Color::Black(ColorSettings::TEquipedFlag_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
										yoffset += 12.f;
									}
								}

								if (m_settings::TurretOnFlags)
								{
									if (flags & 2) {
										UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), XS("ON"), ShowOnline_Color, Color::Black(ColorSettings::ShowOnline_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
										yoffset += 12.f;
									}
									else
									{
										UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), XS("OFF"), ShowOnline_Color, Color::Black(ColorSettings::ShowOnline_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
										yoffset += 12.f;
									}
								}

								if (m_settings::TurretTurningFlag) {
									if (turret_entity->wasTurning()) {
										UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), XS("Turning"), TurningFlags_Color, Color::Black(ColorSettings::TurningFlags_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
										yoffset += 12.f;
									}
								}

								if (m_settings::TurretRange) {
									std::string player_name = XS("Range:");
									char str[256];
									sprintf(str, XS("[%dm]"), (int)distance);
									player_name = player_name + " " + str;

									UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), Range_Color, Color::Black(ColorSettings::Range_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
									yoffset += 12.f;
									UnityEngine::DDraw().Line(muzzlePos, Vector3(muzzlePos + (aimDir * sightRange)), Range_Color, 0.2f, true, false);
								}

								if (m_settings::TurretAuthorizedPlayers) {
									if (authorizedPlayers) {
										for (auto i = 0; i < authorizedPlayers->_size; i++) {
											const auto current = authorizedPlayers->_items->m_Items[i];
											if (current) {
												const auto str = current->username();
												if (str) {


													char retstr[256];
													sprintf(retstr, XS("%s [%dm]"), str->string_safe().c_str(), (int)distance);


													//if (UnityEngine::Input::GetKey(RustStructs::F))
													//{
													//	char stringstr[256];
													//	sprintf(stringstr, XS("client.reportplayer %llu"), current->userid());
													//	AssemblyCSharp::ConsoleSystem::Run(AssemblyCSharp::ConsoleSystem::client(), stringstr, nullptr);
													//}

													/*std::string player_name = str->string_safe();
													char str[128];
													sprintf(str, XS("[%dm]"), (int)distance);
													player_name = player_name + " " + str;*/
													UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), retstr, TAuthedPlayers_Color, Color::Black(ColorSettings::TAuthedPlayers_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
													yoffset += 12.f;
												}
											}
										}
									}
								}
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::BearTrap::StaticClass()))
				{
					if (distance <= m_settings::MaxTrapsDistance)
					{
						if (m_settings::BearTrap)
						{
							if (HASH("beartrap") == Hash(name, false))
							{
								auto BearTrap_Color = Color{ ColorSettings::BearTrap_Color.r, ColorSettings::BearTrap_Color.g, ColorSettings::BearTrap_Color.b, ColorSettings::BearTrap_Color.a };

								std::string player_name = XS("BearTrap");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), BearTrap_Color, Color::Black(ColorSettings::BearTrap_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::GunTrap::StaticClass()))
				{
					if (distance <= m_settings::MaxTrapsDistance)
					{
						if (m_settings::ShotgunTrap)
						{
							if (HASH("guntrap.deployed") == Hash(name, false))
							{
								auto ShotgunTrap_Color = Color{ ColorSettings::ShotgunTrap_Color.r, ColorSettings::ShotgunTrap_Color.g, ColorSettings::ShotgunTrap_Color.b, ColorSettings::ShotgunTrap_Color.a };

								std::string player_name = XS("Shotgun Trap");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), ShotgunTrap_Color, Color::Black(ColorSettings::ShotgunTrap_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::Barricade::StaticClass()))
				{
					if (distance <= m_settings::MaxTrapsDistance)
					{
						if (m_settings::SpikesTrap)
						{
							if (HASH("spikes.floor") == Hash(name, false))
							{
								auto SpikesTrap_Color = Color{ ColorSettings::SpikesTrap_Color.r, ColorSettings::SpikesTrap_Color.g, ColorSettings::SpikesTrap_Color.b, ColorSettings::SpikesTrap_Color.a };

								std::string player_name = XS("Spikes Trap");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), SpikesTrap_Color, Color::Black(ColorSettings::SpikesTrap_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::BaseAnimalNPC::StaticClass()))
				{
					if (distance <= m_settings::MaxAnimalDistance)
					{
						if (m_settings::Bear) {

							if (HASH("bear") == Hash(name, false))
							{
								auto Animal_Color = Color{ ColorSettings::Bear.r, ColorSettings::Bear.g, ColorSettings::Bear.b, ColorSettings::Bear.a };

								std::string player_name = XS("Bear");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), Animal_Color, Color::Black(ColorSettings::Bear.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}

							if (HASH("polarbear") == Hash(name, false))
							{
								auto Animal_Color = Color{ ColorSettings::Bear.r, ColorSettings::Bear.g, ColorSettings::Bear.b, ColorSettings::Bear.a };

								std::string player_name = XS("Polarbear");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), Animal_Color, Color::Black(ColorSettings::Bear.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

						if (m_settings::Boar) {
							if (HASH("boar") == Hash(name, false))
							{
								auto Animal_Color = Color{ ColorSettings::Boar.r, ColorSettings::Boar.g, ColorSettings::Boar.b, ColorSettings::Boar.a };

								std::string player_name = XS("Boar");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), Animal_Color, Color::Black(ColorSettings::Boar.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

						if (m_settings::Stag) {
							if (HASH("stag") == Hash(name, false))
							{
								auto Animal_Color = Color{ ColorSettings::Stag.r, ColorSettings::Stag.g, ColorSettings::Stag.b, ColorSettings::Stag.a };

								std::string player_name = XS("Stag");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), Animal_Color, Color::Black(ColorSettings::Stag.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

						if (m_settings::Wolf) {
							if (HASH("wolf") == Hash(name, false))
							{
								auto Animal_Color = Color{ ColorSettings::Wolf.r, ColorSettings::Wolf.g, ColorSettings::Wolf.b, ColorSettings::Wolf.a };

								std::string player_name = XS("Wolf");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), Animal_Color, Color::Black(ColorSettings::Wolf.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (m_settings::horseEsp)
				{
					if (distance <= m_settings::MaxAnimalDistance)
					{
						if (HASH("horse") == Hash(name, false) || HASH("testridablehorse") == Hash(name, false))
						{
							auto Horse_Color = Color{ ColorSettings::Horse.r, ColorSettings::Horse.g, ColorSettings::Horse.b, ColorSettings::Horse.a };

							std::string player_name = XS("Horse");
							char str[256];
							sprintf(str, XS("[%dm]"), (int)distance);
							player_name = player_name + " " + str;
							UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), Horse_Color, Color::Black(ColorSettings::Horse.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::FlameTurret::StaticClass()))
				{
					if (distance <= m_settings::MaxTrapsDistance)
					{
						if (m_settings::FlameTurret)
						{
							if (HASH("flameturret.deployed") == Hash(name, false))
							{
								auto FlameTurret_Color = Color{ ColorSettings::FlameTurret_Color.r, ColorSettings::FlameTurret_Color.g, ColorSettings::FlameTurret_Color.b, ColorSettings::FlameTurret_Color.a };

								std::string player_name = XS("FlameTurret");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), FlameTurret_Color, Color::Black(ColorSettings::FlameTurret_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::Landmine::StaticClass()))
				{
					if (distance <= m_settings::MaxTrapsDistance)
					{
						if (m_settings::LandMine)
						{
							if (HASH("landmine") == Hash(name, false))
							{
								auto LandMine_Color = Color{ ColorSettings::LandMine_Color.r, ColorSettings::LandMine_Color.g, ColorSettings::LandMine_Color.b, ColorSettings::LandMine_Color.a };

								std::string player_name = XS("LandMine");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), LandMine_Color, Color::Black(ColorSettings::LandMine_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::SamSite::StaticClass()))
				{
					if (distance <= m_settings::MaxTrapsDistance)
					{
						if (m_settings::SamSite)
						{
							if (HASH("sam_site_turret_deployed") == Hash(name, false))
							{
								auto TrapsColor = Color{ m_settings::TrapsColor[0], m_settings::TrapsColor[1], m_settings::TrapsColor[2], m_settings::TrapsColor[3] };
								std::string player_name = XS("Samsite");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), TrapsColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::HackableLockedCrate::StaticClass()))
				{
					if (distance <= m_settings::MaxCrateDistance)
					{
						if (m_settings::HackableCrate)
						{
							auto hackablecrate = reinterpret_cast<AssemblyCSharp::HackableLockedCrate*>(BaseEntity);
							auto hackablecrate_entity = static_cast<AssemblyCSharp::BaseCombatEntity*>(BaseEntity);

							if (HASH("codelockedhackablecrate") == Hash(name, false) || HASH("codelockedhackablecrate_oilrig") == Hash(name, false))
							{
								float yoffset = 0;
								auto CrateColor = Color{ ColorSettings::HackableCrate_Color.r, ColorSettings::HackableCrate_Color.g, ColorSettings::HackableCrate_Color.b, ColorSettings::HackableCrate_Color.a };
								std::string player_name = XS("HackableCrate");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								auto flags = hackablecrate_entity->flags();
								auto hackSeconds = hackablecrate->hackSeconds();
								UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), CrateColor, Color::Black(ColorSettings::HackableCrate_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								yoffset += 12.f;

								if (m_settings::HackableCrateFlags) {
									if (flags & 256) {
										UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), XS("Hacked"), Color::White(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
										yoffset += 12.f;
									}
									else if (flags & 128) {
										UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), XS("Hacking.."), Color::White(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
										yoffset += 12.f;
									}
								}

								if (m_settings::HackableCrateTimer) {
									auto TimeRemaining = 900 - (int)hackSeconds;
									std::string player_name = XS("Timer");
									char str[256];
									sprintf(str, XS("[%dm]"), (int)distance);
									player_name = player_name + " " + str;

									if (flags & 256) {}
									else {
										UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), Color::White(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
										yoffset += 12.f;
									}
								}
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::LootContainer::StaticClass()))
				{
					if (distance <= m_settings::MaxCrateDistance)
					{
						if (m_settings::BradleyCrate)
						{
							auto crate_entity = static_cast<AssemblyCSharp::BaseCombatEntity*>(BaseEntity);

							if (HASH("bradley_crate") == Hash(name, false))
							{
								float yoffset = 0;
								auto CrateColor = Color{ ColorSettings::BradleyCrate_Color.r, ColorSettings::BradleyCrate_Color.g, ColorSettings::BradleyCrate_Color.b, ColorSettings::BradleyCrate_Color.a };
								std::string player_name = XS("BradleyCrate");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								auto flags = crate_entity->flags();
								UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), CrateColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								yoffset += 12.f;
								if (flags & 4)
									UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), XS("OnFire"), CrateColor, Color::Black(ColorSettings::BradleyCrate_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

							}
						}

						if (m_settings::HeliCrate)
						{
							auto crate_entity = static_cast<AssemblyCSharp::BaseCombatEntity*>(BaseEntity);

							if (HASH("heli_crate") == Hash(name, false))
							{
								float yoffset = 0;
								auto CrateColor = Color{ ColorSettings::HeliCrate_Color.r, ColorSettings::HeliCrate_Color.g, ColorSettings::HeliCrate_Color.b, ColorSettings::HeliCrate_Color.a };
								std::string player_name = XS("HeliCrate");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								auto flags = crate_entity->flags();
								UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), CrateColor, Color::Black(ColorSettings::HeliCrate_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								yoffset += 12.f;
								if (flags & 4)
									UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), XS("OnFire"), Color::Red(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);

							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::Tugboat::StaticClass()))
				{
					if (m_settings::TugBoat)
					{
						if (distance <= m_settings::MaxVehicleDistance)
						{
							auto thugboat = reinterpret_cast<AssemblyCSharp::Tugboat*>(BaseEntity);

							if (thugboat)
							{
								auto TugBoat_Color = Color{ ColorSettings::TugBoat_Color.r, ColorSettings::TugBoat_Color.g, ColorSettings::TugBoat_Color.b, ColorSettings::TugBoat_Color.a };

								float yoffset = 0;
								std::string player_name = XS("TugBoat");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), TugBoat_Color, Color::Black(ColorSettings::TugBoat_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								yoffset += 12.f;

								float draw_health = thugboat->_health();
								float yoffsethealth = 7.f;
								if (thugboat->_health() > thugboat->_maxHealth()) {
									draw_health = thugboat->_maxHealth();
								}

								const auto bar_width = 30;
								const auto bar_health = (bar_width / thugboat->_maxHealth()) * draw_health;
								auto bar_color = Color::Green();

								if (thugboat->_health() > 50.f) {
									bar_color = Color::Green();
								}
								else if (thugboat->_health() > 20.f && thugboat->_health() < 40.f) {
									bar_color = Color::Orange();
								}
								else if (thugboat->_health() < 20.f) {
									bar_color = Color::Red();
								}


								UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffsethealth), Vector2(screen.x + (bar_width / 2), screen.y + yoffsethealth + 4.f), Color::Black());
								UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffsethealth), Vector2((screen.x - (bar_width / 2)) + bar_health, screen.y + yoffsethealth + 4.f), bar_color);
								UnityEngine::GL::Rectangle(Vector2(screen.x - (bar_width / 2), screen.y + yoffsethealth), Vector2(screen.x + (bar_width / 2), screen.y + yoffsethealth + 4.f), Color::Black());
								yoffset += 8.f;
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::BaseVehicle::StaticClass()))
				{
					if (distance <= m_settings::MaxVehicleDistance)
					{
						if (m_settings::Minicopter)
						{
							if (HASH("minicopter.entity") == Hash(name, false))
							{
								auto Minicopter_Color = Color{ ColorSettings::Minicopter_Color.r, ColorSettings::Minicopter_Color.g, ColorSettings::Minicopter_Color.b, ColorSettings::Minicopter_Color.a };

								std::string player_name = XS("Minicopter");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), Minicopter_Color, Color::Black(ColorSettings::Minicopter_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

						if (m_settings::ScrapHeli)
						{
							if (HASH("scraptransporthelicopter") == Hash(name, false))
							{
								auto ScrapHeli_Color = Color{ ColorSettings::ScrapHeli_Color.r, ColorSettings::ScrapHeli_Color.g, ColorSettings::ScrapHeli_Color.b, ColorSettings::ScrapHeli_Color.a };

								std::string player_name = XS("ScrapHeli");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), ScrapHeli_Color, Color::Black(ColorSettings::ScrapHeli_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

						//if (m_settings::AttackHeli)
						//{
						//	if (HASH("attackhelicopter") == Hash(name, false))
						//	{
						//		auto VehicleColor = Color{ m_settings::VehicleColor[0], m_settings::VehicleColor[1], m_settings::VehicleColor[2], m_settings::VehicleColor[3] };
						//		std::string player_name = XS("AttackHeli");
						//		char str[256];
						//		sprintf(str, XS("[%dm]"), (int)distance);
						//		player_name = player_name + " " + str;
						//		UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), VehicleColor.GetUnityColor(), Color::Black(), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
						//	}
						//}

						if (m_settings::Rowboat)
						{
							if (HASH("rowboat") == Hash(name, false))
							{
								auto RowBoat_Color = Color{ ColorSettings::RowBoat_Color.r, ColorSettings::RowBoat_Color.g, ColorSettings::RowBoat_Color.b, ColorSettings::RowBoat_Color.a };

								std::string player_name = XS("RowBoat");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), RowBoat_Color, Color::Black(ColorSettings::RowBoat_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

						if (m_settings::Rhib)
						{
							if (HASH("RHIB") == Hash(name, false))
							{
								auto RHIB_Color = Color{ ColorSettings::RHIB_Color.r, ColorSettings::RHIB_Color.g, ColorSettings::RHIB_Color.b, ColorSettings::RHIB_Color.a };

								std::string player_name = XS("RHIB");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), RHIB_Color, Color::Black(ColorSettings::RHIB_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}

				if (BaseEntity->IsA(AssemblyCSharp::Workbench::StaticClass()))
				{
					if (distance <= m_settings::MaxDeployableDistance)
					{
						if (m_settings::T1Workbench)
						{
							if (HASH("workbench1.deployed") == Hash(name, false))
							{
								auto DeployableColor = Color{ ColorSettings::Workbench1_Color.r, ColorSettings::Workbench1_Color.g, ColorSettings::Workbench1_Color.b, ColorSettings::Workbench1_Color.a };
								std::string player_name = XS("T1 Workbench");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), DeployableColor, Color::Black(ColorSettings::Workbench1_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

						if (m_settings::T2Workbench)
						{
							if (HASH("workbench2.deployed") == Hash(name, false))
							{
								auto DeployableColor = Color{ ColorSettings::Workbench2_Color.r, ColorSettings::Workbench2_Color.g, ColorSettings::Workbench2_Color.b, ColorSettings::Workbench2_Color.a };
								std::string player_name = XS("T2 Workbench");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), DeployableColor, Color::Black(ColorSettings::Workbench2_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}

						if (m_settings::T3Workbench)
						{
							if (HASH("workbench3.deployed") == Hash(name, false))
							{
								auto DeployableColor = Color{ ColorSettings::Workbench3_Color.r, ColorSettings::Workbench3_Color.g, ColorSettings::Workbench3_Color.b, ColorSettings::Workbench3_Color.a };
								std::string player_name = XS("T3 Workbench");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), DeployableColor, Color::Black(ColorSettings::Workbench3_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
							}
						}
					}
				}
				if (m_settings::BradleyAPC)
				{
					if (BaseEntity->IsA(AssemblyCSharp::BradleyAPC::StaticClass()))
					{
						if (distance <= m_settings::MaxAPCDistance)
						{
							auto base_heli = reinterpret_cast<AssemblyCSharp::BradleyAPC*>(BaseEntity);
							if (base_heli)
							{
								float yoffset = 0;
								auto Bradley_Color = Color{ ColorSettings::Bradley_Color.r, ColorSettings::Bradley_Color.g, ColorSettings::Bradley_Color.b, ColorSettings::Bradley_Color.a };

								std::string player_name = XS("Bradley");
								char str[256];
								sprintf(str, XS("[%dm]"), (int)distance);
								player_name = player_name + " " + str;
								UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), Bradley_Color, Color::Black(ColorSettings::Bradley_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
								yoffset += 12.f;

								//if (m_settings::BradleyhealthBar)
								//{
								//	float bar_health = 0;
								//	auto health = base_heli->_health();
								//	//auto max_health = base_player->_maxHealth();
								//	float max_health = 100.f;
								//	float draw_health = health;

								//	if (health > max_health)
								//	{
								//		draw_health = max_health;
								//	}

								//	const auto bar_width = 30;
								//	bar_health = (bar_width / max_health) * draw_health;

								//	auto bar_color = Color::Green();
								//	if (health > 50.f)
								//	{
								//		bar_color = Color::Green();
								//	}
								//	else if (health > 20.f && health < 40.f)
								//	{
								//		bar_color = Color::Orange();
								//	}
								//	else if (health < 20.f)
								//	{
								//		bar_color = Color::Red();
								//	}

								//	//UnityEngine::GL::GlFillRectangle(Vector2{ footPos.x - (bar_width / 2), bo.bottom + yoffset }, Vector2{ bar_width, 4.f }, Color::Black());
								//	//UnityEngine::GL::GlFillRectangle(Vector2{ footPos.x - (bar_width / 2), bo.bottom + yoffset }, Vector2{ bar_health, 4.f }, bar_color);
								//	//UnityEngine::GL::Rectangle(Vector2{ footPos.x - (bar_width / 2), bo.bottom + yoffset }, Vector2{ bar_width, 4.f }, Color::Black());

								//	UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffset), Vector2(screen.x + (bar_width / 2), screen.y + yoffset + 3.f), Color::Black());
								//	UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffset), Vector2((screen.x - (bar_width / 2)) + bar_health, screen.y + yoffset + 3.f), bar_color);
								//	UnityEngine::GL::Rectangle(Vector2(screen.x - (bar_width / 2), screen.y + yoffset), Vector2(screen.x + (bar_width / 2), screen.y + yoffset + 4.f), Color::Black());
								//	yoffset += 13;
								//}
							}

						}

					}
				}
				if (m_settings::PatrolHelicopter)
				{
					if (BaseEntity->IsA(AssemblyCSharp::PatrolHelicopter::StaticClass()))
					{
						if (distance <= m_settings::MaxAPCDistance)
						{
							//if (m_settings::PatrolHelicopter)
							{
								auto base_heli = reinterpret_cast<AssemblyCSharp::PatrolHelicopter*>(BaseEntity);
								if (base_heli)
								{
									float yoffset = 0;

									auto PatrolHeli_Color = Color{ ColorSettings::PatrolHeli_Color.r, ColorSettings::PatrolHeli_Color.g, ColorSettings::PatrolHeli_Color.b, ColorSettings::PatrolHeli_Color.a };

									std::string player_name = XS("Patrol Helicopter");
									char str[256];
									sprintf(str, XS("[%dm]"), (int)distance);
									player_name = player_name + " " + str;
									UnityEngine::GL().TextCenter(Vector2(screen.x, screen.y + yoffset), player_name.c_str(), PatrolHeli_Color, Color::Black(ColorSettings::PatrolHeli_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
									yoffset += 12.f;

									//if (m_settings::healthBar)
									//{
									//	float bar_health = 0;
									//	auto health = base_heli->_health();
									//	//auto max_health = base_player->_maxHealth();
									//	float max_health = 100.f;
									//	float draw_health = health;

									//	if (health > max_health)
									//	{
									//		draw_health = max_health;
									//	}

									//	const auto bar_width = 30;
									//	bar_health = (bar_width / max_health) * draw_health;

									//	auto bar_color = Color::Green();
									//	if (health > 50.f)
									//	{
									//		bar_color = Color::Green();
									//	}
									//	else if (health > 20.f && health < 40.f)
									//	{
									//		bar_color = Color::Orange();
									//	}
									//	else if (health < 20.f)
									//	{
									//		bar_color = Color::Red();
									//	}

									//	//UnityEngine::GL::GlFillRectangle(Vector2{ footPos.x - (bar_width / 2), bo.bottom + yoffset }, Vector2{ bar_width, 4.f }, Color::Black());
									//	//UnityEngine::GL::GlFillRectangle(Vector2{ footPos.x - (bar_width / 2), bo.bottom + yoffset }, Vector2{ bar_health, 4.f }, bar_color);
									//	//UnityEngine::GL::Rectangle(Vector2{ footPos.x - (bar_width / 2), bo.bottom + yoffset }, Vector2{ bar_width, 4.f }, Color::Black());

									//	UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffset), Vector2(screen.x + (bar_width / 2), screen.y + yoffset + 3.f), Color::Black());
									//	UnityEngine::GL::RectangleFilled(Vector2(screen.x - (bar_width / 2), screen.y + yoffset), Vector2((screen.x - (bar_width / 2)) + bar_health, screen.y + yoffset + 3.f), bar_color);
									//	UnityEngine::GL::Rectangle(Vector2(screen.x - (bar_width / 2), screen.y + yoffset), Vector2(screen.x + (bar_width / 2), screen.y + yoffset + 4.f), Color::Black());
									//	yoffset += 13;
									//}
								}
							}
						}
					}
				}
				if (m_settings::Recycler)
				{
					if (distance <= m_settings::MaxDeployableDistance)
					{
						if (HASH("recycler_static") == Hash(name, false))
						{
							auto DeployableColor = Color{ ColorSettings::Recycler_Color.r, ColorSettings::Recycler_Color.g, ColorSettings::Recycler_Color.b, ColorSettings::Recycler_Color.a };
							std::string player_name = XS("Recycler");
							char str[256];
							sprintf(str, XS("[%dm]"), (int)distance);
							player_name = player_name + " " + str;
							UnityEngine::GL().TextCenter(Vector2(screen), player_name.c_str(), DeployableColor, Color::Black(ColorSettings::Recycler_Color.a), m_settings::WorldFontSize, m_settings::WorldOutlinedText, m_settings::WorldShadedText);
						}
					}
				}
			}
		}
	}
}


void Visuals::CacheEntities()
{
	if (!InGame)
		return;

	if (const auto ClientEntites = AssemblyCSharp::BaseNetworkable::clientEntities())
	{
		if (const auto entityList = ClientEntites->entityList())
		{
			if (const auto EntityListVals = entityList->vals)
			{
				if (const auto EntityListBuffer = EntityListVals->buffer)
				{
					for (std::int32_t index = 0; index < EntityListVals->count; index++)
					{
						auto BaseEntity = EntityListBuffer->m_Items[index];

						if (IsAddressValid(BaseEntity))
						{

							if (!BaseEntity->net())
								continue;

							if (BaseEntity->IsPlayer())
								continue;

							if (BaseEntity->IsEntity())
								continue;

							auto distance = Features().LocalPlayer->get_transform()->get_position().Distance(BaseEntity->get_transform()->get_position());

							if (distance >= 300)
								continue;

							const auto EntityID = BaseEntity->prefabID();
							const auto StashID = 2568831788;
							const auto boarID = 502341109;
							const auto stagID = 1378621008;
							const auto wolfID = 2144238755;
							const auto bearID = 1799741974;
							const auto HempCollectable = 3006540952;
							const auto CornID = 3019211920;
							const auto PumpkinID = 2251957318;
							const auto PotatoID = 726972295;
							const auto mushRoomID1 = 2697239269;
							const auto mushRoomID2 = 178882626;
							const auto dieselCollectable = 1388355532;

							const auto MetalCollectable = 4060169083;
							const auto MetalOre = 3774647716;
							const auto MetalOre2 = 4225479497;
							const auto MetalOre3 = 3345228353;
							const auto OreMetal = 3327726152;

							const auto StoneCollectable = 2422310333;
							const auto StoneOre = 4124824587;
							const auto StoneOre2 = 266547145;
							const auto StoneOre3 = 723721358;
							const auto OreStone = 960501790;

							const auto SulfurCollectable = 2972237931;
							const auto SulfurOre = 3058967796;
							const auto SulfurOre2 = 1227527004;
							const auto SulfurOre3 = 2204178116;
							const auto OreSulfur = 152562243;

							const auto player_corpse = 2604534927;
							const auto player_backpack = 1519640547;

							const auto autoturret_deployed = 3312510084;

							const auto bradley_crate = 1737870479;
							const auto heli_crate = 1314849795;

							const auto patrol_heli = 3029415845;
							const auto bradley_apc = 1456850188;

							const auto cupboard_deployed = 2476970476;
							const auto crate_basic = 1603759333;
							const auto crate_normal_2 = 1546200557;
							const auto crate_normal_2_food = 2066926276;
							const auto crate_normal_2_medical = 1791916628;
							const auto crate_normal = 2857304752;
							const auto crate_elite = 3286607235;
							const auto supply_drop = 3632568684;
							const auto loot_barrel = 966676416;
							const auto oil_barrel = 3438187947;
							const auto horse = 3880446623;
							const auto horse2 = 2421623959;
							const auto bear = 1799741974;
							const auto boar = 502341109;
							const auto stag = 1378621008;
							const auto wolf = 2144238755;
							const auto thugboat = 7995600;

							const auto BearTrap = 922529517;
							const auto GunTrap = 1348746224;
							const auto FlameTurret = 4075317686;
							const auto FloorSpikes = 976279966;
							const auto LandMine = 1463807579;
							const auto SamSite = 2059775839;

							const auto Minicopter = 2278499844;
							const auto ScrapHeli = 3484163637;
							const auto RHIB = 2226588638;
							const auto Rowboat = 1283317166;

							const auto t1workbench = 2561955800;
							const auto t2workbench = 601265145;
							const auto t3workbench = 2764275075;

							const auto recycler = 1729604075;

							if (EntityID == horse && m_settings::horseEsp && distance <= m_settings::MaxAnimalDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							if (EntityID == recycler && m_settings::Recycler && distance <= m_settings::MaxDeployableDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == horse2 && m_settings::horseEsp && distance <= m_settings::MaxAnimalDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == bear && m_settings::Bear && distance <= m_settings::MaxAnimalDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (BaseEntity->IsA(AssemblyCSharp::Polarbear::StaticClass()) && m_settings::Bear && distance <= m_settings::MaxAnimalDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == boar && m_settings::Boar && distance <= m_settings::MaxAnimalDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == stag && m_settings::Stag && distance <= m_settings::MaxAnimalDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == wolf && m_settings::Wolf && distance <= m_settings::MaxAnimalDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (BaseEntity->IsA(AssemblyCSharp::Tugboat::StaticClass()) && m_settings::TugBoat && distance <= m_settings::MaxVehicleDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == t1workbench && m_settings::T1Workbench && distance <= m_settings::MaxDeployableDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == t2workbench && m_settings::T2Workbench && distance <= m_settings::MaxDeployableDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == t3workbench && m_settings::T3Workbench && distance <= m_settings::MaxDeployableDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == Minicopter && m_settings::Minicopter && distance <= m_settings::MaxVehicleDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == ScrapHeli && m_settings::ScrapHeli && distance <= m_settings::MaxVehicleDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == RHIB && m_settings::Rhib && distance <= m_settings::MaxVehicleDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == Rowboat && m_settings::Rowboat && distance <= m_settings::MaxVehicleDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							//else if (BaseEntity->IsA(AssemblyCSharp::AttackHeli::StaticClass()) && m_settings::AttackHeli)
							//{
							//	PrefabListTemp.push_back(PrefabList(BaseEntity));
							//}
							else if (EntityID == BearTrap && m_settings::BearTrap && distance <= m_settings::MaxTrapsDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == GunTrap && m_settings::ShotgunTrap && distance <= m_settings::MaxTrapsDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == FlameTurret && m_settings::FlameTurret && distance <= m_settings::MaxTrapsDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == FloorSpikes && m_settings::SpikesTrap && distance <= m_settings::MaxTrapsDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == LandMine && m_settings::LandMine && distance <= m_settings::MaxTrapsDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == SamSite && m_settings::SamSite && distance <= m_settings::MaxTrapsDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == crate_basic && m_settings::BasicCrate && distance <= m_settings::MaxCrateDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == crate_normal_2 || EntityID == crate_normal_2_medical || EntityID == crate_normal_2_food && m_settings::NormalCrate && distance <= m_settings::MaxCrateDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == crate_normal && m_settings::MilitaryCrate && distance <= m_settings::MaxCrateDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == crate_elite && m_settings::EliteCrate && distance <= m_settings::MaxCrateDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == supply_drop && m_settings::SupplyDrop && distance <= m_settings::MaxSupplyDropDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == crate_normal && m_settings::NormalCrate && distance <= m_settings::MaxCrateDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
	/*						else if (EntityID == loot_barrel && m_settings::LootBarrel)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}*/
							else if (BaseEntity->IsA(AssemblyCSharp::PatrolHelicopter::StaticClass()) && m_settings::PatrolHelicopter && distance <= m_settings::MaxAPCDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == heli_crate && m_settings::HeliCrate && distance <= m_settings::MaxCrateDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == bradley_apc && m_settings::BradleyAPC && distance <= m_settings::MaxAPCDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == bradley_crate && m_settings::BradleyCrate && distance <= m_settings::MaxCrateDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (BaseEntity->IsA(AssemblyCSharp::HackableLockedCrate::StaticClass()) && m_settings::HackableCrate && distance <= m_settings::MaxCrateDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == autoturret_deployed && m_settings::AutoTurret && distance <= m_settings::MaxTrapsDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == player_corpse && m_settings::Corpse && distance <= m_settings::MaxPlayerDropsDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == player_backpack && m_settings::BackPack && distance <= m_settings::MaxPlayerDropsDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == StoneOre || EntityID == StoneOre2 || EntityID == StoneOre3 || EntityID == OreStone && m_settings::StoneOre && distance <= m_settings::MaxOreDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == MetalOre || EntityID == MetalOre2 || EntityID == MetalOre3 || EntityID == OreMetal && m_settings::MetalOre && distance <= m_settings::MaxOreDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == SulfurOre || EntityID == SulfurOre2 || EntityID == SulfurOre3 || EntityID == OreSulfur && m_settings::SulfurOre && distance <= m_settings::MaxOreDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == StoneCollectable && m_settings::StoneCollectable && distance <= m_settings::MaxCollectableDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == MetalCollectable && m_settings::MetalCollectable && distance <= m_settings::MaxCollectableDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == SulfurCollectable && m_settings::SulfurCollectable && distance <= m_settings::MaxCollectableDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == dieselCollectable && m_settings::DieselBarrel && distance <= m_settings::MaxCrateDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == HempCollectable && m_settings::Hemp && distance <= m_settings::MaxCollectableDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == StashID && m_settings::Stash && distance <= m_settings::MaxDeployableDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == mushRoomID1 || EntityID == mushRoomID2 && m_settings::Mushroom && distance <= m_settings::MaxFoodDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == PumpkinID && m_settings::Pumpkin && distance <= m_settings::MaxFoodDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}

							else if (EntityID == PotatoID && m_settings::Potato && distance <= m_settings::MaxFoodDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							
							else if (EntityID == CornID && m_settings::Corn && distance <= m_settings::MaxFoodDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (BaseEntity->IsA(AssemblyCSharp::WorldItem::StaticClass()) && m_settings::DroppedItems && distance <= m_settings::MaxDroppedDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (EntityID == cupboard_deployed && m_settings::cupboard && distance <= m_settings::MaxTCDistance)
							{
								PrefabListTemp.push_back(PrefabList(BaseEntity));
							}
							else if (BaseEntity->IsA(AssemblyCSharp::Door::StaticClass()) && m_settings::DoorSpammer)
							{
								auto distance = Features().LocalPlayer->get_transform()->get_position().Distance(BaseEntity->get_transform()->get_position());

								auto ent = reinterpret_cast<AssemblyCSharp::Door*>(BaseEntity);

								if (IsAddressValid(ent) && distance <= 3.f)
								{
									if (RPC_Counter.Calculate() <= 5)
									{
										ent->KnockDoor(Features().LocalPlayer);
										RPC_Counter.Increment();
									}
								}
							}
							else if (BaseEntity->IsA(AssemblyCSharp::BuildingBlock::StaticClass()) && m_settings::AutoUpgrade)
							{
								auto block = reinterpret_cast<AssemblyCSharp::BuildingBlock*>(BaseEntity);

								if (block)
								{
									auto entity_pos = block->get_positionz();

									if (RPC_Counter.Calculate() >= 5)
									{
										continue;
									}


									Vector3 local = Features().LocalPlayer->ClosestPoint(entity_pos);
									if (local.get_3d_dist(entity_pos) <= 5.5f)
									{
										float LastGrade = 0.f;
										auto BuildingGrade = m_settings::BuildingGrade + 1;
										if (Features().LocalPlayer->lastSentTickTime() > LastGrade + 0.35f
											&& block->CanAffordUpgrade((RustStructs::BuildingGrade)BuildingGrade, 0, Features().LocalPlayer)
											&& block->CanChangeToGrade((RustStructs::BuildingGrade)BuildingGrade, 0, Features().LocalPlayer)
											&& !block->IsUpgradeBlocked()) {
											block->UpgradeToGrade((RustStructs::BuildingGrade)BuildingGrade, 0, Features().LocalPlayer);
											RPC_Counter.Increment();
											LastGrade = Features().LocalPlayer->lastSentTickTime();
										}
									}

								}
							}
							else
							{
								continue;
							}
						}
					}

					PrefabVectorList = PrefabListTemp;
					PrefabListTemp.clear();
				}

			}

		}

	}

}


AssemblyCSharp::BasePlayer::Target Visuals::GetAimbotTargetSafe(Vector3 Source, float MaxDist)
{
	if (!InGame)
	{
		free(VisiblePlayerList);	
		auto Vals = VisiblePlayerList->vals;
		auto buffer = Vals->buffer;
		free(Vals);
		free(buffer);

		return {};
	}
		

	if (!VisiblePlayerList)
		VisiblePlayerList = AssemblyCSharp::BasePlayer::visiblePlayerList();

	auto Vals = VisiblePlayerList->vals;
	auto size = Vals->count;
	auto buffer = Vals->buffer;
	AssemblyCSharp::BasePlayer::Target best_target = AssemblyCSharp::BasePlayer::Target();

	for (std::int32_t index = 0; index < size; index++)
	{
		auto BasePlayer = buffer->m_Items[index];
		if (!IsAddressValid(BasePlayer))
			continue;

		if(!IsAddressValid(BasePlayer->net()))
			continue;

		if (!IsAddressValid(BasePlayer->playerModel()) || !IsAddressValid(BasePlayer->model()))
			continue;

		if (BasePlayer->IsDead() || BasePlayer->IsLocalPlayer() ||
			BasePlayer->playerFlags() & RustStructs::PlayerFlags::Sleeping || BasePlayer->wasDead() ||
			BasePlayer->_health() <= 0.f)
			continue;

		auto isWounded = BasePlayer->playerFlags() & RustStructs::PlayerFlags::Wounded;
		if (isWounded && !m_settings::TargetWounded)
			continue;

		bool isNpc = false;
		if (BasePlayer->playerModel()->get_IsNpc()) {
			if (!m_settings::AimbotNPC)
				continue;
			isNpc = true;
		}

		AssemblyCSharp::BasePlayer::Target target;
		target.m_player = BasePlayer;

		if (target.m_player != nullptr)
		{
			if (target.m_player != BasePlayer)
			{
				target.m_player = BasePlayer;
			}
		}


		auto velocity = BasePlayer->playerModel()->newVelocity();
		target.m_velocity = velocity;

		Vector3 pos = Vector3(0.f, 0.f, 0.f);
		int selectedAimbone = m_settings::SelectedAimbone;
		int bone = 47;
		switch (selectedAimbone) {
		case 0: // Head
			pos = BasePlayer->get_bone_transform(RustStructs::bones::head)->get_position();
			bone = RustStructs::bones::head;
			break;
		case 1: // neck
			pos = BasePlayer->get_bone_transform(RustStructs::bones::neck)->get_position();
			bone = RustStructs::bones::neck;
			break;
		case 2: // spine1
			pos = BasePlayer->get_bone_transform(RustStructs::bones::spine1)->get_position();
			bone = RustStructs::bones::spine1;
			break;
		case 3: // Random bone selection
			switch (my_rand() % 9) {
			case 0: // Head
				pos = BasePlayer->get_bone_transform(RustStructs::bones::head)->get_position();
				bone = RustStructs::bones::head;
				break;
			case 1: // pelvis
				pos = BasePlayer->get_bone_transform(RustStructs::bones::pelvis)->get_position();
				bone = RustStructs::bones::pelvis;
				break;
			case 2: // r_hip
				pos = BasePlayer->get_bone_transform(RustStructs::bones::r_hip)->get_position();
				bone = RustStructs::bones::r_hip;
				break;
			case 3: // r_foot
				pos = BasePlayer->get_bone_transform(RustStructs::bones::r_foot)->get_position();
				bone = RustStructs::bones::r_foot;
				break;
			case 4: // spine1
				pos = BasePlayer->get_bone_transform(RustStructs::bones::spine1)->get_position();
				bone = RustStructs::bones::spine1;
				break;
			case 5: // l_hand
				pos = BasePlayer->get_bone_transform(RustStructs::bones::l_hand)->get_position();
				bone = RustStructs::bones::l_hand;
				break;
			case 6: // r_upperarm
				pos = BasePlayer->get_bone_transform(RustStructs::bones::r_upperarm)->get_position();
				bone = RustStructs::bones::r_upperarm;
				break;
			case 7: // l_knee
				pos = BasePlayer->get_bone_transform(RustStructs::bones::l_knee)->get_position();
				bone = RustStructs::bones::l_knee;
				break;
			case 8: // spine4
				pos = BasePlayer->get_bone_transform(RustStructs::bones::spine4)->get_position();
				bone = RustStructs::bones::spine4;
				break;
			}
			break;
		case 4:
			bone = AssemblyCSharp::BasePlayer::ClosesestToCrosshair(ToAddress(BasePlayer));
			pos = BasePlayer->get_bone_transform(bone)->get_position();
			break;
		}

		target.m_position = pos;
		target.m_bone = bone;
		target.m_npc = isNpc;
		target.m_heli = false;

		auto distance = Source.get_3d_dist(pos);
		target.m_distance = distance;
		if (distance > MaxDist)
			continue;

		auto fov = AssemblyCSharp::get_fov(pos);
		target.m_fov = fov;

		if (!IsAddressValid(target.m_player))
			continue;

		if (target < best_target)
			best_target = target;
	}


	return best_target;
}