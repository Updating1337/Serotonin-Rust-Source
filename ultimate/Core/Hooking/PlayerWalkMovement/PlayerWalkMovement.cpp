#include "../Hooks.hpp"
#include "../../Features/Features/Features.hpp"

struct NodeTarget {
	Vector3 pos;
	int steps;
	std::vector<Vector3> path;
	AssemblyCSharp::BasePlayer* ent;
};

float time_at_node = 0.f;
float last_player_follow_update = 0.f;
int psteps = 0;
bool needs_to_jump = false;
Vector3 last_pos_until_jump = { 0, 0, 0 };
float time_within_1m = 0.f;
Vector3 last_pos = Vector3(0, 0, 0);

#include <array>
std::array<Vector3, 73> sphere1m = { Vector3(0.000000, -1.000000, 0.000000), Vector3(0.382683, -0.923880, 0.000000), Vector3(0.270598, -0.923880, 0.270598), Vector3(-0.000000, -0.923880, 0.382683), Vector3(-0.270598, -0.923880, 0.270598), Vector3(-0.382683, -0.923880, -0.000000), Vector3(-0.270598, -0.923880, -0.270598), Vector3(0.000000, -0.923880, -0.382683), Vector3(0.270598, -0.923880, -0.270598), Vector3(0.382683, -0.923880, 0.000000), Vector3(0.707107, -0.707107, 0.000000), Vector3(0.500000, -0.707107, 0.500000), Vector3(-0.000000, -0.707107, 0.707107), Vector3(-0.500000, -0.707107, 0.500000), Vector3(-0.707107, -0.707107, -0.000000), Vector3(-0.500000, -0.707107, -0.500000), Vector3(0.000000, -0.707107, -0.707107), Vector3(0.500000, -0.707107, -0.500000), Vector3(0.707107, -0.707107, 0.000000), Vector3(0.923880, -0.382683, 0.000000), Vector3(0.653281, -0.382683, 0.653281), Vector3(-0.000000, -0.382683, 0.923880), Vector3(-0.653281, -0.382683, 0.653281), Vector3(-0.923880, -0.382683, -0.000000), Vector3(-0.653281, -0.382683, -0.653282), Vector3(0.000000, -0.382683, -0.923880), Vector3(0.653282, -0.382683, -0.653281), Vector3(0.923880, -0.382683, 0.000000), Vector3(1.000000, 0.000000, 0.000000), Vector3(0.707107, 0.000000, 0.707107), Vector3(-0.000000, 0.000000, 1.000000), Vector3(-0.707107, 0.000000, 0.707107), Vector3(-1.000000, 0.000000, -0.000000), Vector3(-0.707107, 0.000000, -0.707107), Vector3(0.000000, 0.000000, -1.000000), Vector3(0.707107, 0.000000, -0.707107), Vector3(1.000000, 0.000000, 0.000000), Vector3(0.923880, 0.382683, 0.000000), Vector3(0.653281, 0.382683, 0.653281), Vector3(-0.000000, 0.382683, 0.923880), Vector3(-0.653281, 0.382683, 0.653281), Vector3(-0.923880, 0.382683, -0.000000), Vector3(-0.653281, 0.382683, -0.653282), Vector3(0.000000, 0.382683, -0.923880), Vector3(0.653282, 0.382683, -0.653281), Vector3(0.923880, 0.382683, 0.000000), Vector3(0.707107, 0.707107, 0.000000), Vector3(0.500000, 0.707107, 0.500000), Vector3(-0.000000, 0.707107, 0.707107), Vector3(-0.500000, 0.707107, 0.500000), Vector3(-0.707107, 0.707107, -0.000000), Vector3(-0.500000, 0.707107, -0.500000), Vector3(0.000000, 0.707107, -0.707107), Vector3(0.500000, 0.707107, -0.500000), Vector3(0.707107, 0.707107, 0.000000), Vector3(0.382683, 0.923880, 0.000000), Vector3(0.270598, 0.923880, 0.270598), Vector3(-0.000000, 0.923880, 0.382683), Vector3(-0.270598, 0.923880, 0.270598), Vector3(-0.382683, 0.923880, -0.000000), Vector3(-0.270598, 0.923880, -0.270598), Vector3(0.000000, 0.923880, -0.382683), Vector3(0.270598, 0.923880, -0.270598), Vector3(0.382683, 0.923880, 0.000000), Vector3(-0.000000, 1.000000, -0.000000), Vector3(-0.000000, 1.000000, -0.000000), Vector3(0.000000, 1.000000, -0.000000), Vector3(0.000000, 1.000000, -0.000000), Vector3(0.000000, 1.000000, 0.000000), Vector3(0.000000, 1.000000, 0.000000), Vector3(-0.000000, 1.000000, 0.000000), Vector3(-0.000000, 1.000000, 0.000000), Vector3(-0.000000, 1.000000, -0.000000) };

float dist_from_ground(Vector3 v)
{
	Vector3 p = v;
	int t = 0;
	while (t++ < 100)
	{
		if (!AssemblyCSharp::IsVisible(v, p))
			return v.distanceeee(p);
		p.y -= 0.1;
	}
}

Vector3 lowest_pos(Vector3 in)
{
	Vector3 current = in;
	for (size_t i = 0; i < 100; i++)
	{
		if (AssemblyCSharp::IsVisible(in, current))
		{
			current = Vector3(current.x, current.y -= 1.f, current.z);
			continue;
		}
		else break;
	}
	return Vector3(current.x, current.y += 1.6f, current.z);
}

void PathSmooth(std::vector<Vector3>& ref) {
	std::vector<int> indexes = { };
	if (ref.size() < 3) return;
	std::vector<Vector3> new_path = { ref[0], ref[1] };
	auto lp = AssemblyCSharp::LocalPlayer::get_Entity();
	Vector3 current = ref[0];
	Vector3 next = ref[1];
	int fi = 0;
	for (size_t i = 2; i < ref.size(); i++)
	{
		next = ref[i];
		if (AssemblyCSharp::IsVisible(current, next)
			&& dist_from_ground(next) <= 1.5f)
			continue;
		else
			new_path.push_back(next);
	}
	if (!new_path.empty() && new_path.size() < ref.size())
		ref = new_path;
}

void CreatePath(Vector3 marker_pos,
	Vector3 point)
{
	NodeTarget node;
	node.pos = marker_pos;
	node.steps = 1;
	//create path
	std::vector<Vector3> path;
	Vector3 original = point;
	bool failed = false;
	Vector3 old_point = point;
	float control = 0.f;
	int iterations = 0;
	while (point.distanceeee(node.pos) > 1.0f)
	{
		if (iterations++ > 500)
			break;

		path.push_back(point);
		//Vector3 new_point = lowest_pos(Vector3::move_towards(point, node.pos, 1.0f));
		Vector3 new_point = Vector3::move_towards(point, node.pos, 1.0f);

		if (AssemblyCSharp::IsVisible(point, new_point, 1.0f))
		{
			//LOG(XS("[DEBUG] CreatePath - visibility straight ahead (%d)"), path.size());
			//vars->local_player->console_echo(string::wformat(_(L"[matrix]: CreatePath - visibility straight ahead (%d)"), path.size()));
			old_point = point;
			point = lowest_pos(new_point);
		}
		else
		{
			//vars->local_player->console_echo(string::wformat(_(L"[matrix]: CreatePath - no visibility straight ahead, creating sphere (%d)"), path.size()));
			//LOG(XS("[DEBUG] CreatePath - no visibility straight ahead, creating sphere (%d)"), path.size());
			std::vector<Vector3> ps = {};

			for (auto e : sphere1m) //create sphere if cannot find LOS straight ahead
				if (AssemblyCSharp::IsVisible(point, point + e, 1.5f)
					&& (point + e).distanceeee(node.pos) < point.distanceeee(node.pos)
					&& (point + e).distanceeee(point) > 0.7f)
				{
					ps.push_back(lowest_pos(point + e));
				}

			Vector3 best = Vector3(0, 0, 0);
			if (ps.size() == 0) {
				//vars->local_player->console_echo(string::wformat(_(L"[matrix]: CreatePath could not create another node, path size: %i"), path.size()));
				//LOG(XS("[DEBUG] CreatePath could not create another node, path size: %i"), path.size());
				break;
			}

			//vars->local_player->console_echo(string::wformat(_(L"[matrix]: CreatePath - potentials: %d"), ps.size()));
			//LOG(XS("[DEBUG] CreatePath - potentials: %d"), path.size());

			for (auto e : ps)
				if (e.distanceeee(node.pos) < best.distanceeee(node.pos)
					&& dist_from_ground(e) < 1.6f)
					best = e;
			//LOG(XS("[DEBUG] CreatePath - closest (best chosen) (%d, %d, %d) (%d)"), (int)best.x, (int)best.y, (int)best.z, path.size());
			//vars->local_player->console_echo(string::wformat(_(L"[matrix]: CreatePath - closest (best chosen) (%d, %d, %d) (%d)"), (int)best.x, (int)best.y, (int)best.z, path.size()));
			old_point = point;
			point = best;
		}
	}

	if (node.path.size() > 5)
	{
		int within_2m = 0;
		int within_idx = 0;
		for (size_t i = 4; i < node.path.size(); i++)
		{
			if (node.path[i].distanceeee(node.path[i - 4]) < 2.f)
				within_2m++;
			else within_idx = i;
		}
		if (within_idx != 0
			&& within_2m != 0) {
			node.path.erase(node.path.begin() + within_idx, node.path.end());
		}
	}

	//if (!node.path.empty())
	//	PathSmooth(node.path);

	node.path = path;
}

void pathfind(AssemblyCSharp::PlayerWalkMovement* pwm,
	Vector3 marker_pos) {
	auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
	Vector3 vel = pwm->get_TargetMovement();
	vel = Vector3(vel.x / vel.length() * 5.5f, vel.y, vel.z / vel.length() * 5.5f);
	auto eyepos = LocalPlayer->get_transform()->get_position();
	NodeTarget node;
	//if (vars->misc.autoattack)
	//	checkandshoot(pwm);

	int walkto = 0;

	auto threshold = walkto == 5 ? 0.1f : 1.f;

	if (node.steps > 0
		&& eyepos.distanceeee(node.pos) < threshold)
	{
		node.path.clear();
		node.pos = Vector3(0, 0, 0);
		node.steps = 0;
		vel = Vector3(0, 0, 0);
		time_at_node += UnityEngine::Time::get_deltaTime();
	}

	if (eyepos.distanceeee(node.pos) >= threshold)
	{
		if (node.path.empty() || ((node.pos.IsZero() || node.pos == Vector3(0, 0, 0))
			&& eyepos.distanceeee(node.pos)) > 1.f
			|| last_player_follow_update + 5.f < UnityEngine::Time::get_fixedTime())
		{
			CreatePath(marker_pos, eyepos);
			last_player_follow_update = UnityEngine::Time::get_fixedTime();
		}
		
		//Vector3 current_step = node.path[node.steps];
		
		//if (current_step.IsZero())
		//	CreatePath(marker_pos, eyepos);
		
		//psteps = node.steps;
		//if (current_step.distanceeee(node.pos) <= threshold / 2.f)
		//{
		//	vel = Vector3(0, 0, 0);
		//	node.path.clear();
		//	node.pos = Vector3(0, 0, 0);
		//	node.steps = 0;
		//	return;
		//}
		
		//draw path
		//if (!node.path.empty())
		//{
		//	for (size_t i = 1; i < node.path.size(); i++)
		//	{
		//		if (node.path[i] == current_step)
		//			UnityEngine::DDraw::Line(node.path[i - 1], node.path[i], Color(190, 20, 20, 50.f), 0.02f, false, true);
		//		else
		//			UnityEngine::DDraw::Line(node.path[i - 1], node.path[i], Color(190, 190, 190, 50.f), 0.02f, false, true);
		//	}
		//}
		
	//	if (eyepos.distanceeee(current_step) < 1.6f)
	//		node.steps += 1;
	//
	//	if (node.steps >= node.path.size() - 1)
	//	{
	//		vel = Vector3(0, 0, 0);
	//		node.path.clear();
	//		node.pos = Vector3(0, 0, 0);
	//		node.steps = 0;
	//		return;
	//	}
	//
		//Vector3 dir = ((Vector3(current_step.x, current_step.y - dist_from_ground(current_step) + 0.1f, current_step.z)) - eyepos).Normalized();
		//vel = { (dir.x / dir.length() * 5.5f), vel.y, (dir.z / dir.length() * 5.5f) };
		//if (!node.pos.IsZero())
		//	pwm->set_TargetMovement(vel);
	//
	//
	//	if (node.path[node.steps].y - eyepos.y > 1.4f)
	//	{
	//		needs_to_jump = true;
	//		pwm->set_TargetMovement({ vel.x, vel.y += 10, vel.z });
	//	}
	//
	//	if (time_within_1m + 5.f < UnityEngine::Time::get_fixedTime()
	//		&& eyepos.distanceeee(last_pos_until_jump) <= 1.f)
	//	{
	//		needs_to_jump = true;
	//		pwm->set_TargetMovement({ vel.x, vel.y += 5, vel.z });
	//		last_pos_until_jump = last_pos;
	//	}
	//	else
	//		time_within_1m = UnityEngine::Time::get_fixedTime();
	//
	}
}

void Hooks::PlayerWalkMovement(AssemblyCSharp::PlayerWalkMovement* _This, AssemblyCSharp::InputState* _State, AssemblyCSharp::ModelState* _ModelState)
{
	if (!InGame)
		return Hooks::PlayerWalkMovementhk.get_original< decltype(&PlayerWalkMovement)>()(_This, _State, _ModelState);

	if (!_This || !_State || !_ModelState)
		return Hooks::PlayerWalkMovementhk.get_original< decltype(&PlayerWalkMovement)>()(_This, _State, _ModelState);

	static bool SilentWalking = false;

	if (!IsAddressValid(Features().LocalPlayer))
	{
		return Hooks::PlayerWalkMovementhk.get_original< decltype(&PlayerWalkMovement)>()(_This, _State, _ModelState);
	}

	if (Features().LocalPlayer->IsDead() || Features().LocalPlayer->IsSleeping()) {
		SilentWalking = false;
		return Hooks::PlayerWalkMovementhk.get_original< decltype(&PlayerWalkMovement)>()(_This, _State, _ModelState);
	}

	if (Features().LocalPlayer->lifestate() & RustStructs::Dead || !Features().LocalPlayer->IsConnected()) {
		SilentWalking = false;
		return Hooks::PlayerWalkMovementhk.get_original< decltype(&PlayerWalkMovement)>()(_This, _State, _ModelState);
	}

	Hooks::PlayerWalkMovementhk.get_original< decltype(&PlayerWalkMovement)>()(_This, _State, _ModelState);

	if (m_settings::AdminFlags)
		_ModelState->remove_flag(RustStructs::ModelState_Flag::Flying);

	//if (m_settings::WalkToMarker)
	//{

	//	auto LocalPlayer = AssemblyCSharp::LocalPlayer::get_Entity();
	//	auto note = LocalPlayer->ClientCurrentMapNotes();
	//	if (note)
	//	{
	//		for (auto i = 0; i < note->_size; i++) {
	//			const auto current = note->_items->m_Items[i];
	//			if (current) {
	//				NodeTarget node;
	//				auto pos = LocalPlayer->get_transform()->get_position();
	//				Vector3 market_pos = current->worldPosition();

	//				if (market_pos.IsZero())
	//					break;

	//				node.pos = market_pos;
	//				pathfind(_This, market_pos);
	//			}
	//		}
	//	}
	//}

	if (m_settings::SilentWalk)
	{
		if (UnityEngine::Input::GetKeyDown(m_settings::SilentWalkKey) && !SilentWalking)
			SilentWalking = true;
		else if (UnityEngine::Input::GetKeyDown(m_settings::SilentWalkKey) && SilentWalking)
			SilentWalking = false;

		if (SilentWalking)
			_ModelState->remove_flag(RustStructs::ModelState_Flag::OnGround);
		
	}
	else
		SilentWalking = false;

	auto g_local_player = Features().LocalPlayer;
	if (IsAddressValid(g_local_player))
	{
		//spiderman
		if (m_settings::SpiderMan)
		{
			if (_This->groundAngle() != 0.f)
				_This->groundAngle() = 0.f;

			if (_This->groundAngleNew() != 0.f)
				_This->groundAngleNew() = 0.f;
		}

		//fly up launch site
		if (m_settings::SmallerLocalRadius)
		{
			_This->capsule()->set_radius(0.44);
		}

		// inf jump
		if (m_settings::InfiniteJump)
		{
			if (_This->landTime() != 0.f)
				_This->landTime() = 0.f;

			if (_This->jumpTime() != 0.f)
				_This->jumpTime() = 0.f;

			if (_This->groundTime() != 100000.f)
				_This->groundTime() = 100000.f;
		}

		//always sprint (not omni sprint)
		if (m_settings::AlwaysSprint)
		{
			if (_This->sprintForced() != true)
				_This->sprintForced() = true;
		}

		static float LastTeleportTime = 0;
		if (m_settings::Teleport && UnityEngine::Input::GetKey(m_settings::TeleportKey))
		{
			if (LastTeleportTime + 20.f < UnityEngine::Time::get_fixedTime())
			{
				LastTeleportTime = UnityEngine::Time::get_fixedTime();

				Vector3 TpPos = Vector3::Zero;
				auto Forward = g_local_player->eyes()->BodyForward() * 5;
				auto Right = g_local_player->eyes()->BodyRight() * 5;
				auto up = Vector3(0, 5, 0);

				if (UnityEngine::Input::GetKey(RustStructs::KeyCode::W))
				{
					TpPos = Forward;
				}
				else if (UnityEngine::Input::GetKey(RustStructs::KeyCode::A))
				{
					TpPos = -Right;
				}
				else if (UnityEngine::Input::GetKey(RustStructs::KeyCode::S))
				{
					TpPos = -Forward;
				}
				else if (UnityEngine::Input::GetKey(RustStructs::KeyCode::D))
				{
					TpPos = Right;
				}
				else if (UnityEngine::Input::GetKey(RustStructs::KeyCode::Space)) {
					TpPos = up;
				}

				_This->TeleportTo(g_local_player->get_transform()->get_position() + TpPos, g_local_player);
			}
		}

		if (!_This->flying())
		{
			if (m_settings::OmniSprint)
			{
				Vector3 vel = _This->get_TargetMovement();
				_ModelState->SetSprinting(true);

				float max_speed = (g_local_player->IsSwimming() || _ModelState->get_ducked() > 0.5) ? 1.7f : 5.5f;
				if (vel.Length() > 0.f) {
					Vector3 target_vel = Vector3(vel.x / vel.Length() * max_speed, vel.y, vel.z / vel.Length() * max_speed);
					_This->set_TargetMovement(target_vel);
				}
			}
		}

		if (m_settings::InteractiveDebug && UnityEngine::Input::GetKey(m_settings::InteractiveKey))
		{
			_ModelState->remove_flag(RustStructs::ModelState_Flag::Aiming);
			_ModelState->SetMounted(true);
		}

		if (m_settings::StopPlayer && m_settings::Manipulation && UnityEngine::Input::GetKey(m_settings::ManipKey))
		{
			Vector3 vel = _This->get_TargetMovement();

			float max_speed = (_This->swimming() || _This->ducking() > 0.5) ? 1.7f : 5.5f;
			if (vel.Length() > 0.f) {
				_This->set_TargetMovement(Vector3());
			}
		}
	}
}